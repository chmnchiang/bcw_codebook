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

#define int long long
const int MX = 333333;
const int LG = 22;
int N, Q;
vector<int> el[MX];
int pfa[LG][MX];
auto *fa = pfa[0];
int dep[MX];
int stamp[MX];
int few[MX];
using pii = pair<int, int>;
vector<pii> wel[MX];

void dfs1(int me, int f, int d) {
	dep[me] = d;
	for (auto he: el[me]) {
		if (he == f) continue;
		fa[he] = me;
		dfs1(he, me, d+1);
	}
}

void make_pfa() {
	for (int i=1; i<LG; i++) {
		for (int u=1; u<=N; u++) {
			pfa[i][u] = pfa[i-1][pfa[i-1][u]];
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int dd = dep[u] - dep[v];
	for (int i=0; dd; i++, dd/=2) {
		if (dd & 1) u = pfa[i][u];
	}

	if (u == v) return u;

	for (int i=LG-1; i>=0; i--) {
		if (pfa[i][u] != pfa[i][v]) {
			u = pfa[i][u];
			v = pfa[i][v];
		}
	}
	assert(u != v);
	u = fa[u]; v = fa[v];
	assert(u == v);
	return u;
}

static void make_stamp() {
	for (int i=0; i<Q; i++) {
		int u, v; cin >> u >> v;
		stamp[u] ++;
		stamp[v] ++;
		int w = lca(u, v);
		stamp[w] -= 2;
	}
}

int dp1[MX], dp2[MX];
int sch[MX], se[MX];

int dfs2(int me, int f) {
	int res = 0;
	dp1[me] = 0;
	for (auto he: el[me]) {
		if (he == f) continue;
		int t = dfs2(he, me);
		wel[me].PB({he, t});
		res += t;

		dp1[me] += dp1[he] + t;
		sch[me] += dp1[he];
		se[me] += t;
	}
	sort(ALL(wel[me]), [](pii p1, pii p2) { return p1.S > p2.S; });

	if (SZ(wel[me])) dp1[me] -= wel[me][0].S;

	res += stamp[me];
	if (me != 1) {
		few[me] = res;
		se[me] += res;
	}
	return res;
}

void dfs3(int me, int f) {
	if (me == 1) {
		dp2[me] = 0;
	} else {
		int mx = -1;
		for (int i=0; i<2; i++) {
			if (i >= SZ(wel[f])) break;
			if (wel[f][i].F == me) continue;
			mx = max(mx, wel[f][i].S);
		}
		mx = max(mx, few[f]);
		dp2[me] = dp2[f] + sch[f] - dp1[me] + se[f] - few[me] - mx;
	}

	for (auto he: el[me]) {
		if (he == f) continue;
		dfs3(he, me);
	}
}

const int INF = 1e16;
void calc() {
	int ans = INF;
	for (int i=1; i<=N; i++) {
		int res = sch[i] + dp2[i] + se[i];
		int t = 0;
		for (auto p: wel[i]) t = max(t, p.S);
		t = max(t, few[i]);
		res -= t;
		ans = min(ans, res);
	}
	cout << ans << endl;
}


int32_t main() {
	IOS;
	cin >> N >> Q;
	for (int i=0; i<N-1; i++) {
		int u, v; cin >> u >> v;
		el[u].PB(v);
		el[v].PB(u);
	}


	dfs1(1, -1, 0);
	make_pfa();
	make_stamp();
	dfs2(1, -1);
	dfs3(1, -1);
	calc();


	return 0;
}

