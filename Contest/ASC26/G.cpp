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


const int MAXN = 52;
const int MOD = 10003;

int M, N, K;
int dp[MAXN][MAXN][MAXN][MAXN];

void update(int &x, int y)
{
	x = (x + y) % MOD;
}

int calc()
{
	dp[0][M][0][0] = 1;
	for(int i=0; i<N; i++)
	{
		for(int n0=0; n0<=M; n0++)
		{
			for(int n1=0; n1<=M; n1++)
			{
				for(int n2=0; n2<=M; n2++)
				{
					if(dp[i][n0][n1][n2] == 0) continue;
					int v = dp[i][n0][n1][n2];
//					cout<<i<<" "<<n0<<" "<<n1<<" "<<n2<<" = "<<v<<endl;

					update(dp[i+1][n0][n1][n2], v);
					if(n0 >= 1) update(dp[i+1][n0-1][n1+1][n2], v * n0);
					if(n1 >= 1) update(dp[i+1][n0][n1-1][n2+1], v * n1);
					if(n0 >= 2) update(dp[i+1][n0-2][n1+2][n2], v * (n0 * (n0-1) / 2));
					if(n1 >= 2) update(dp[i+1][n0][n1-2][n2+2], v * (n1 * (n1-1) / 2));
					if(n0 >= 1 and n1 >= 1) update(dp[i+1][n0-1][n1][n2+1], v * n0 * n1);
				}
			}
		}
	}

	int ans = 0;
	for(int i=0; i<=M; i++)
	{
		for(int j=0; j<=M; j++)
		{
			for(int k=0; k<=M; k++)
			{
				if(j + 2 * k == K)
				{
					ans = (ans + dp[N][i][j][k]) % MOD;
				}
			}
		}
	}

	return ans;
}

int main() {
	FILEIO("rooks");
	IOS;

	cin>>M>>N>>K;

	int ans = calc();
	cout<<ans<<endl;

    return 0;
}

