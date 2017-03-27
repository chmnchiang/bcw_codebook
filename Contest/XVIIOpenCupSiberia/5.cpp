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

const int MXN = 405;
const long long INF = 102938475610293847LL;
struct CostFlow {
  struct Edge {
    int v, r, tag;
    long long f, c;
  };
  int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
  long long dis[MXN], fl, cost;
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
    fl = cost = 0;
  }
  void add_edge(int u, int v, long long f, long long c) {
    E[u].PB({v, SZ(E[v])  , 1, f,  c});
    E[v].PB({u, SZ(E[u])-1, 0, 0, -c});
  }
  pll flow() {
    while (true) {
      for (int i=0; i<n; i++) {
        dis[i] = INF;
        inq[i] = 0;
      }
      dis[s] = 0;
      queue<int> que;
      que.push(s);
      while (!que.empty()) {
        int u = que.front(); que.pop();
        inq[u] = 0;
        for (int i=0; i<SZ(E[u]); i++) {
          int v = E[u][i].v;
          long long w = E[u][i].c;
          if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
            prv[v] = u; prvL[v] = i;
            dis[v] = dis[u] + w;
            if (!inq[v]) {
              inq[v] = 1;
              que.push(v);
            }
          }
        }
      }
      if (dis[t] == INF) break;
      long long tf = INF;
      for (int v=t, u, l; v!=s; v=u) {
        u=prv[v]; l=prvL[v];
        tf = min(tf, E[u][l].f);
      }
      for (int v=t, u, l; v!=s; v=u) {
        u=prv[v]; l=prvL[v];
        E[u][l].f -= tf;
        E[v][E[u][l].r].f += tf;
      }
      cost += tf * dis[t];
      fl += tf;
    }
    return {fl, cost};
  }
}flow;

int N,K,G;
int S,T,TP,V;
int cost[MXN][MXN];

void build_graph(int f) {
  flow.init(V,S,T);
  REP(i,N) flow.add_edge(S,i,1,0);
  REP(j,K) {
    if (j == G) {
      flow.add_edge(N+j,T,f,0);
    } else {
      flow.add_edge(N+j,TP,f-1,0);
    }
  }
  flow.add_edge(N+K,TP,INF,0);
  flow.add_edge(TP,T,N-f,0);

  REP(i,N) REP(j,K+1) {
    flow.add_edge(i,N+j,1,cost[i][j]);
  }
}

int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;
  cin>>N>>K>>G;
  G--;
  S = N+K+1;
  TP = S+1;
  T = TP+1;
  V = T+1;

  REP(i,N) {
    REP(j,K+1) cin>>cost[i][j];
  }

  ll ans = INF;
  int ansf = 0;
  for (int f=1; f<=N; f++) {
    build_graph(f);
    auto res = flow.flow();
    int ff = res.F;
    ll cc = res.S;
    assert(ff == N);
    if (cc < ans) {
      ans = cc;
      ansf = f;
    }
  }

  build_graph(ansf);
  flow.flow();

  cout<<ans<<endl;
  vector<int> vec;
  REP(i,N) {
    int ok = -1;
    for (auto it:flow.E[i]) {
      if (it.tag and it.f == 0) {
        ok = it.v - N + 1;
        break;
      }
    }
    assert(ok != -1);
    cout<<ok<<" \n"[i == N-1];
  }

  return 0;
}

