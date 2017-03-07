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

namespace HH{
	const int MAXN = 100;
	vector<vector<int>> resvvv;
	void go(int mn, int rem, vector<int> &vec) {
		if (rem == 0) {
			resvvv.PB(vec);
		}
		REP1(i,mn,rem) {
			vec.PB(i);
			go(i,rem-i,vec);
			vec.pop_back();
		}
	}
	vector<vector<int>> ws360(int n) {
		resvvv.clear();
		vector<int> vec;
		go(1,n,vec);
		return resvvv;
	}
	struct DisjoinSet {
		int fa[MAXN];
		void init(int n) {
			REP(i,n) fa[i]=i;
		}
		int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
		void uni(int x, int y) {
			fa[f(y)] = f(x);
		}
	};

	struct Graph {
		DisjoinSet djs;
		int n;
		int E[MAXN];
		void init(int tn) {
			n = tn;
			REP(i,n) E[i] = 0;
			djs.init(n);
		}
		void add_edge(int u, int v) {
			djs.uni(u, v);
			E[u] = E[v] = 1;
		}
		int calc() {
			int res = 0;
			REP(i,n) {
				if (djs.f(i) == i) res++;
			}
			return res;
		}

	};
}

using HH::ws360;
using HH::Graph;

Graph gp;

const int MAXN = 62;
const ll MOD = 1000000007;

ll twopow[MAXN*MAXN], fact[MAXN*MAXN];
ll f[MAXN], g[MAXN], h[MAXN][MAXN];
ll ans[MAXN];
int gcd[MAXN][MAXN];

ll lpow(ll a, ll p)
{
	ll ret = 1, cur = a;
	p %= MOD;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return ret;
}

ll linv(ll a)
{
	return lpow(a, MOD-2);
}

void pre()
{
	twopow[0] = 1;
	fact[0] = 1;
	for(int i=1; i<MAXN*MAXN; i++)
	{
		twopow[i] = (twopow[i-1] * 2) % MOD;
		fact[i] = (fact[i-1] * i) % MOD;
	}
	for(int i=1; i<MAXN; i++)
		for(int j=1; j<MAXN; j++)
			gcd[i][j] = __gcd(i, j);
}

ll H(ll n, ll m)
{
	n %= MOD;
	ll ret = linv(fact[m]);
	for(int i=0; i<m; i++)
		ret = ret * (n+i) % MOD;
	return ret;
}

void calc_g(int n)
{
	auto vecs = ws360(n);

	ll res = 0;
	for(auto p: vecs)
	{
		int M = SZ(p);
		ll down = 1;
		for(auto x: p)
			down = (down * x) % MOD;
		int pos = 0;
		while(pos < M)
		{
			int cnt = 0;
			int z = p[pos];
			while(pos < M and p[pos] == z)
			{
				pos++;
				cnt++;
			}
			down = (down * fact[cnt]) % MOD;
		}

		ll numsigma = (fact[n] * linv(down)) % MOD;

		ll V = M + 1;
		gp.init(V);

		int E = 0;

		for(int i=0; i<M; i++)
		{
			E += (p[i]+1)/2;
			if(p[i]%2 == 0)
			{
				E++;
				gp.add_edge(i, M);
			}
		}

		for(int i=0; i<M; i++)
		{
			for(int j=i+1; j<M; j++)
			{
				int gg = gcd[p[i]][p[j]];
				int a = p[i] / gg, b = p[j] / gg;
				E += gg;
				a %= 2;
				b %= 2;
				int lv = (b ? i : M);
				int rv = (a ? j : M);
				gp.add_edge(lv, rv);
			}
		}

		int C = gp.calc();

		for(int i=0; i<M; i++)
		{
			if(!gp.E[i])
			{
//				C += (p[i]%2 ? p[i] : p[i]/2) - 1;
//				if(p[i]%2 == 0)
//					V += p[i]/2;
			}
		}

		int epo = E - V + C;
		ll num = twopow[epo];
//		cout<<"# "<<p<<" = "<<numsigma<<", E "<<E<<" V "<<V<<" C "<<C<<" EXP "<<epo<<endl;
		res = (res + num * numsigma) % MOD;
	}

	res = (res * linv(fact[n])) % MOD;
	g[n] = res;
	cout<<"G "<<n<<" = "<<g[n]<<endl;
}

void calc()
{
	for(int i=0; i<MAXN; i++)
		h[i][0] = 0;
	h[0][0] = 1;

	for(int i=1; i<MAXN; i++)
	{
		calc_g(i);
		f[i] = (g[i] - h[i][i-1] + MOD) % MOD;
//		cout<<"F "<<i<<" : "<<f[i]<<endl;

		h[0][i] = 1;
		for(int j=1; j<MAXN; j++)
		{
			h[j][i] = 0;
			for(int x=0; x*i<=j; x++)
			{
				h[j][i] += h[j-x*i][i-1] * H(f[i], x);
				//cout<<"HH("<<f[i]<<","<<x<<") = "<<H(f[i], x)<<endl;
				h[j][i] %= MOD;
			}
//			cout<<"H "<<j<<" "<<i<<" : "<<h[j][i]<<endl;
		}
	}

	ans[0] = MOD-1;
	for(int i=1; i<MAXN; i++)
		ans[i] = (ans[i-1] + f[i]) % MOD;

	for(int i=1; i<MAXN; i++)
		cout<<ans[i]<<",";
	cout<<endl;
}

int main() {
	IOS;
	pre();
	cout<<SZ(ws360(60))<<endl;
	gp.init(4);

	calc();

	return 0;
}

