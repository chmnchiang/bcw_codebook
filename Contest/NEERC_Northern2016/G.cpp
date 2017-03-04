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

template<typename T>
ostream& operator <<(ostream &s, const set<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
typedef pair<int,int> pii;
const int MXN = 300005;

int N,Q,bln[MXN],cnt[MXN],isleaf[MXN];
int step,at[MXN],dep[MXN],arr[MXN];
int line[MXN],stv[MXN],edv[MXN];
vector<int> child[MXN];

struct Tree {
	int n;
	pii tree[4*MXN];
	void init(int _n) {
		n = _n;
		init_tree(0, n-1, 1);
	}
	void init_tree(int l, int r, int id) {
		if (l == r) {
			tree[id] = pii(dep[arr[l]], arr[l]);
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		init_tree(l,m,lc);
		init_tree(m+1,r,rc);
		tree[id] = min(tree[lc], tree[rc]);
	}
	pii query(int l, int r, int fl, int fr, int id) {
		if (l == fl and r == fr) return tree[id];
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		if (fr <= m) return query(l, m, fl, fr, lc);
		if (m < fl) return query(m+1, r, fl, fr, rc);
		return min(query(l, m, fl, m, lc), query(m+1, r, m+1, fr, rc));
	}
	int lca(int l, int r) {
		return query(0, n-1, l, r, 1).S;
	}
}lcaTree;
struct BIT {
	int bit[MXN];
	int lb(int x) { return x & -x; }
	void add(int x, int v) {
		x += 2;
		for (int i=x; i<MXN; i+=lb(i)) bit[i] += v;
	}
	int qry(int x) {
		x += 2;
		int r = 0;
		for (int i=x; i>0; i-=lb(i)) r += bit[i];
		return r;
	}
}bit;

void DFS1(int u, int d) {
	dep[u] = d;
	at[u] = step;
	arr[step++] = u;
	isleaf[u] = 1;
	for (auto v:child[u]) {
		isleaf[u] = 0;
		arr[step++] = u;
		DFS1(v, d+1);
	}
}
void DFS2(int u) {
	stv[u] = step;
	line[step++] = u;

	for (auto v:child[u]) {
		DFS2(v);
	}
	edv[u] = step;
	line[step++] = u;
}
void predo() {
	queue<int> que;
	for (auto v:child[0]) {
		bln[v] = v;
		que.push(v);
	}
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto v:child[u]) {
			bln[v] = bln[u];
			que.push(v);
		}
	}

	step = 0;
	for (auto v:child[0]) DFS1(v, 1);
	lcaTree.init(step);

	step = 0;
	DFS2(0);

	REP(i,N) if (isleaf[i]) bit.add(stv[i], 1);

}

set<int> st[MXN];

int query(int b) {
	if (st[b].empty()) return 0;
	int g = lcaTree.lca(*st[b].begin(), *st[b].rbegin());
	return bit.qry(edv[g]) - bit.qry(stv[g]-1);
}

void solve() {
	int ans1 = 0;
	int ans2 = 0;
	REP(i,Q) {
		string s;
		int v;
		cin >> s >> v;
		v--;

		int b = bln[v];
		if (s == "+") {
			if (cnt[b] == 0) ans1++;
			cnt[b]++;

			ans2 -= query(b);

			st[b].insert(at[v]);
			bit.add(stv[v], -1);

			ans2 += query(b);

		} else {
			if (cnt[b] == 1) ans1--;
			cnt[b]--;

			ans2 -= query(b);

			st[b].erase(at[v]);
			bit.add(stv[v], 1);

			ans2 += query(b);
		}

		cout << ans1 << " " << ans2 << "\n";
	}
}
int main() {
	IOS;
	FILEIO("gangsters");
	cin >> N >> Q;
	for (int i=1,f; i<N; i++) {
		cin >> f;
		f--;
		child[f].PB(i);
	}

	predo();
	solve();

	return 0;
}

