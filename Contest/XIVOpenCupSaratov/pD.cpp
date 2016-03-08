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

const int MXN = 400005;
const int INF = 1029384756;

struct DisjointSet {
  vector<int> fa;
  void init(int n) {
    fa.resize(n+1);
    REP(i,n+1) fa[i] = i;
  }
  int f(int x) { return x == fa[x] ? x : fa[x] = f(fa[x]); }
  void uni(int x, int y) { fa[f(y)] = f(x); }
}djs;
struct Tree {
  vector<int> E[MXN],W[MXN];
  void init(int n) {
    REP1(i,0,n) {
      E[i].clear();
      W[i].clear();
    }
  }
  void add_edge(int u, int v, int w) {
    E[u].PB(v); W[u].PB(w);
    E[v].PB(u); W[v].PB(w);
  }
}mst;
struct Edge {
  int u,v,w;
  friend ostream& operator << (ostream &s, const Edge &he) {
    return s << "{ " << he.u << " " << he.v << " : " << he.w << " }";
  }
}edge[MXN];

int N,M;
int lca[MXN],vst[MXN],ans[MXN],isSon[MXN];
vector<int> edgeID[MXN],crossEdge[MXN];
multiset<int> weight;
int heapID[MXN];
priority_queue<pii> pq[MXN];

bool input() {
  if (!(cin >> N >> M)) return false;
  REP1(i,1,M) cin >> edge[i].u >> edge[i].v >> edge[i].w;
  return true;
}
void init() {
  weight.clear();
  REP1(i,0,N) {
    edgeID[i].clear();
    crossEdge[i].clear();
    isSon[i] = 0;
    ans[i] = INF;
    heapID[i] = i;
    pq[i] = priority_queue<pii>();
  }
}
bool comp(Edge a, Edge b) { return a.w < b.w; }
void DFS1(int u) {
  vst[u] = 1;
  for (auto v:mst.E[u]) {
    if (vst[v]) continue;
    DFS1(v);
    djs.uni(u,v);
  }
  for (auto qid:edgeID[u]) {
    int v = u ^ edge[qid].u ^ edge[qid].v;
    if (vst[v]) lca[qid] = djs.f(v);
  }
}

int merge_heap(int a, int b) {
  if (pq[a].size() < pq[b].size()) swap(a,b);
  while (!pq[b].empty()) {
    pq[a].push(pq[b].top());
    pq[b].pop();
  }
  return a;
}
int make_mst(int n, vector<Edge> eg) {
  vector<int> seq;
  for (auto &it:eg) {
    it.u = max(it.u,0);
    it.v = max(it.v,0);
    if (it.u) it.u = djs.f(it.u);
    if (it.v) it.v = djs.f(it.v);
    seq.PB(it.u);
    seq.PB(it.v);
  }
  sort(ALL(seq));
  seq.resize(unique(ALL(seq))-begin(seq));
  assert(SZ(seq) <= n);
  for (auto &it:eg) {
    it.u = lower_bound(ALL(seq),it.u)-begin(seq);
    it.v = lower_bound(ALL(seq),it.v)-begin(seq);
  }
  DisjointSet djs2;
  int res = -1;
  sort(ALL(eg),comp);
  djs2.init(n);
  int con = n;
  for (auto it:eg) {
    if (djs2.f(it.u) != djs2.f(it.v)) {
      djs2.uni(it.u,it.v);
      res = max(res,it.w);
      con--;
    }
  }
  if (con > 1) res = INF;
  return res;
}
void DFS(int u, int f) {
  vector<Edge> todo;
  int hid = heapID[u];
  for (auto v:mst.E[u]) {
    if (v == f) continue;
    DFS(v,u);
  }
  for (auto v:mst.E[u]) {
    if (v == f) continue;
    isSon[v] = 1;
  }
  for (auto v:mst.E[u]) {
    if (v == f) continue;
    int vid = heapID[v];
    while (!pq[vid].empty()) {
      auto it = pq[vid].top();
      if (djs.f(it.S) == u or isSon[djs.f(it.S)]) {
        pq[vid].pop();
        continue;
      }
      todo.PB({v,-it.S,-it.F});
      break;
    }
    hid = merge_heap(hid,vid);
  }
  for (auto v:mst.E[u]) {
    isSon[v] = 0;
  }

  for (auto eid:crossEdge[u])
    todo.PB(edge[eid]);
  int res = make_mst(SZ(mst.E[u]),todo);
  int mn = INF;
  for (auto w:mst.W[u]) {
    mn = min(mn,w);
    weight.erase(weight.find(w));
  }
  res = max(res,mn);
  if (!weight.empty()) res = max(res,*weight.rbegin());
  ans[u] = res;
  for (auto w:mst.W[u])
    weight.insert(w);

  for (auto v:mst.E[u]) {
    if (v == f) continue;
    djs.uni(u,v);
  }
  for (auto eid:edgeID[u]) {
    int v = edge[eid].u ^ edge[eid].v ^ u;
    if (djs.f(u) == djs.f(v)) continue;
    pq[hid].push({-edge[eid].w,v});
  }
  heapID[u] = hid;
}
void solve() {
  mst.init(N);
  djs.init(N);
  sort(edge+1,edge+1+M,comp);
  weight.clear();
  int con = N;
  REP1(i,1,M) {
    int u = edge[i].u, v = edge[i].v;
    if (djs.f(u) != djs.f(v)) {
      djs.uni(u,v);
      weight.insert(edge[i].w);
      mst.add_edge(u,v,edge[i].w);
      con--;
    }
    edgeID[u].PB(i);
    edgeID[v].PB(i);
  }
  if (con > 1) return;
  djs.init(N);
  REP1(i,0,N) vst[i] = 0;
  DFS1(1);
  REP1(i,1,M) {
    if (lca[i] != edge[i].u and lca[i] != edge[i].v)
      crossEdge[lca[i]].PB(i);
  }
  djs.init(N);
  DFS(1,1);
}
int main() {
  IOS;
  int cas = 0;
  while (input())  {
    init();
    solve();
    cas++;
    cout << "Case " << cas << ":";
    REP1(i,1,N) {
      if (ans[i] == INF) ans[i] = -1;
      cout << " " << ans[i];
    }
    cout << "\n";
  }

  return 0;
}
