//a34021501 {{{
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

#ifdef HAO123
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef HAO123
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif
// }}}
// Let's Fight! !111111111!

#define int long long
const int MX = 333333;
struct Edge {
  int u, v;
  int id;
  bool isl;

  int to(int from) {
    return u == from ? v : u;
  }
};

int V, M;
vector<Edge> eds;
vector<int> E[MX];

void addEdge(int u, int v) {
  int id = SZ(eds);
  eds.PB({u, v, id, 0});
  E[u].PB(id);
  E[v].PB(id);
}

vector<int> sta, staE;
bool ins[MX], vt[MX];
int ans1[MX];
int lsz[MX];
vector<vector<int>> lps;

int dfs(int u, int fa) {
  sta.PB(u);
  ins[u] = 1;
  vt[u] = 1;
  int t = 1;
  for (auto id: E[u]) {
    int v = eds[id].to(u);
    if (v == fa) continue;
    if (ins[v]) {
      eds[id].isl = 1;
      int j = SZ(sta) - 1;
      vector<int> vec;
      vec.PB(v);
      while (sta[j] != v) {
        vec.PB(sta[j]);
        int eid = staE[j-1];
        eds[eid].isl = 1;
        j--;
      }
      lps.PB(vec);
    } else if (!vt[v]) {
      staE.PB(id);
      int tt = dfs(v, u);
      t += tt;
      staE.pop_back();
      if (!eds[id].isl) {
        ans1[id] = (V - tt) * tt;
      }
    }
  }
  ins[u] = 0;
  sta.pop_back();
  return t;
}

struct DJS {
  int vl[MX];
  int sz[MX];
  void init() {
    for (int i=0; i<MX; i++) vl[i] = i, sz[i] = 1;
  }

  int ffa(int u) {
    return vl[u] == u ? u : (vl[u] = ffa(vl[u]));
  }

  void uni(int u, int v) {
    int fu = ffa(u), fv = ffa(v);
    if (fu == fv) return;
    vl[fv] = fu;
    sz[fu] += sz[fv];
  }

  int gets(int u) {
    return sz[ffa(u)];
  }
} djs;

int C2(int x) {
  return (x-2) * (x-1) / 2;
}

int32_t main() {
#ifndef HAO123
  FILEIO("cactus");
#endif
  IOS;

  cin >> V >> M;
  for (int i=0; i<M; i++) {
    int n; cin >> n;
    int u; cin >> u;
    for (int j=1; j<n; j++) {
      int v; cin >> v;
      addEdge(u, v);
      u = v;
    }
  }

  dfs(1, -1);

  int ans = 0;
  djs.init();
  for (auto &e: eds) {
    if (!e.isl) {
      djs.uni(e.u, e.v);
      ans += ans1[e.id];
    }
  }
  //cout << ans << endl;

  int tmp = 0;
  for (int i=1; i<=V; i++) {
    if (djs.ffa(i) == i) {
      tmp += C2(djs.gets(i));
    }
  }

  //cout << tmp << endl;
  for (auto &loop: lps) {
    int ts = 0, n = 0;
    for (auto v: loop) {
      ts += C2(djs.gets(v)); 
      n += djs.gets(v);
    }
    ans += (C2(n) + tmp - ts) * SZ(loop);
  }

  cout << ans-SZ(eds) << endl;
  return 0;
}

