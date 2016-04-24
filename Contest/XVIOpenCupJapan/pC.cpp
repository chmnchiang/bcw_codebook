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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

#define int long long
typedef pair<int,int> pii;

pii operator + (const pii a, const pii b) { return pii(a.F+b.F,a.S+b.S); }
const int MX = 201010;

struct Tree {
	static const int MN = MX*2;
	int V[2][MN];
	int N;
	struct Node {
		int A,B,dot;
		pii tag;
		Node () {
			A = B = dot = 0;
			tag = pii(0,0);
		}
	}tree[4*MN];

	void init(int n) {
		FZ(V[0]);
		FZ(V[1]);
		N = n;
		REP(i,4*MN) tree[i] = Node();
	}
	void push(int id, int l, int r) {
		if (!tree[id].tag.F and !tree[id].tag.S) return;
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		pii &v = tree[id].tag;
		tree[lc].dot += tree[lc].A * v.S + tree[lc].B * v.F + (m-l+1) * v.F * v.S;
		tree[lc].A += (m-l+1) * v.F;
		tree[lc].B += (m-l+1) * v.S;
		tree[lc].tag = tree[lc].tag + v;
		tree[rc].dot += tree[rc].A * v.S + tree[rc].B * v.F + (r-m) * v.F * v.S;
		tree[rc].A += (r-m) * v.F;
		tree[rc].B += (r-m) * v.S;
		tree[rc].tag = tree[rc].tag + v;
		v = pii(0,0);
	}
	void update_tree(int l, int r, int fl ,int fr, pii v, int id) {
		if (l == fl and r == fr) {
			tree[id].tag = tree[id].tag + v;
			tree[id].dot += tree[id].A * v.S + tree[id].B * v.F + (r-l+1) * v.F * v.S;
			tree[id].A += (r-l+1) * v.F;
			tree[id].B += (r-l+1) * v.S;
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		push(id,l,r);
		if (fr <= m) update_tree(l,m,fl,fr,v,lc);
		else if (m < fl) update_tree(m+1,r,fl,fr,v,rc);
		else {
			update_tree(l,m,fl,m,v,lc);
			update_tree(m+1,r,m+1,fr,v,rc);
		}
		tree[id].A = tree[lc].A + tree[rc].A;
		tree[id].B = tree[lc].B + tree[rc].B;
		tree[id].dot = tree[lc].dot + tree[rc].dot;
	}

	// [l, r)
	void update(int t, int l, int r, int v) {
		pii x(0,0);
		if (t) x.S = v;
		else x.F = v;
		update_tree(0,N,l,r-1,x,1);
		//for (int i=l; i<r; i++) V[t][i]+=v;
	}

	int query() {
		return tree[1].dot;
		int res = 0;
		for (int i=0; i<N; i++) {
			res += V[0][i] * V[1][i];
		}
		assert(res == tree[1].dot);
		return res;
	}

	void dump() {
		return;
		for (int i=0; i<N; i++) cout << V[0][i] << ' '; cout << endl;
		for (int i=0; i<N; i++) cout << V[1][i] << ' '; cout << endl;
	}
};

int N, Q;
Tree tree;
int D[MX];
using pii=pair<int,int>;
vector<pii> ip;
vector<int> in[MX], out[MX];
int res;

int cost(int i, int j) {
	assert(j > i);
	return D[j] - D[i];
}

void pre(int a) {
	for (auto x: in[a]) {
		tree.update(1, a, x, -1);
		//cout << "- " << a << " <- " << x << endl;
		//cout << cost(a, x) << endl;
		res -= cost(a, x);
	}
	for (auto x: out[a]) {
		tree.update(0, a, x, -1);
		//cout << "- " << a << " -> " << x << endl;
		//cout << cost(a, x) << endl;
		res -= cost(a, x);
	}
}
void post(int a) {
	for (auto x: in[a]) {
		tree.update(0, x, N+a, 1);
		res += cost(x, N+a);
		//cout << "+ " << a << " <- " << x << endl;
	}
	for (auto x: out[a]) {
		tree.update(1, x, N+a, 1);
		res += cost(x, N+a);
	//	cout << "+ " << a << " -> " << x << endl;
	}
	//cout << "after post res = " << res << endl;
}

bool isok(int t, int l, int r) {
	tree.update(t, l, r, 1);
	int ret = !tree.query();
	tree.update(t, l, r, -1);
	return ret;
}

int32_t main() {
	IOS;
	cin>>N>>Q;
	for (int i=0; i<N; i++) {
		int t; cin>>t;
		D[i+1] = D[i+N+1] = t;
	}
	for (int i=1; i<=N*2; i++) D[i] += D[i-1];


	tree.init(2*N+5);
	ip.resize(Q);
	int s1, s2; s1=s2=0;
	loop(i, 0, Q) {
		int s, t; cin>>s>>t;
		ip[i] = pii{s, t};
		int c1 = (t < s ? cost(s, t+N) : cost(s, t));
		int c2 = (t < s ? cost(t, s) : cost(t, s+N));
		s1+=c1; s2+=c2;
		in[t].PB(s < t ? s+N : s);
		out[s].PB(t < s ? t+N : t);
		res += (s < t ? cost(s, t) : cost(t, s));

		if (s < t) tree.update(0, s, t, 1);
		else tree.update(1, t, s, 1);
	}
	int ans = min(s1, s2);

	loop(i, 0, N) {
		pre(i);
		//cout << "val = " << tree.query() << endl;
		tree.dump();
		if (!tree.query()) {
			if (!SZ(in[i]) or !SZ(out[i])) {
				auto &vec = (SZ(in[i]) ? in[i] : out[i]);
				int typ = !!SZ(in[i]);

				int xres = res;
				bool flag = true;
				for (auto x: vec) {
					int c1 = cost(i, x);
					int c2 = cost(x, N+i);
					bool ok1 = isok(typ, i, x),
						 ok2 = isok(!typ, x, i+N);
					if (!ok1 and !ok2) {
						flag=0; break;
					} else if (!ok1) {
						xres += c2;
					} else if (!ok2) {
						xres += c1;
					} else {
						xres += min(c1, c2);
					}
				}
				if (flag) ans=min(ans, xres);
			}
		}

		post(i);
	}
	cout << ans << endl;
	

	return 0;
}

