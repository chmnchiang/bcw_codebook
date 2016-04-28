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

const int MXN = 405;

struct DisjointSet {
  int fa[MXN];
  DisjointSet () { REP(i,MXN) fa[i]=i; }
  int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
  void uni(int x, int y) { fa[f(y)] = f(x); }
}djs;

struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    fill(vst,vst+n,0);
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    fill(vst,vst+n,0);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
}scc;
struct Edge {
  int u,v,w;
}edge[MXN*MXN];

int N,M,vst[MXN],col[MXN];
int iste[MXN*MXN];
bitset<MXN> dp[MXN];
vector<int> E[MXN];

bool isbin() {
  REP(i,N) vst[i] = col[i] = 0;
  REP(i,N) {
    if (vst[i]) continue;
    queue<int> que;
    que.push(i);
    vst[i] = 1;
    while (!que.empty()) {
      int u = que.front(); que.pop();
      for (auto v:E[u]) {
        if (vst[v]) {
          if (col[v] == col[u]) return false;
          continue;
        }
        col[v] = col[u]^1;
        vst[v] = 1;
        que.push(v);
      }
    }
  }
  return true;
}
inline int rev(int x) {
  if (x < N) return x + N;
  else return x-N;
}
vector<int> X;
// return true if failed
bool test(int mid) {
  scc.init(2*N);
  REP1(i,0,mid) {
    int u = edge[i].u, v = edge[i].v;
    if (iste[i]) {
      scc.add_edge(rev(u),v);
      scc.add_edge(rev(v),u);
      scc.add_edge(u,rev(v));
      scc.add_edge(v,rev(u));
    } else {
      scc.add_edge(rev(u),v);
      scc.add_edge(rev(v),u);
    }
  }
  scc.solve();
  REP(i,N) if (scc.bln[i] == scc.bln[rev(i)]) return false;
  return true;
}
inline int solve() {
  REP(i,2*N) {
    dp[i].reset();
    dp[i][i] = 1;
  }
  int l = 0, r = M;
  while (l < r) {
    int mid = (l+r)/2;
    if (test(mid)) l=mid+1;
    else r = mid;
  }
  if (l == M) return 0;
  return edge[l].w;
}
int main() {
  IOS;
  cin >> N;
  M = 0;
  REP(i,N) {
    REP1(j,i+1,N-1) {
      int v;
      cin >> v;
      edge[M++] = {i,j,v};
    }
  }
  fill(iste,iste+M,0);
  sort(edge,edge+M,[](Edge a, Edge b) { return a.w > b.w; });

  int B = 0;
  int ans = edge[0].w;
  REP(i,M) {
    int u = edge[i].u, v = edge[i].v, A;
    if (i == M) A = 0;
    else A = edge[i+1].w;
    if (djs.f(u) != djs.f(v)) {
      E[u].PB(v);
      E[v].PB(u);
      if (!isbin()) break;
      djs.uni(u,v);
      iste[i] = 1;
      B = solve();
      //cout << "CALC " << A << " " << B << endl;
      ans = min(ans, A+B);
    } else {
      if (col[u] == col[v]) break;
      ans = min(ans, A+B);
    }
  }
  cout << ans << endl;

  return 0;
}

