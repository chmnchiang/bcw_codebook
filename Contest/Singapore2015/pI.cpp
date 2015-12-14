#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

typedef long long ll;

const int MAXN = 505050;
const ll MOD = 1000000007;

ll A, C, M;

ll fact[MAXN], ifact[MAXN];
ll tpow[MAXN];

ll inv(ll a)
{
	ll ret = 1, cur = a, p = MOD-2;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return ret;
}

void pre()
{
	fact[0] = 1;
	for(int i=1; i<MAXN; i++)
		fact[i] = (fact[i-1] * i) % MOD;
	for(int i=0; i<MAXN; i++)
		ifact[i] = inv(fact[i]);
	tpow[0] = 1;
	for(int i=1; i<MAXN; i++)
		tpow[i] = (tpow[i-1] * 2) % MOD;	
}

ll comb(int x, int y)
{
	if(x < 0 || y < 0 || x < y) return 0;
	return fact[x] * ifact[y] % MOD * ifact[x-y] % MOD;
}

ll f(ll N)
{
	if(C < 0) return 0;

	ll ret = 0;

	for(ll g=0; g<=N; g++)
	{
		ll a = A-M+N-g;
		ll b = N-g-A+M;
		if(a < 0 || b < 0 || a%2 || b%2) continue;
		a /= 2;
		b /= 2;
		ll p = A+M-N+g;
		if(p < g || p%2) continue;
		p /= 2;

//		cout<<"GOOD "<<a<<" "<<b<<" "<<g<<" "<<p<<endl;

		ll val = comb(N, a) * comb(N-a, b) % MOD;
		val = val * tpow[g] % MOD;
		val = val * comb(p-g+N-1, N-1) % MOD;
//		cout<<val<<endl;
		ret += val;
	}
	ret %= MOD;

//	cout<<N<<" : "<<ret<<endl;
	return ret;
}

int main() {
	pre();
	cin>>A>>C>>M;
	ll ans = f(C+1) + 2 * f(C) + f(C-1);
	ans %= MOD;
	if(ans < 0) ans += MOD;

	cout<<ans<<endl;

	return 0;
}

