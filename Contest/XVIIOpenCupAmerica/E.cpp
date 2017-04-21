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

const int MX = 555555;
int V, E, K, W;
bool spec[MX];

struct Edge {
  int u, v;
  int c;
  bool sp;
};

vector<Edge> ed;

int djs[MX];
void dinit() {
  for (int i=0; i<=V+5; i++) djs[i] = i;
}

int ffa(int a) {
  return djs[a] == a ? a : (djs[a] = ffa(djs[a]));
}

int lans;
int proc() {
  dinit();
  lans = 0;
  int v = V;
  int a = 0;
  for (auto e: ed) {
    int fu = ffa(e.u), fv = ffa(e.v);
    if (fu == fv) continue;
    v--;
    djs[fu] = fv;
    lans += e.c;
    if (spec[e.u] ^ spec[e.v]) a++;
    if (v == 1) break;
  }
  if (v != 1) return -1;
  return a;
}

int calc(int m) {
  for (auto &e: ed) {
    if (e.sp) e.c -= m;
  }

  sort(ALL(ed), [](Edge e1, Edge e2) -> bool { 
     return make_tuple(e1.c, (int)e1.sp) < make_tuple(e2.c, (int)e2.sp);
   });

  int l = proc();

  sort(ALL(ed), [](Edge e1, Edge e2) -> bool { 
     return make_tuple(e1.c, -(int)e1.sp) < make_tuple(e2.c, -(int)e2.sp);
   });

  int r = proc();

  //cout << m << ' ' << l << ' ' << r << endl;

  for (auto &e: ed) {
    if (e.sp) e.c += m;
  }

  if (l <= W and W <= r) return 0;
  else if (W <= l) return 1;
  else return -1;
}

int32_t main() {
  IOS;

  cin >> V >> E >> K >> W;
  for (int i=0; i<K; i++) {
    int t; cin >> t;
    spec[t] = 1;
  }

  for (int i=0; i<E; i++) {
    int u, v, t; cin >> u >> v >> t;
    ed.PB({u, v, t, spec[u] ^ spec[v]});
    //cout << u << ' ' << v << ' ' << t << ' ' << (spec[u] ^ spec[v]) << endl;
  }

  int l = -1e7, r = 1e7;
  while (l < r) {
    int m = (l+r)/2;
    int f = calc(m);

    if (f == 0) {
      l = r = m;
      //cout << "l = " << l << endl;
      break;
    } else if (f < 0) l = m+1;
    else r = m-1;
  }

  //cout << l << endl;

  if (r >= 1e7-3) {
    cout << -1 << endl;
  } else {
    calc(l);
    cout << lans + l*W << endl;
  }

  return 0;
}

