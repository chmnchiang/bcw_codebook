#pragma GCC optimize ("O2")
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

const int MAXN = 205;
const ll MOD = 1000000007;

int N, M, K;
ll psum[MAXN*2], kpow[MAXN*MAXN];
ll Gk[5], numk[5];

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

ll calc()
{
	kpow[0] = 1;
	for(int i=1; i<=N*M; i++)
		kpow[i] = kpow[i-1] * K % MOD;

	for(int j=0; j<MAXN*2; j++)
		psum[j] = 0;

	for(int i=1; i<=K; i++)
	{
		ll cur = 1;
		for(int j=0; j<MAXN*2; j++)
		{
			psum[j] += cur;
			cur = (cur * (i-1)) % MOD;
		}
	}
	for(int j=0; j<MAXN*2; j++)
		psum[j] %= MOD;

	ll ans = 0;

	ans = ((N*M*psum[N+M-2]) % MOD) * kpow[N*M-N-M+1] + kpow[N*M];
	ans %= MOD;
	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M>>K;
		ll ans = calc();
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

