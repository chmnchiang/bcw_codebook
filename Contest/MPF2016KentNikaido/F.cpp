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

struct Isap{
  static const int MXN = 10000;
  static const int INF = 2147483647;
  struct Edge{ int v,f,re; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (nf){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  int flow(int res=0){
    for (int i=0; i<n; i++) h[i] = gap[i] = 0;
    gap[0] = n;
    while (h[s] < n) res += DFS(s,INF);
    return res;
  }
}flow;

int N;
const int MX = 333;
char ip[MX][MX];
int off[MX*MX];

inline int id(int x, int y) {
  return x * (N-1) + y;
}

int main() {
  IOS;

  cin >> N;
  for (int i=0; i<N; i++) {
    cin >> ip[i];
  }

  int M = (N+1) * (N+1), S = M, U = S+1, V = U+1;
  flow.init(V, S, U);

  for (int i=0; i<N-1; i++) {
    if (ip[0][i] != ip[0][i+1]) {
      off[id(0, i)] --;
    }

    if (ip[N-1][i] != ip[N-1][i+1]) {
      off[id(N-2, i)] --;
    }

    if (ip[i][0] != ip[i+1][0]) {
      off[id(i, 0)] --;
    }

    if (ip[i][N-1] != ip[i+1][N-1]) {
      off[id(i, N-2)] --;
    }
  }

  for (int i=0; i<N-1; i++) {
    for (int j=0; j<N-2; j++) {
      if (ip[i][j+1] != ip[i+1][j+1]) {
        if ((i+j)%2 == 0) {
          flow.add_edge(id(i, j), id(i, j+1), 1);
        } else {
          flow.add_edge(id(i, j+1), id(i, j), 1);
        }
      }
    }
  }

  for (int i=0; i<N-1; i++) {
    for (int j=0; j<N-2; j++) {
      if (ip[j+1][i] != ip[j+1][i+1]) {
        if ((i+j)%2 == 0) {
          flow.add_edge(id(j, i), id(j+1, i), 1);
        } else {
          flow.add_edge(id(j+1, i), id(j, i), 1);
        }
      }
    }
  }

  int X, Y; X = Y = 0;
  for (int i=0; i<N-1; i++) {
    for (int j=0; j<N-1; j++) {
      int f = 2 + off[id(i, j)];
      if ((i+j)%2 == 0) {
        flow.add_edge(S, id(i, j), f);
        X += f;
      } else {
        flow.add_edge(id(i, j), U, f);
        Y += f;
      }
    }
  }

  if (X != Y) {
    cout << "NO" << endl;
    return 0;
  }

  int t = flow.flow();
  if (t != X) {
    cout << "NO" << endl;
  } else {
    cout << "YES" << endl;
  }

  return 0;
}


