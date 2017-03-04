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

const int MX = 111111;

struct YY {
	struct Node {
		int tag,v;
	} tree[MX*4];
	void init(int n) {
		memset(tree,0,sizeof(Node)*n*4);
	}
	void push(int id, int lc, int rc) {
		if (tree[id].tag == 0) return;
		tree[lc].v += tree[id].tag;
		tree[lc].tag += tree[id].tag;
		tree[rc].v += tree[id].tag;
		tree[rc].tag += tree[id].tag;
		tree[id].tag = 0;
	}
	void add(int l, int r, int fl, int fr, int v, int id) {
		if (l == fl and r == fr) {
			tree[id].v += v;
			tree[id].tag += v;
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		push(id,lc,rc);
		if (fr <= m) add(l,m,fl,fr,v,lc);
		else if (m < fl) add(m+1,r,fl,fr,v,rc);
		else {
			add(l,m,fl,m,v,lc);
			add(m+1,r,m+1,fr,v,rc);
		}
		tree[id].v = max(tree[lc].v, tree[rc].v);
	}
	int qry(int l, int r, int fl, int fr, int id) {
		if (l == fl and r == fr) return tree[id].v;
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		push(id,lc,rc);
		if (fr <= m) return qry(l,m,fl,fr,lc);
		if (m < fl) return qry(m+1,r,fl,fr,rc);
		return max(qry(l,m,fl,m,lc), qry(m+1,r,m+1,fr,rc));
	}
}segtree;

struct ZZ {
	int n, val[MX];
	void init(int tn) {
		n = tn;
		fill(val, val+n, 0);
		segtree.init(n);
	}

	void add(int l, int r, int v) {
		//cout << "ADD = " << l << ' ' << r << ' ' << v << endl;
		//for (int i=l; i<=r; i++) val[i] += v;
		segtree.add(0,n-1,l,r,v,1);
	}

	int qry(int l, int r) {
		return segtree.qry(0,n-1,l,r,1);
		//cout << "QRY = " << l << ' ' << r<< endl;
		//int x = 0;
		//for (int i=l; i<=r; i++) x = max(x, val[i]);
		//assert(x == segtree.qry(0,n-1,l,r,1));
		//return x;
	}
} tree;

const int INF = 1029384756;

using pii = pair<int, int>;
int N, M;
vector<pii> ip;
vector<int> op;

int main() {
	IOS;

	int T; cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cin >> N >> M;

		ip.resize(N);
		op.resize(M+1);
		for (int i=0; i<N; i++) {
			cin >> ip[i].F >> ip[i].S;
		}

		sort(ALL(ip), [](pii p1, pii p2) { return p1.S < p2.S; });

		op[0] = -INF;

		for (int i=0; i<M; i++) cin >> op[i+1];
		sort(ALL(op));

		tree.init(M+5);

		int j = 0;
		for (int i=1; i<=M; i++) {
			int x = op[i];
			while (j < N and ip[j].S < x) {
				int k = lower_bound(ALL(op), ip[j].F) - op.begin() - 1;
				tree.add(0, k, 1);
				j++;
			}

			int r = tree.qry(0, i-1) + 1;
			tree.add(i, i, r);
		}

		while (j < N) {
			int k = lower_bound(ALL(op), ip[j].F) - op.begin() - 1;
			tree.add(0, k, 1);
			j++;
		}

		int ans = tree.qry(1, M);
		cout << "Case #" << cas << ": ";
		if (ans > N) {
			cout << "IMPOSSIBLE!" << endl;
		} else {
			cout << ans << endl;
		}
	}

	return 0;
}

