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

const int MAXN = 205;

typedef pair<int, int> pii;

int N, K;

bool has[MAXN][MAXN];
int pcnt[MAXN], kcnt[MAXN];
int totcnt;
vector<pii> vreq[MAXN];
int val[MAXN][MAXN];
int ans[MAXN];
int push[MAXN], pk[MAXN];

void calc()
{
	for(int i=0; i<K; i++)
	{
		has[0][i] = true;
		kcnt[i] = 1;
	}
	pcnt[0] = K;
	totcnt = K;

	int rnd = 0;
	while(totcnt < N*K)
	{
		rnd++;
//		cout<<"ROUND "<<rnd<<endl;

		for(int i=0; i<N; i++)
			vreq[i].clear();

		for(int i=0; i<N; i++)
		{
			int reqk = -1;
			for(int k=0; k<K; k++)
			{
				if(has[i][k]) continue;
				if(reqk == -1 or kcnt[reqk] > kcnt[k])
					reqk = k;
			}

			if(reqk == -1) continue;

			int reqp = -1;
			for(int p=0; p<N; p++)
			{
				if(!has[p][reqk]) continue;
				if(reqp == -1 or pcnt[reqp] > pcnt[p])
					reqp = p;
			}
			vreq[reqp].PB({i, reqk});

//			cout<<i+1<<" REQ "<<reqk+1<<" FROM "<<reqp+1<<endl;
		}

		for(int i=0; i<N; i++)
		{
			push[i] = -1, pk[i] = -1;
			sort(ALL(vreq[i]));
			for(auto x: vreq[i])
			{
				int p = x.F, k = x.S;
				if(push[i] == -1 or val[push[i]][i] < val[p][i] or (val[push[i]][i] == val[p][i] and pcnt[push[i]] > pcnt[p]))
				{
					push[i] = p;
					pk[i] = k;
				}
			}
		}

		for(int i=0; i<N; i++)
		{
			if(push[i] == -1) continue;
			has[push[i]][pk[i]] = true;
			pcnt[push[i]]++;
			kcnt[pk[i]]++;
			totcnt++;
			val[i][push[i]]++;

			if(pcnt[push[i]] == K)
				ans[push[i]] = rnd;

//			cout<<push+1<<" GET "<<pk+1<<" FROM "<<i+1<<endl;
		}
	}

	for(int i=1; i<N; i++)
		cout<<ans[i]<<" ";
	cout<<endl;
}

int main() {
	IOS;
	FILEIO("epig");

	cin>>N>>K;

	calc();

	return 0;
}

