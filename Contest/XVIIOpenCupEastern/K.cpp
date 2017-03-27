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
using LL = long long;
using pii = pair<int,int>;
const int MAXN = 100005;
const int MAX = 2500005;
const LL MD = 1000000007;

struct Item {
	int ll, l, r;
};
ostream& operator << (ostream &s, Item a) {
	return s<<"{["<<a.ll<<","<<a.l<<"], "<<a.r<<"}";
}

int N,ip[MAXN];
vector<Item> gcd[MAX];

/*
int check[1024][1024];
void validate_gcd() {
	REP(v,MAX) {
		for (auto it:gcd[v]) {
			int ll = it.ll;
			int l = it.l;
			int r = it.r;
			REP1(i,ll,l) {
				int vv = 0;
				REP1(j,i,r) vv = __gcd(vv, ip[j]);
				assert(vv == v);
				check[i][r] = 1;
			}
		}
	}
	REP1(i,1,N) {
		REP1(j,i+1,N) {
			assert(check[i][j]);
		}
	}
}
*/
void build_gcd() {
	vector<pair<pii,int>> vec;
	REP1(i,1,N) {
		for (auto &it: vec) {
			it.S = __gcd(it.S, ip[i]);
		}
		vec.PB({{i,i}, ip[i]});

		vector<pair<pii,int>> v2;
		int sz = SZ(vec);
		REP(j,sz) {
			int k = j;
			while (k < sz and vec[k].S == vec[j].S) k++;
			k--;
			v2.PB({{vec[j].F.F,vec[k].F.S}, vec[j].S});
			j = k;
		}
		vec = v2;
		for (auto it:vec) {
			gcd[it.S].PB({it.F.F, it.F.S, i});
		}
	}
//	validate_gcd();
}
struct SegmentTree {
	int inv[4*MAXN];
	vector<int> vec;
	struct Node {
		LL val, tag;
	} tree[4*MAXN];

	void init() {
		for (auto i:vec) {
			tree[i] = {0,0};
			inv[i] = 0;
		}
		vec.clear();

	}

	void push(int l, int m, int r, int id, int lc, int rc) {
		if (!tree[id].tag) return;
		(tree[lc].tag += tree[id].tag) %= MD;
		(tree[lc].val += 1LL * (m-l+1) * tree[id].tag) %= MD;
		if (!inv[lc]) {
			inv[lc] = 1;
			vec.PB(lc);
		}

		(tree[rc].tag += tree[id].tag) %= MD;
		(tree[rc].val += 1LL * (r-m) * tree[id].tag) %= MD;
		if (!inv[rc]) {
			inv[rc] = 1;
			vec.PB(rc);
		}

		tree[id].tag = 0;
	}

	void upd(int l, int r, int fl, int fr, LL v, int id) {
		if (fr < l) return;
		if (r < fl) return;
		if (fl <= l and r <= fr) {
			(tree[id].tag += v) %= MD;
			(tree[id].val += 1LL * v * (r - l + 1)) %= MD;

			if (!inv[id]) {
				inv[id] = 1;
				vec.PB(id);
			}
			return;
		}
		int m = (l + r) / 2, lc = id * 2, rc = id * 2 + 1;
		push(l,m,r,id,lc,rc);
		upd(l,m,fl,fr,v,lc);
		upd(m+1,r,fl,fr,v,rc);

		tree[id].val = tree[lc].val + tree[rc].val;
		if (tree[id].val >= MD) tree[id].val -= MD;
		if (!inv[id]) {
			inv[id] = 1;
			vec.PB(id);
		}
	}
	LL query(int l, int r, int fl, int fr, int id) {
		if (l == fl and r == fr) return tree[id].val;

		int m = (l+r)/2, lc = id * 2, rc = id * 2 + 1;
		push(l,m,r,id,lc,rc);

		if (fr <= m) return query(l,m,fl,fr,lc);
		if (m < fl) return query(m+1,r,fl,fr,rc);
		int res = query(l,m,fl,m,lc) + query(m+1,r,m+1,fr,rc);
		if (res >= MD) res -= MD;
		return res;
	}
	void add(int l, int r, int v) {
		upd(0,N+3,l,r,v,1);
	}
	LL qry(int l, int r) {
		return query(0,N+3,l,r,1);
	}


} ws360;

struct Tree {
	int val[MAXN];
	void init(int n) {
		//memset(val, 0, sizeof(val));
		ws360.init();
	}

	int qry(int l, int r) {
		return ws360.qry(l,r);
		assert(l <= r);
		int res = 0;
		for (int i=l; i<=r; i++) {
			(res += val[i]) %= MD;
		}
		assert(res == ws360.qry(l,r));
		return res;
	}

	void add(int l, int r, int v) {
		ws360.add(l,r,v);
		return;
		for (int i=l; i<=r; i++) {
			(val[i] += v) %= MD;
		}
	}
} tree;

bool itemcmp(const Item &i1, const Item &i2) {
	return i1.r < i2.r;
}

vector<int> mv;
inline int vl(int id) {
	return upper_bound(ALL(mv), id) - mv.begin() - 1;
}

int ansVal, ansCnt;

void calc(int g) {
	auto &vec = gcd[g];
	if (!SZ(vec)) return;

	tree.init(N+2);

	mv.clear();
	int nw = 0;
	mv.PB(nw);
	for (auto it: vec) {
		if (it.l > nw) {
			nw = it.r;
			mv.PB(nw);
		}
	}

	mv.PB(N+1);
	tree.add(0, mv[1]-1, 1);

	//cout << "MV = " << mv << endl;

	//cout << "VEC = " << vec << endl;
	//for (int i=0; i<=N; i++) {
	//	cout << tree.val[i] << ' ';
	//}
	//cout << endl;

	for (auto it: vec) {
		int r = it.r, l = it.l;

		int vall = vl(l-1), valr = vl(r);
		assert(vall != valr);

		if (vall < valr-1) continue;

		int t = mv[vall];
		int ll = max(it.ll-1, t);
		int way = tree.qry(ll, l-1);
		//cout << "QRY = " << ll << ' ' << l-1 << endl;
		tree.add(r, mv[valr+1] - 1, way);

		//for (int i=0; i<=N; i++) {
		//	cout << tree.val[i] << ' ';
		//}
		//cout << endl;

	}

	//	cout << "GCD = " << g << ": ";
	//	cout << SZ(mv)-2 << ' ';
	//	cout << tree.val[N] << endl;

	int ansval = SZ(mv)-2;
	if (ansVal == ansval) {
		ansCnt += tree.qry(N, N);
		if (ansCnt >= MD) ansCnt -= MD;
	} else if (ansVal < ansval) {
		ansVal = ansval;
		ansCnt = tree.qry(N, N);
	}
}

int32_t main() {
	IOS;
	cin>>N;
	int MX = 0;
	REP1(i,1,N) {
		cin>>ip[i];
		MX = max(MX, ip[i]);
	}
	build_gcd();
	for (int i=1; i<=MX; i++) {
		calc(i);
	}


	cout << ansVal << ' ' << ansCnt << endl;
	return 0;
}

