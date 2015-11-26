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
// Let's Fight!

typedef long long ll;

const int MAXN = 514;
const ll MOD = 1000000007;

int N;
ll fact[MAXN];
ll ifact[MAXN];

ll inv(ll x)
{
	ll p = MOD-2, cur = x, res = 1;
	while(p)
	{
		if(p&1LL)
			res = res * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return res;
}

void pre()
{
	fact[0] = 1;
	for(int i=1; i<MAXN; i++)
		fact[i] = (fact[i-1] * i) % MOD;
	for(int i=0; i<MAXN; i++)
		ifact[i] = inv(fact[i]);
}

ll calc(int a, int b, int c)
{
	ll ret = (fact[N] * (a-c+2) * (a-b+1) * (b-c+1)) % MOD;
	ret = ret * ifact[a+2] % MOD;
	ret = ret * ifact[b+1] % MOD;
	ret = ret * ifact[c] % MOD;
	return ret;
}

int main() {
    FILEIO("great");
	pre();
	IOS;
	cin>>N;

	ll ans = 0;
	for(int a=0; a<=N; a++)
	{
		for(int b=0; b<=a; b++)
		{
			int c = N-a-b;
			if(c < 0 || c > b) continue;
			ll val = calc(a, b, c);
			ans += val * val;
			ans %= MOD;
		}
	}

	cout<<ans<<endl;

    return 0;
}

