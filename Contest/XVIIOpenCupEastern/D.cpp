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

using pii = pair<int,int>;
const int MAXN = 100005;
const int INF = 1029384756;

struct SegmentTree {
	int n;
	pii tree[MAXN*4];
	void init(int tn, int arr[]) {
		n = tn;
		init_tree(0,n-1,1,arr);
	}
	void init_tree(int l, int r, int id, int arr[]) {
		if (l == r) {
			tree[id] = {arr[l],l};
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		init_tree(l,m,lc,arr);
		init_tree(m+1,r,rc,arr);
		tree[id] = min(tree[lc], tree[rc]);
	}
	void update(int l, int r, int x, int v, int id) {
		if (l == r) {
			tree[id].F = v;
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		if (x <= m) update(l,m,x,v,lc);
		else update(m+1,r,x,v,rc);
		tree[id] = min(tree[lc], tree[rc]);
	}
	pii query(int l, int r, int fl, int fr, int id) {
		if (r < fl) return {INF,-1};
		if (fr < l) return {INF,-1};
		if (fl <= l and r <= fr) {
			return tree[id];
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		return min(query(l,m,fl,fr,lc), query(m+1,r,fl,fr,rc));
	}
	void upd(int x, int v) {
		update(0,n-1,x,v,1);
	}
	pii qry(int l, int r) {
		return query(0,n-1,l,r,1);
	}
} tree1, tree2;

int N,ip[MAXN],bye[MAXN],arr[MAXN];
set<int> gg;

int main() {
	IOS;
	cin>>N;
	REP1(i,1,N) cin>>ip[i];
	ip[0] = ip[N+1] = -INF;

	REP1(i,0,N+1) {
		arr[i] = ip[i] - i;
	}
	tree1.init(N+2,arr);
	REP1(i,0,N+1) {
		arr[i] = ip[i] + i;
	}
	tree2.init(N+2,arr);

	gg.insert(0);
	gg.insert(N+1);

	int Q;
	cin>>Q;
	REP(_,Q) {
		int v,cmpv,fg;
		cin>>v;
		assert(!bye[v]);

		int ans = 0;

		int l = *(--gg.lower_bound(v));
		int r = *gg.lower_bound(v);
		l++;
		r--;

		fg = 1;
		cmpv = ip[v] - v;
		while (fg and l < v) {
			auto tmp = tree1.qry(l, v-1);
			int id = tmp.S;
			if (tmp.F <= cmpv) {
				tree1.upd(id, INF);
				tree2.upd(id, INF);
				gg.insert(id);
				bye[id] = 1;
				ans++;
//				cout<<"BYE1 "<<id<<endl;
			} else {
				fg = 0;
			}
		}

		fg = 1;
		cmpv = ip[v] + v;
		while (fg and r > v) {
			auto tmp = tree2.qry(v+1, r);
			int id = tmp.S;
			if (tmp.F <= cmpv) {
				tree1.upd(id, INF);
				tree2.upd(id, INF);
				gg.insert(id);
				bye[id] = 1;
				ans++;
//				cout<<"BYE2 "<<id<<endl;
			} else {
				fg = 0;
			}
		}

		ans++;
		tree1.upd(v, INF);
		tree2.upd(v, INF);
		cout<<ans<<endl;
	}

	return 0;
}

