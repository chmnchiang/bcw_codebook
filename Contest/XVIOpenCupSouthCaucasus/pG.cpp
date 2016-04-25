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

const int MAXN = 101010;
const ll MOD = 1000000033;

int N, K;
int bad[MAXN];
ll cumu[MAXN];

ll lpow(ll a, ll p)
{
	ll ret = 1, cur = a % MOD;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return ret;
}

ll inv(ll a)
{
	return lpow(a, MOD-2);
}

ll calc()
{
	ll sum = 0;
	ll ans = 0;
	cumu[N] = 1;
	for(int i=N; i>=0; i--)
	{
		ll cur = (sum + cumu[i]) % MOD;

		ll v = cur * inv(i) % MOD;
		sum = (sum + v) % MOD;
		ll mv = (MOD - v) % MOD;
		for(int j=0; j<K; j++)
		{
			int k = i - bad[j];
			if(k < 0) continue;
			cumu[k] = (cumu[k] + mv) % MOD;
		}

		if(i == 0) ans = cur;
	}

	for(int i=1; i<=N; i++)
		ans = (ans * i) % MOD;
	return ans;
}

int main() {
	IOS;

	cin>>N>>K;
	for(int i=0; i<K; i++)
		cin>>bad[i];

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

