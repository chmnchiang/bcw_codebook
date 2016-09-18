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

const int MX = 101010;
int V, E;
int did, dfn[MX], low[MX];
vector<int> el[MX];

bool dfs(int u, int fa) {
	dfn[u] = low[u] = ++did;
	for (auto v: el[u]) {
		if (v == fa) continue;
		if (!dfn[v]) {
			if (!dfs(v, u)) return false;
			low[u] = min(low[u], low[v]);
			if (low[v] > dfn[u]) {
				return false;
			}
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
	return true;
}

bool vt[MX];
int FA[MX];
int dep[MX];
int deg[MX];
vector<vector<int>> ans;
void dfs2(int u, int fa, int d) {
	vt[u] = 1;
	FA[u] = fa;
	dep[u] = d;
	for (auto v: el[u]) {
		if (!vt[v]) {
			dfs2(v, u, d+1);
		} else {
			if (dep[v] > dep[u]) {
				vector<int> vec;
				vec.PB(u);
				vec.PB(v);
				while (deg[v] == 2) {
					v = FA[v];
					if (v == -1) break;
					vec.PB(v);
				}
				deg[vec.front()] --;
				deg[vec.back()] --;
				ans.PB(vec);
			}
		}
	}
}

int main() {
	IOS;
	FILEIO("ear");
	cin >> V >> E;
	for (int i=0; i<E; i++) {
		int u, v; cin >> u >> v;
		el[u].PB(v);
		el[v].PB(u);
	}

	for (int i=1; i<=V; i++) deg[i] = SZ(el[i]);

	bool flag = dfs(1, -1);
	if (!flag) {
		cout << -1 << endl;
		return 0;
	}

	dfs2(1, -1, 0);

	cout << SZ(ans) << endl;
	for (const auto &v: ans) {
		cout<<SZ(v)-1;
		for (auto x: v) cout << ' ' << x;
		cout << endl;
	}

	return 0;
}

