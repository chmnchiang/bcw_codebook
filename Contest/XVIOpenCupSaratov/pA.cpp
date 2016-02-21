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
#define REP(i,n) for (int i=0;i<(n);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MAXN = 404;
const int MAXC = 33;
const int MAXL = 4096;

int N;
int arr[MAXN];
int cnt[MAXC];
vector<int> cvec[MAXC];
bitset<MAXL> dp[MAXC][MAXL], tmp[MAXL];
int cpos[MAXC];
vector<int> vans[3];
bool used[MAXN];

void calc()
{
	int tot = 0;
	for(int i=0; i<N; i++)
		tot += arr[i];

	dp[0][0][0] = true;
	for(int i=1; i<MAXC; i++)
	{
		for(int j=0; j<MAXL; j++)
			dp[i][j] = dp[i-1][j];
		for(int j=0; j<cnt[i-1]; j++)
		{
			for(int k=0; k<MAXL; k++)
				tmp[k] = dp[i][k];
			for(int k=0; k<MAXL; k++)
			{
				tmp[k] |= dp[i][k] << (i-1);
				if(k+i-1 < MAXL)
					tmp[k+i-1] |= dp[i][k];
			}
			for(int k=0; k<MAXL; k++)
				dp[i][k] = tmp[k];
		}
	}

	int best = MAXL, bi = -1, bj = -1;
	for(int i=0; i<MAXL; i++)
	{
		for(int j=0; j<MAXL; j++)
		{
			if(!dp[MAXC-1][i][j]) continue;
			int k = tot - i - j;
			int dif = max(max(i, j), k) - min(min(i, j), k);
			if(dif < best)
			{
				best = dif;
				bi = i;
				bj = j;
			}
		}
	}

	for(int i=MAXC-2; i>=0; i--)
	{
		bool ok = false;
		int ni, nj;
		for(int j=0; j<=cnt[i]; j++)
		{
			if(ok) break;
			ni = bi - j * i;
			if(ni < 0) continue;
			for(int k=0; j+k<=cnt[i]; k++)
			{
				nj = bj - k * i;
				if(nj < 0) continue;
				if(dp[i][ni][nj])
				{
					for(int l=0; l<j; l++)
					{
						int v = cvec[i][cpos[i]++];
						used[v] = true;
						vans[0].PB(v);
					}
					for(int l=0; l<k; l++)
					{
						int v = cvec[i][cpos[i]++];
						used[v] = true;
						vans[1].PB(v);
					}
					bi = ni;
					bj = nj;
					ok = true;
					break;
				}
			}
		}
	}

	for(int i=0; i<N; i++)
		if(!used[i])
			vans[2].PB(i);

	cout<<best<<endl;
	for(int i=0; i<3; i++)
	{
		int S = vans[i].size();
		cout<<S;
		for(int j=0; j<S; j++)
			cout<<" "<<vans[i][j]+1;
		cout<<endl;
	}
}

int main() {
	IOS;
	cin>>N;
	for(int i=0; i<N; i++)
	{
		cin>>arr[i];
		cnt[arr[i]]++;
		cvec[arr[i]].PB(i);
	}

	calc();

    return 0;
}
