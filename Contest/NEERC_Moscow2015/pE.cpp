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
const int MAXK = 19;
const int MAXN = 1<<MAXK;
const ll MOD = 1000000007;

int K, N;
ll arr[MAXN];
ll fact[MAXN], ifact[MAXN];

ll inv(ll a)
{
	ll cur = a, ret = 1, p = MOD-2;
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
		fact[i] = fact[i-1] * i % MOD;
	for(int i=0; i<MAXN; i++)
		ifact[i] = inv(fact[i]);
}

ll comb(int a, int b)
{
	if(a < 0 || b < 0 || a < b) return 0;
	return fact[a] * ifact[b] % MOD * ifact[a-b] % MOD;
}

ll f(int x)
{
	ll ret = 0;
	ll sca = 0;
	for(int b=1; b<=N; b++)
	{
		ll ratio = comb(b-x-1, x-1) * arr[b] % MOD * sca % MOD;
		ret += ratio;
		sca += comb(b-1, x-1) * arr[b];
		sca %= MOD;
	}
	ret *= 2;
	ret %= MOD;
	ret = ret * inv(comb(N, x) * comb(N-x, x) % MOD) % MOD;

	return ret;
}

int main() {
	pre();
	IOS;
	cin>>K;
	N = (1<<K);
	for(int i=0; i<N; i++)
		cin>>arr[N-i];

	ll ans = 0;
	for(int i=0; i<K; i++)
	{
		ans += f(1<<i) * (1<<(K-i-1));
		ans %= MOD;
	}

	cout<<ans<<endl;

    return 0;
}

