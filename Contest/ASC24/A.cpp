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

typedef long long ll;

const int MAXN = 32;
const int MAXM = 5005;
const ll INF = 1LL<<50;

int N, M;
ll g[MAXN], gg[MAXN], s[MAXN];
int ord[MAXN];

ll dp[MAXN][MAXM], ep[MAXN][MAXM][MAXN];
short dprv[MAXN][MAXM], eprv[MAXN][MAXM][MAXN];
int ant[MAXN];

bool cmp(int a, int b){return g[a] < g[b];}

void calc()
{
	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(ord, ord+N, cmp);

	for(int i=0; i<N; i++)
		gg[i] = g[ord[i]];

	s[0] = 0;
	for(int i=0; i<N; i++)
		s[i+1] = s[i] + gg[i];

	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<=M; j++)
		{
			dp[i][j] = INF;
			for(int k=0; k<=N; k++)
				ep[i][j][k] = INF;
		}
	}

	for(int i=N; i>=0; i--)
	{
		for(int k=0; k<=M; k++)
		{
			if(i==N)
			{
				dp[i][k] = (k==0 ? 0 : INF);
			}
			else
			{
				if(k-(N-i)<0) continue;
				for(int j=i+1; j<=N; j++)
				{
					ll val = ep[j][k-(N-i)][N-i] + (N-j) * (s[j]-s[i]);
					if(val < dp[i][k])
					{
						dp[i][k] = val;
						dprv[i][k] = j;
					}
				}
			}
		}

		for(int y=1; y<=N; y++)
		{
			for(int k=0; k<=M; k++)
			{
				ep[i][k][y] = dp[i][k];
				eprv[i][k][y] = k;

				if(k-y>=0 and ep[i][k-y][y] < ep[i][k][y])
				{
					ep[i][k][y] = ep[i][k-y][y];
					eprv[i][k][y] = eprv[i][k-y][y];
				}
			}
		}
	}

	ll ans = dp[0][M];
	cout<<ans<<endl;

	int curk = M;
	int sum = 0;
	for(int i=0; i<N; )
	{
		int j = dprv[i][curk];
		int k = eprv[j][curk-(N-i)][N-i];
		int dk = (curk - k) / (N-i);
		sum += dk;
		for(int x=i; x<j; x++)
			ant[ord[x]] = sum;

		curk = k;
		i = j;
	}
	assert(curk == 0);

	for(int i=0; i<N; i++)
		cout<<ant[i]<<" ";
	cout<<endl;
}

int main() {
	IOS;
	FILEIO("cookies");

	cin>>N>>M;
	for(int i=0; i<N; i++)
		cin>>g[i];

	calc();

	return 0;
}

