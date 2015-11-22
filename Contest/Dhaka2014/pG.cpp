#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;

const int MAXN = 2020;
const ll MOD = 1000000007;

int N, K;
ll comb[MAXN][MAXN];
ll fact[MAXN];
ll dp[MAXN][MAXN][2][2];
ll num[MAXN];
ll m[MAXN];

void pre()
{
	comb[0][0] = 1;
	for(int i=1; i<MAXN; i++)
	{
		comb[i][0] = 1;
		for(int j=1; j<=i; j++)
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
	}

	fact[0] = 1;
	for(int i=1; i<MAXN; i++)
		fact[i] = (fact[i-1] * i) % MOD;
}

void calc_dp()
{
	for(int i=0; i<=N; i++)
		num[i] = 0;
	for(int x=0; x<4; x++)
	{
		for(int i=0; i<=N; i++)
			for(int j=0; j<=N; j++)
				for(int k=0; k<2; k++)
					for(int l=0; l<2; l++)
						dp[i][j][k][l] = 0;

		if(x == 0)
			dp[2][2][0][0] = 1;
		if(x == 1)
			dp[2][2][1][0] = dp[2][2][0][1] = dp[2][1][0][0] = 1;
		if(x == 2)
		{
			dp[2][2][1][0] = 2;
			dp[2][2][0][1] = 1;
			dp[2][1][0][0] = 2;
		}
		if(x == 3)
		{
			dp[2][2][1][1] = 1;
			dp[2][1][1][0] = 2;
			dp[2][1][0][1] = 1;
			dp[2][0][0][0] = 1;
		}

		int start = 3;
		for(int i=start; i<=N; i++)
		{
			for(int j=0; j<=i; j++)
			{
				for(int a=0; a<2; a++)
				{
					for(int b=0; b<2; b++)
					{
						dp[i][j][b][0] += dp[i-1][j][a][b];

						if(j > 0)
						{
							if(a == 0)
								dp[i][j][b][0] += dp[i-1][j-1][a][b];
							if(b == 0)
								dp[i][j][1][0] += dp[i-1][j-1][a][b];
							dp[i][j][b][1] += dp[i-1][j-1][a][b];
						}
					}
				}
				for(int a=0; a<2; a++)
					for(int b=0; b<2; b++)
						dp[i][j][a][b] %= MOD;
			}
		}

		for(int i=0; i<=N; i++)
		{
			if(x == 0)
				num[i] += dp[N][i][0][0];
			else if(x == 1)
				num[i] += dp[N][i][0][0] + dp[N][i][0][1];
			else if(x == 2)
				num[i] += dp[N][i][1][0] + dp[N][i][0][0];
			else if(x == 3)
				num[i] += dp[N][i][0][0] + dp[N][i][0][1] + dp[N][i][1][0] + dp[N][i][1][1];
		}
	}
	
	for(int i=0; i<=N; i++)
	{
		num[i] %= MOD;
		num[i] = (num[i] * fact[N-i]) % MOD;
	}
}

ll calc_ans()
{
	m[K] = 1;
	for(int x=K+1; x<=N; x++)
	{
		m[x] = 1;
		for(int i=K; i<x; i++)
		{
			m[x] -= comb[x][i] * m[i];
			m[x] %= MOD;
		}
		if(m[x] < 0) m[x] += MOD;
	}

	ll ans = 0;
	for(int i=K; i<=N; i++)
	{
		ans += m[i] * num[i];
		ans %= MOD;
	}
	if(ans < 0) ans += MOD;
	return ans;
}

int main() {
	IOS;
	pre();
	int T;
	cin>>T;
	for(int _t=1; _t<=T; _t++)
	{
		cin>>N>>K;
		calc_dp();
		ll ans = calc_ans();
		cout<<"Case "<<_t<<": "<<ans<<endl;
	}

    return 0;
}


