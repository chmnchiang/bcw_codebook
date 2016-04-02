#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

const int MAXS = 55;
const int MAXN = 20;

int N, K;
int myid;
string teamname[MAXN];
int init_score[MAXN];
double pwin[MAXN][MAXN], pdraw[MAXN][MAXN];
bool played[MAXN][MAXN];
double score_prob[MAXN][MAXS];
double person_prob[MAXN];
double rank_kp1_prob[MAXS];
double tmp[MAXS];
double my_prob[MAXN][MAXS];
bool curr_use[MAXN];
double best;
bool ans[MAXN];

void dfs(int lv)
{
	if(lv == N)
	{
		double res = 0;
		for(int i=0; i<MAXS; i++)
			res += my_prob[lv][i] * rank_kp1_prob[i];
		if(res > best)
		{
			best = res;
			for(int i=0; i<N; i++)
				ans[i] = curr_use[i];
		}
		return;
	}
	curr_use[lv] = 0;
	for(int i=0; i<MAXS; i++)
		my_prob[lv+1][i] = my_prob[lv][i];
	dfs(lv+1);

	if(lv == myid) return;
	if(played[myid][lv]) return;

	curr_use[lv] = 1;
	for(int i=0; i<MAXS; i++)
		my_prob[lv+1][i] = 0;
	double pw = pwin[myid][lv], pd = pdraw[myid][lv];
	double pl = 1 - pw - pd;
	for(int i=0; i<MAXS; i++)
	{
		if(i+3<MAXS)
			my_prob[lv+1][i+3] += my_prob[lv][i] * pw;
		if(i+1<MAXS)
			my_prob[lv+1][i+1] += my_prob[lv][i] * pd;
		my_prob[lv+1][i] += my_prob[lv][i] * pl;
	}
	dfs(lv+1);
}

void calc()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			pwin[i][j] *= 0.01;
			pdraw[i][j] *= 0.01;
		}
	}

	for(int i=0; i<N; i++)
	{
		if(i == myid) continue;
		for(int j=0; j<MAXS; j++)
			score_prob[i][j] = 0;
		score_prob[i][init_score[i]] = 1;

		for(int j=0; j<N; j++)
		{
			if(j == i) continue;
			if(played[i][j]) continue;
			for(int k=0; k<MAXS; k++)
				tmp[k] = 0;
			double pw = pwin[i][j] * 0.5, pd = pdraw[i][j] * 0.5;
			double pl = 1 - pw - pd;
			for(int k=0; k<MAXS; k++)
			{
				if(k+3<MAXS)
					tmp[k+3] += score_prob[i][k] * pw;
				if(k+1<MAXS)
					tmp[k+1] += score_prob[i][k] * pd;
				tmp[k] += score_prob[i][k] * pl;
			}
			for(int k=0; k<MAXS; k++)
				score_prob[i][k] = tmp[k];
		}
	}

	for(int s=0; s<MAXS; s++)
	{
		for(int j=0; j<=N; j++)
			person_prob[j] = 0;
		person_prob[0] = 1;

		for(int i=0; i<N; i++)
		{
			if(i == myid) continue;
			double p = 0;
			for(int j=s; j<MAXS; j++)
				p += score_prob[i][j];
			for(int j=0; j<=N; j++)
				tmp[j] = 0;
			for(int j=0; j<=N; j++)
			{
				if(j+1<=N)
					tmp[j+1] += person_prob[j] * p;
				tmp[j] += person_prob[j] * (1-p);
			}
			for(int j=0; j<=N; j++)
				person_prob[j] = tmp[j];
		}
		rank_kp1_prob[s] = person_prob[K];
	}

	for(int i=0; i<N; i++)
		curr_use[i] = false;

	best = -1;
	for(int i=0; i<MAXS; i++)
		my_prob[0][i] = 0;
	my_prob[0][init_score[myid]] = 1;

	dfs(0);

//	cout<<best<<endl;

	vector<string> vans;
	for(int i=0; i<N; i++)
		if(ans[i])
			vans.PB(teamname[i]);

	cout<<vans.size()<<endl;
	for(auto s: vans)
		cout<<s<<endl;
}

int main() {
	IOS;
	FILEIO("division2");

	cin>>N>>K;
	for(int i=0; i<N; i++)
		cin>>teamname[i]>>init_score[i];
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			cin>>pwin[i][j];
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			cin>>pdraw[i][j];
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			cin>>played[i][j];
	string s;
	cin>>s;
	for(int i=0; i<N; i++)
		if(teamname[i] == s)
			myid = i;

	calc();

	return 0;
}

