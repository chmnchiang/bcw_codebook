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

const int MAXN = 514;
const ll MOD = 1000000007;

int N, K, P;
ll comb[MAXN][MAXN];
ll fact[MAXN];

void make_comb()
{
	fact[0] = 1;
	for(int i=1; i<MAXN; i++)
		fact[i] = (fact[i-1] * i) % MOD;
	comb[0][0] = 1;
	for(int i=1; i<MAXN; i++)
	{
		comb[i][0] = 1;
		for(int j=1; j<=i; j++)
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
	}
}

ll C(int a, int b)
{
	if(a<0 || b<0 || b>a) return 0;
	return comb[a][b];
}

int main() {
	make_comb();
	IOS;
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>K>>P;
		ll ans = 0;
		for(int i=1; i<=N-K; i++)
		{
			ans += fact[N-i-1] * (C(N-1, i) - (i==N-K ? 0 : C(P-1, i)));
			ans %= MOD;
		}
		if(ans < 0) ans += MOD;
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

    return 0;
}

