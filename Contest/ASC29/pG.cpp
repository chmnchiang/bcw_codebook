//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
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

const int MXN = 100005;

struct SegmentTree {
  int n;
  pii tree[4*MXN];
  vector<int> sp;
  vector<pair<int*,int>> h;
  void init(int _n) {
    n = _n;
    REP(i,4*MXN) tree[i] = {0,0};
    sp.clear();
    h.clear();
  }
  void save() {
    sp.PB(SZ(h));
  }
  void undo() {
    assert(!sp.empty());
    while (SZ(h) != sp.back()) {
      auto x=h.back(); h.pop_back();
      *x.F=x.S;
    }
    sp.pop_back();
  }
  void assign(int *k, int v) {
    h.PB({k, *k});
    *k=v;
  }
  void upd_tree(int l, int r, int fl, int fr, pii v, int id) {
    if (l == fl && r == fr) {
      if (tree[id] < v) {
        assign(&tree[id].F, v.F);
        assign(&tree[id].S, v.S);
      }
      return;
    }
    int m=(l+r)/2, lc=id*2, rc=id*2+1;
    if (fr <= m) upd_tree(l, m, fl, fr, v, lc);
    else if (m < fl) upd_tree(m+1, r, fl, fr, v, rc);
    else {
      upd_tree(l, m, fl, m, v, lc);
      upd_tree(m+1, r, m+1, fr, v, rc);
    }
  }
  void qry_tree(int l, int r, int fn, pii &res, int id) {
    res = max(res, tree[id]);
    if (l == r) return;
    int m=(l+r)/2, lc=id*2, rc=id*2+1;
    if (fn <= m) qry_tree(l, m, fn, res, lc);
    else qry_tree(m+1, r, fn, res, rc);
  }
  void update(int l, int r, pii v) {
    upd_tree(0,n,l,r,v,1);
  }
  int query(int x) {
    pii res;
    qry_tree(0,n,x,res,1);
    return res.S;
  }
}seg;
struct Event {
  int s,t,c,x;
  friend ostream& operator << (ostream &out, const Event &he) {
    out << "[";
    out << he.s << " -> " << he.x << " -> " << he.t << " : " << he.c;
    out << "]";
    return out;
  }
};
struct Tree {
  int rt,step,st[MXN],ed[MXN],flow[MXN];
  vector<pii> child[MXN];
  void init(int r) {
    rt = r;
    REP(i,MXN) child[i].clear();
    REP(i,MXN) flow[i] = 0;
  }
  void DFS(int u) {
    st[u] = step++;
    for (auto it:child[u]) DFS(it.F);
    ed[u] = step-1;
  }
  void yabian() {
    step = 0;
    DFS(rt);
  }
  int calc(int u, int ans[]) {
    int res = flow[u];
    for (auto it:child[u]) {
      int tmp = calc(it.F, ans);
      ans[it.S] += tmp;
      res += tmp;
    }
    return res;
  }
  void calc(int ans[]) {
    calc(rt, ans);
  }
}tree1,tree2;

int A,B,N,M,ip[MXN],ans[MXN];
int vst[MXN];
vector<pii> E[MXN],rE[MXN];
vector<Event> event;
vector<int> qid[MXN];

void build_event() {
  vector<pii> v1,v2;
  REP1(i,1,A) v1.PB({i,ip[i]});
  REP1(i,A+1,N) v2.PB({i,ip[i]});
  while (!v1.empty()) {
    pii a = v1.back(); v1.pop_back();
    pii b = v2.back(); v2.pop_back();
    int s = a.F;
    int t = b.F;
    int c = min(a.S, b.S);
    event.PB({s,t,c,0});
    if (a.S > c) v1.PB({a.F, a.S-c});
    if (b.S > c) v2.PB({b.F, b.S-c});
  }
}
void BFS(int st, vector<pii> edge[], Tree &tree) {
  tree.init(st);
  memset(vst,0,sizeof(vst));
  queue<int> que;
  que.push(st);
  vst[st] = 1;
  while (!que.empty()) {
    int u = que.front(); que.pop();
    for (auto it:edge[u]) {
      int v = it.F;
      if (vst[v]) continue;
      que.push(v);
      vst[v] = 1;
      tree.child[u].PB(it);
    }
  }
  REP1(i,1,N) assert(vst[i]);
}
void DFS(int u, int dep) {
  seg.save();
  seg.update(tree1.st[u], tree1.ed[u], {dep,u});
  for (auto i:qid[u]) {
    event[i].x = seg.query(tree1.st[event[i].s]);
    assert(event[i].x != 0);
  }
  for (auto it:tree2.child[u]) {
    DFS(it.F, dep+1);
  }
  seg.undo();
}
int main() {
  FILEIO("transport");
  IOS;
  cin >> A >> B >> M;
  N = A + B;
  REP1(i,1,N) cin >> ip[i];
  REP1(eid,1,M) {
    int u, v;
    cin >> u >> v;
    u = u < 0 ? -u : u+A;
    v = v < 0 ? -v : v+A;
    E[u].PB({v,eid});
    rE[v].PB({u,eid});
  }

  build_event();
  BFS(1,rE,tree1);
  BFS(1,E,tree2);
  tree1.yabian();
  seg.init(N);
  REP(i,SZ(event))
    qid[event[i].t].PB(i);
  DFS(tree1.rt,1);
  for (auto it:event) {
    tree1.flow[it.s] += it.c;
    tree1.flow[it.x] -= it.c;
    tree2.flow[it.t] += it.c;
    tree2.flow[it.x] -= it.c;
  }
/*
  cout << "TREE1\n";
  REP1(i,1,N) cout << i << " : " << tree1.child[i] << endl;
  cout << "TREE2\n";
  REP1(i,1,N) cout << i << " : " << tree2.child[i] << endl;
  cout << event << endl;
*/
  tree1.calc(ans);
  tree2.calc(ans);

  REP1(i,1,M) assert(ans[i] >= 0);

  cout << "YES" << endl;
  REP1(i,1,M) cout << ans[i] << " ";
  cout << endl;
  

  return 0;
}

