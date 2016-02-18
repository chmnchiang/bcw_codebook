//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

#include <bits/extc++.h>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

typedef pair<int,int> pii;
const int MXN = 100005;

int N,ip[MXN];
int step,seq[MXN];
pii seg[MXN];
vector<int> E[MXN];

struct BSP1 {
  struct Node {
    int c,tag;
  }tree[MXN*4];
  int n;
  void init(int _n) {
    n = _n;
    REP(i,MXN*4) tree[i] = {0,0};
  }
  void push(int id, int lc, int rc) {
    if (!tree[id].tag) return;
    tree[lc] = tree[rc] = {tree[id].tag, tree[id].tag};
    tree[id].tag = 0;
  }
  void update_tree(int l, int r, int fl, int fr, int c, int id) {
    if (l == fl && r == fr) {
      tree[id] = {c, c};
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id, lc, rc);
    if (fr <= m) {
      update_tree(l, m, fl, fr, c, lc);
    } else if (m < fl) {
      update_tree(m+1, r, fl, fr, c, rc);
    } else {
      update_tree(l, m, fl, m, c, lc);
      update_tree(m+1, r, m+1, fr, c, rc);
    }
  }
  int query_tree(int l, int r, int x, int id) {
    if (l == r) return tree[id].c;
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id, lc, rc);
    if (x <= m) return query_tree(l, m, x, lc);
    return query_tree(m+1, r, x, rc);
  }
  void update(int l, int r, int c) {
    update_tree(1,n,l,r,c,1);
  }
  int query(int p) {
    return query_tree(1,n,p,1);
  }
}color_bsp;
struct BSP2 {
  int n;
  ll tree[MXN*4];
  vector<int> bye;
  void init(int _n) {
    n = _n;
    REP(i,MXN*4) tree[i] = 0;
  }
  void update_tree(int l, int r, int x, int c, int id) {
    if (l == r) {
      tree[id] = c;
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    if (x <= m) update_tree(l,m,x,c,lc);
    else update_tree(m+1,r,x,c,rc);
    tree[id] = tree[lc] + tree[rc];
  }
  void query_tree(int l, int r, int fl, int fr, int id) {
    if (!tree[id]) return;
    if (fr < l || fl > r) return;
    if (l == r) {
      bye.PB(l);
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    query_tree(l,m,fl,fr,lc);
    query_tree(m+1,r,fl,fr,rc);
  }
  void update(int x, int c) {
    update_tree(1,n,x,c,1);
  }
  vector<int> query(int l, int r) {
    bye.clear();
    query_tree(1,n,l,r,1);
    return bye;
  }
}tag_bsp;
struct BIT {
  set_t bit[MXN];
  void init() {
    REP(i,MXN) bit[i].clear();
  }
  int lb(int a) { return a & -a; }
  void del(int x, int v) {
    for (int i=x; i<MXN; i+=lb(i)) {
      assert(bit[i].order_of_key(v) != bit[i].order_of_key(v+1));
      bit[i].erase(v);
    }
  }
  void add(int x, int v) {
    for (int i=x; i<MXN; i+=lb(i)) {
      assert(bit[i].order_of_key(v) == bit[i].order_of_key(v+1));
      bit[i].insert(v);
    }
  }
  int query(int x, int v) {
    int res = 0;
    for (int i=x; i>0; i-=lb(i)) {
      res += SZ(bit[i]) - bit[i].order_of_key(v+1);
    }
    return res;
  }
};
struct ColorSet {
  BIT bit;
  set<int> col[MXN];
  void init() {
    bit.init();
    REP(i,MXN) col[i].clear();
  }
  int prv(int x, int c) {
    auto it = col[c].lower_bound(x);
    if (it == begin(col[c])) return -1;
    it--;
    return *it;
  }
  int nxt(int x, int c) {
    auto it = col[c].upper_bound(x);
    if (it == end(col[c])) return MXN+c;
    return *it;
  }
  void add(int x, int c) {
    assert(!col[c].count(x));
    int a = prv(x, c);
    int b = nxt(x, c);
    if (a != -1) {
      bit.del(a, b);
      bit.add(a, x);
    }
    bit.add(x, b);
    col[c].insert(x);
  }
  void del(int x, int c) {
    assert(col[c].count(x));
    int a = prv(x, c);
    int b = nxt(x, c);
    bit.del(x, b);
    if (a != -1) {
      bit.del(a, x);
      bit.add(a, b);
    }
    col[c].erase(x);
  }
  int query(int l, int r) {
//    cout << bit.query(r,r) << " " << bit.query(l-1,r) << endl;
    return bit.query(r, r) - bit.query(l-1, r);
  }
}cs;

void init_all() {
  REP(i,MXN) E[i].clear();
}
void input() {
  cin >> N;
  REP(i,N-1) {
    int u,v;
    cin >> u >> v;
    E[u].PB(v);
    E[v].PB(u);
  }
  REP1(i,1,N) {
    cin >> ip[i];
  }
}
void DFS(int u, int f) {
  seq[++step] = u;
  seg[u].F = step;
  for (auto v:E[u]) {
    if (v == f) continue;
    DFS(v, u);
  }
  seg[u].S = step;
}
void predo() {
  step = 0;
  DFS(1,1);
  assert(step == N);
  color_bsp.init(N);
  tag_bsp.init(N);
  cs.init();
  REP1(i,1,step) {
    int v = seq[i];
    color_bsp.update(i,i,ip[v]);
    tag_bsp.update(i,ip[v]);
    cs.add(i,ip[v]);
  }
}
void update_colors(int l, int r, int c) {
  vector<int> bye = tag_bsp.query(l, r);
  for (auto it:bye) {
    cs.del(it, color_bsp.query(it));
    tag_bsp.update(it, 0);
  }
  color_bsp.update(l, r, c);
  tag_bsp.update(l, c);
  cs.add(l, c);
}
int query_colors(int l, int r) {
  int res = cs.query(l, r);
  int mycol = color_bsp.query(l);
//  cout << l << " " << r << " " << mycol << endl;
//  cout << cs.nxt(l-1,mycol) << endl;
  if (cs.nxt(l-1, mycol) > r) res++;
  return res;
}
void solve() {
//  REP1(i,1,N) cout << seq[i] << " ";
//  cout << endl;
  int Q, t, u, c;
  cin >> Q;
  REP(q,Q) {
//    REP1(i,1,N) {
//      cout << "col[" << i << "] : " << cs.col[i] << endl;
//    }
    cin >> t >> u;
    if (t == 0) {
      cin >> c;
      update_colors(seg[u].F, seg[u].S, c);
    } else {
      cout << query_colors(seg[u].F, seg[u].S) << "\n";
    }
  }
}
int main(int argc, char** argv) {
  IOS;
  int ts;
  cin >> ts;
  REP1(cas,1,ts) {
    cout << "Case #" << cas << ":\n";
    init_all();
    input();
    predo();
    solve();
  }

  return 0;
}

