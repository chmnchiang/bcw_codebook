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
// Let's Fight!

#define REP(i,x) for(int i=0; i<(x); i++)
#define REP1(i,a,b) for(int i=(a); i<=(b); i++)

typedef int ll;
const int MX = 100005;
const int LOG = 17;
const ll MINF = -2147483648;

struct Query {
	int l,r;
	ll v;
}qry[MX];

ll N,Q,s[MX];
ll rmq[LOG][MX];
ll tree[MX*4];

void init_tree(int l, int r, int id) {
	tree[id]=MINF;
	if (l == r) {
		return;
	}
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	init_tree(l,m,lc);
	init_tree(m+1,r,rc);
}
void update(int l, int r, int fl, int fr, int v, int id) {
	if (l == fl && r == fr) {
		tree[id] = max(tree[id], v);
		return;
	}
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	if (fr <= m) return update(l, m, fl, fr, v, lc);
	if (m < fl) return update(m+1, r, fl, fr, v, rc);
	update(l, m, fl, m, v, lc);
	update(m+1, r, m+1, fr, v, rc);
}
void query(int l, int r, int fn, int id, ll &ans) {
	ans = max(ans, tree[id]);
	if (l == r) return;
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	if (fn <= m) query(l, m, fn, lc, ans);
	else query(m+1, r, fn, rc, ans);
}
void build() {
	REP1(i,1,N) rmq[0][i] = s[i];
	REP1(i,1,LOG-1) {
		for (int j=0; j+(1<<i)-1<=N; j++) {
			rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
		}
	}
}
ll query(int l, int r) {
	int len=r-l+1;
	int i=31-__builtin_clz(len);
	return min(rmq[i][l], rmq[i][r-(1<<i)+1]);
}
void check() {
	REP(i,Q) {
		if (query(qry[i].l, qry[i].r) != qry[i].v) {
			cout << "inconsistent" << endl;
			exit(0);
		}
	}
}
int main() {
	IOS;
	FILEIO("rmq");
	cin >> N >> Q;
	REP(i,Q) cin>> qry[i].l >> qry[i].r >> qry[i].v;
	init_tree(1, N, 1);
	REP(i,Q) {
		update(1, N, qry[i].l, qry[i].r, qry[i].v, 1);
	}
	REP1(i,1,N) {
		s[i] = MINF;
		query(1, N, i, 1, s[i]);
	}

	build();
	check();

	cout << "consistent\n";
	REP1(i,1,N) {
		cout << s[i] << " \n"[i==N];
	}

	return 0;
}

