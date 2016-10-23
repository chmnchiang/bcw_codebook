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

typedef pair<int,int> pii;
const int MXN = 2005;

struct Tree{
	int n, label[MXN], sz[MXN];
	vector<int> child[MXN], sum[MXN];
	vector<pii> eid;
	void init() {
		REP(i,MXN) {
			child[i].clear();
		}
		eid.clear();
		n = 0;
	}
	int add_node(int x) {
		label[n] = x;
		return n++;
	}
	void add_edge(int u, int v) {
		child[u].PB(v);
	}
	void DFS(int u) {
		sz[u] = 1;
		for (auto v:child[u]) {
			DFS(v);
			sz[u] += sz[v];
		}
	}
	void build() {
		eid.clear();
		REP(i,n) REP1(j,0,SZ(child[i]))
			eid.PB({i,j});
		sort(ALL(eid));
		DFS(0);
		REP(i,n) {
			sum[i].resize(SZ(child[i])+1);
			int szz = SZ(sum[i]);
			sum[i][szz-1] = 0;
			for (int j=szz-2; j>=0; j--) {
				sum[i][j] = sum[i][j+1] + sz[child[i][j]];
			}
		}
	}
	int getid(int x, int i) {
		int j = lower_bound(ALL(eid), pii(x,i)) - begin(eid);
		assert(j < SZ(eid) and eid[j] == pii(x,i));
		return j;
	}
	void print() {
		cout << "TREE with " << n << " node(s).\n";
		REP(i,n) cout << "LABEL[" << i << "] : " << char(label[i]) << endl;
		REP(i,n) cout << "CHILD[" << i << "] : " << child[i] << endl;
		cout << eid << endl;
	}
}tree1, tree2;

int parse(string &s, int &pos, Tree &tree) {
	assert(pos < SZ(s));
	assert(s[pos] == '(');
	pos++;
	int id = tree.add_node((int)s[pos]);
	pos++;
	while (s[pos] != ')') {
		int son = parse(s, pos, tree);
		tree.add_edge(id, son);
	}
	pos++;
	return id;
}

int dpv[MXN][MXN], dpe[MXN][MXN];

int gov(int, int);
int goe(int, int);

int gov(int a, int b) {
	int &res = dpv[a][b];
	if (res != -1) return res;
	res = 0;
	if (tree1.label[a] != tree2.label[b]) {
		res = 1;
	}
	if (tree1.child[a].empty()) {
		res += tree2.sz[b] - 1;
		return res;
	}
	if (tree2.child[b].empty()) {
		res += tree1.sz[a] - 1;
		return res;
	}
	int na = tree1.getid(a, 0);
	int nb = tree2.getid(b, 0);
	res += goe(na, nb);
	return res;
}
int goe(int a, int b) {
	int &res = dpe[a][b];
	if (res != -1) return res;
	int x = tree1.eid[a].F;
	int i = tree1.eid[a].S;
	int y = tree2.eid[b].F;
	int j = tree2.eid[b].S;
	if (i == SZ(tree1.child[x])) {
		return res = tree2.sum[y][j];
	}
	if (j == SZ(tree2.child[y])) {
		return res = tree1.sum[x][i];
	}
	int u = tree1.child[x][i];
	int v = tree2.child[y][j];
	res = gov(u, v) + goe(tree1.getid(x,i+1), tree2.getid(y,j+1));
	res = min(res, tree1.sz[u] + goe(tree1.getid(x,i+1), tree2.getid(y,j)));
	res = min(res, tree2.sz[v] + goe(tree1.getid(x,i), tree2.getid(y,j+1)));
	return res;
}

int main() {
	IOS;
	int TTTTT;
	cin >> TTTTT;
	while (TTTTT--) {
		string s1, s2;
		cin >> s1 >> s2;
		tree1.init();
		tree2.init();
		int pos = 0;
		int a = parse(s1, pos, tree1);
		assert(pos == SZ(s1));
		pos = 0;
		int b = parse(s2, pos, tree2);
		assert(pos == SZ(s2));

		tree1.build();
		tree2.build();

		REP(i,tree1.n) REP(j,tree2.n)
			dpv[i][j] = -1;
		REP(i,SZ(tree1.eid)) REP(j,SZ(tree2.eid))
			dpe[i][j] = -1;

		int ans = gov(a, b);
		cout << ans << endl;
	}

    return 0;
}

