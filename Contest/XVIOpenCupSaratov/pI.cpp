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
#define REP(i,n) for (int i=0;i<(n);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MXN = 300005;
const int INF = 1029384756;

struct BSP {
	int n;
	int tree[4*MXN];
	void init(int _n) {
		n = _n;
		REP(i,4*MXN) tree[i] = -INF;
	}
	void update(int l, int r, int fn , int v, int id) {
		if (l == r) {
			tree[id] = v;
			return;
		}
		int m=(l+r)/2, lc=id*2, rc=id*2+1;
		if (fn <= m) update(l, m, fn, v, lc);
		else update(m+1, r, fn, v, rc);
		tree[id] = min(tree[lc], tree[rc]);
	}
	int query(int l, int r, int v, int id) {
		if (l == r) return l;
		int m=(l+r)/2, lc=id*2, rc=id*2+1;
		if (tree[lc] < v) return query(l, m, v, lc);
		return query(m+1, r, v, rc);
	}
	void update(int c, int v) {
		update(1,n,c,v,1);
	}
	int query(int x) {
		return query(1,n,x,1);
	}
}tree;

int N,lt[MXN],ans[MXN];
int main() {
	IOS;
	cin >> N;
	REP1(i,1,N) lt[i] = i-1;
	REP1(i,1,N) {
		int m, v;
		cin >> m;
		while (m--) {
			cin >> v;
			lt[v] = min(lt[v], i);
		}
	}
	ans[1] = 1;
	tree.init(N);
	tree.update(1, 1);
	REP1(i,2,N) {
//		cout << "#" << i << " " << lt[i] << endl;
		ans[i] = tree.query(lt[i]+1);
		tree.update(ans[i], i);
	}
	REP1(i,1,N)
		cout << ans[i] << " \n"[i == N];


    return 0;
}
