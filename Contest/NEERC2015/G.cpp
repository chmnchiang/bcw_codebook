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

const int MX = 11111;
int N, K;
int used[MX];
int X[MX], Y[MX];

using pii = pair<int, int>;

vector<pii> gen(int x, int a, int b, int c) {
  fill(used, used+MX, 0);
  vector<pii> ret;
  int t = 1;
  while (!used[x]) {
    used[x] = t;
    t++;
    x = (a * x + b) % c;
  }
  for (int i=0; i<c; i++) if (used[i]) {
    ret.PB({i, used[i]-1});
  }
  reverse(ALL(ret));
  return ret;
}

int main() {
#ifndef HAO123
  FILEIO("generators");
#endif
  IOS;

  cin >> N >> K;
  int sm = 0;
  const int INF = 1029384756;
  int bs = INF;
  int bi = -1;
  for (int i=0; i<N; i++) {
    int x, a, b, c;
    cin >> x >> a >> b >> c;
    auto ret = gen(x, a, b, c);
    sm += ret[0].F;
    X[i] = ret[0].S;
    for (int j=1; j<SZ(ret); j++) {
      int t = ret[0].F - ret[j].F;
      if (t % K) {
        if (bs > t) {
          bs = t;
          bi = i;
          Y[i] = ret[j].S;
        }
      }
    }
  }

  if (sm % K) {
    cout << sm << endl;
    for (int i=0; i<N; i++) {
      cout << X[i] << " \n"[i == N-1];
    }
  } else {
    if (bs == INF) {
      cout << -1 << endl;
    } else {
      cout << sm - bs << endl;
      for (int i=0; i<N; i++) {
        cout << (i == bi ? Y[i] : X[i]) << " \n"[i == N-1];
      }
    }
  }

  return 0;
}

