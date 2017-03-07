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

using ll = long long;
using pll = pair<ll,ll>;

const int MXN = 100005;
const pll P(1877,8999);
const pll MOD(1000000007,1000000009);

pll operator + (const pll a, const pll b) {
	ll x = (a.F+b.F) % MOD.F;
	ll y = (a.S+b.S) % MOD.S;
	return {x,y};
}
pll operator - (const pll a, const pll b) {
	ll x = (a.F-b.F+MOD.F) % MOD.F;
	ll y = (a.S-b.S+MOD.S) % MOD.S;
	return {x,y};
}
pll operator * (const pll a, const pll b) {
	ll x = (a.F*b.F) % MOD.F;
	ll y = (a.S*b.S) % MOD.S;
	return {x,y};
}

struct Tree {
	int n,fa[MXN];
	pll dp[MXN], hs[MXN];
	vector<int> E[MXN];
	void init(int tn) {
		n = tn;
		REP1(i,1,n) E[i].clear();
	}
	void add_edge(int u, int v) {
		E[u].PB(v);
		E[v].PB(u);
	}
	void DFS(int u, int f) {
		fa[u] = f;
		dp[u] = {0,0};
		for (auto v:E[u]) {
			if (v == f) continue;
			DFS(v, u);
			dp[u] = dp[u] + dp[v] * dp[v];
		}
		dp[u] = dp[u] + P;
	}
	void DFS2(int u) {
		int f = fa[u];
		if (f == u) hs[u] = dp[u];
		else {
			auto x = hs[f] - dp[u] * dp[u];
			hs[u] = dp[u] + x * x;
		}
		for (auto v:E[u]) {
			if (v == f) continue;
			DFS2(v);
		}
	}
	void make() {
		DFS(1,1);
		DFS2(1);
	}
	bool isleaf(int x) {
		return SZ(E[x]) == 1;
	}
} tree1, tree2;

int N;

int main() {
	IOS;
	while (cin>>N) {
		tree1.init(N);
		REP(i,N-1) {
			int u,v;
			cin>>u>>v;
			tree1.add_edge(u,v);
		}

		tree2.init(N+1);
		REP(i,N) {
			int u,v;
			cin>>u>>v;
			tree2.add_edge(u, v);
		}

		tree1.make();
		tree2.make();

		set<pll> s;
		REP1(i,1,N) s.insert(tree1.hs[i]);

		/*
		REP1(i,1,N) {
			cout<<"T1 "<<i<<" : "<<tree1.hs[i]<<endl;
		}

		REP1(i,1,N+1) {
			cout<<"T2 "<<i<<" : "<<tree2.dp[i]<<" "<<tree2.hs[i]<<endl;
		}
		*/

		int ans = -1;
		REP1(u,1,N+1) {
			if (!tree2.isleaf(u)) continue;
			int v = tree2.E[u][0];
			pll h = tree2.hs[v] - P*P;

//			cout<<u<<": "<<v<<"  "<<h<<endl;

			if (s.count(h)) {
				ans = u;
				break;
			}
		}
		cout<<ans<<endl;
	}

	return 0;
}

