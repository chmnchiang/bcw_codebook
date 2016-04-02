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
typedef pair<ll,ll> pll;
const int MXN = 200005;
const ll INF = 1e15;

struct Lisan {
	vector<int> seq;
	void add(int x) { seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int qry(int x) {
		return lower_bound(ALL(seq),x)-begin(seq)+1;
	}
}lisan;
struct SegmentTree {
	struct Node {
		pll mn;
		ll tag;
	}tree[MXN*4];
	int n;
	void init(int _n) {
		n = _n;
		init(1,n,1);
	}
	void init(int l, int r, int id) {
		tree[id] = {{0,0},0};
		if (l == r) {
			tree[id].mn.S = l;
			return;
		}
		int m=(l+r)/2, lc=id*2, rc=id*2+1;
		init(l,m,lc);
		init(m+1,r,rc);
	}
	void push(int id, int lc, int rc) {
		if (tree[id].tag == 0) return;
		tree[lc].mn.F += tree[id].tag;
		tree[lc].tag += tree[id].tag;
		tree[rc].mn.F += tree[id].tag;
		tree[rc].tag += tree[id].tag;
		tree[id].tag = 0;
	}
	void update(int l, int r, int fl, int fr, ll v, int id) {
		if (l == fl and r == fr) {
			tree[id].mn.F += v;
			tree[id].tag += v;
			return;
		}
		int m=(l+r)/2, lc=id*2, rc=id*2+1;
		push(id,lc,rc);
		if (fr <= m) update(l,m,fl,fr,v,lc);
		else if (m < fl) update(m+1,r,fl,fr,v,rc);
		else {
			update(l,m,fl,m,v,lc);
			update(m+1,r,m+1,fr,v,rc);
		}
		tree[id].mn = min(tree[lc].mn, tree[rc].mn);
	}
	Node query(int l, int r, int fl, int fr, int id) {
		if (l == fl and r == fr) return tree[id];
		int m=(l+r)/2, lc=id*2, rc=id*2+1;
		push(id,lc,rc);
		if (fr <= m) return query(l,m,fl,fr,lc);
		if (m < fl) return query(m+1,r,fl,fr,rc);
		Node res = query(l,m,fl,m,lc);
		Node tmp = query(m+1,r,m+1,fr,rc);
		res.mn = min(res.mn, tmp.mn);
		return res;
	}
	void add(int l, int r, ll v) {
		assert(l <= r);
		update(1,n,l,r,v,1);
	}
	pll qry(int l, int r) {
		return query(1,n,l,r,1).mn;
	}
}tree;
struct Segment {
	int a,b,t;
}ip[MXN];

int N,minb,maxa;
ll cost[MXN];
int mnR[MXN];
vector<Segment> segl[MXN],segr[MXN];

int main() {
	IOS;
	FILEIO("lamps");
	cin >> N;
	REP1(i,1,N) {
		cin >> ip[i].a >> ip[i].b >> ip[i].t;
		ip[i].a *= 2;
		ip[i].b = ip[i].b * 2 + 1;
		lisan.add(ip[i].a);
		lisan.add(ip[i].b);
	}
	lisan.build();
	int rn = SZ(lisan.seq);
	minb = rn;
	maxa = 0;
	REP1(i,1,N) {
		ip[i].a = lisan.qry(ip[i].a);
		ip[i].b = lisan.qry(ip[i].b);
		maxa = max(maxa, ip[i].a);
		minb = min(minb, ip[i].b);
		segl[ip[i].a].PB(ip[i]);
		segr[ip[i].b].PB(ip[i]);
	}

	mnR[rn+1] = rn;
	for (int i=rn; i>=1; i--) {
		mnR[i] = mnR[i+1];
		for (auto it:segl[i])
			mnR[i] = min(mnR[i], it.b);
	}

//	REP1(i,1,rn) cout << i << " : " << cost[i] << endl;
	tree.init(rn);
	REP1(l,1,rn) {
		for (auto it:segl[l]) {
			tree.add(it.a,it.b,it.t);
		}
		for (auto it:segr[l]) {
			tree.add(it.a,it.b,-it.t);
		}
		cost[l] = tree.qry(l,l).F;
		/*
		ll tmp = 0;
		REP1(j,1,N) {
			if (ip[j].a <= l and l < ip[j].b) tmp += ip[j].t;
		}
		cout << lisan.seq[l-1] << " " << cost[l] << " " << tmp << endl;
		assert(tmp == cost[l]);
		*/
	}

	tree.init(rn);
	REP1(i,1,rn) tree.add(i,i,cost[i]);
	tree.add(maxa,rn,INF);
	tree.add(1,minb-1,INF);
	//cout << "START" << endl;
	ll bestC = INF;
	ll bestL = -1;
	ll bestR = -1;
	REP1(l,0,rn) {
		for (auto it:segl[l]) {
			tree.add(it.a,it.b-1,-it.t);
		}
		if (l < minb) continue;
		pll tmp = tree.qry(mnR[l+1],rn);
		ll costr = tmp.F;
		int r = tmp.S;
		ll c = cost[l] + costr;
		//cout << l << " " << r << " " << c << endl;
		if (c < bestC) {
			tie(bestL,bestR,bestC) = tie(l,r,c);
		}
	}
	//cout << "END WITH " << bestL << " " << bestR << " " << bestC << endl;

	if (bestL == -1) {
		cout << -1 << endl;
	} else {
		ll c = 0;
		vector<int> ans;
		REP1(i,1,N) {
			if ((ip[i].a <= bestL and bestL < ip[i].b) or
				(ip[i].a <= bestR and bestR < ip[i].b)) {
				ans.PB(i);
				c += ip[i].t;
			}
		}
//		cout << "CALC " << c << endl;
		assert(c == bestC);
		cout << c << endl;
		cout << SZ(ans) << endl;
		for (auto id:ans) cout << id << " ";
		cout << endl;
	}

	return 0;
}

