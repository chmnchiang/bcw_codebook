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
// Let's Fight! ~OAO~~

using LL = long long;
using ll = long long;

const int MX = 123;
const int MAX = 1LL<<22;

int N, M;
int X, Y;


int L[MX], R[MX], V[MX];
LL F[MX];

using pii = pair<int, int>;
using pll = ll;
using pllii = pair<pll, pii>;
vector<pllii> hsx, hsy;

vector<pii> Hao[111];

inline void setll(pll &x, int i) {
  x |= 1LL<<i;
}

void haoboohao() {
  for (int i=1; i<=N; i++) {
    if (!SZ(Hao[i])) continue;
    sort(ALL(Hao[i]));
    int n = SZ(Hao[i]);
    for (int j=0; j<n-1; j++) {
      if (Hao[i][j].F == Hao[i][j+1].F) assert(Hao[i][j] == Hao[i][j+1]);
    }

    Hao[i].resize(unique(ALL(Hao[i])) - Hao[i].begin());
    n = SZ(Hao[i]);

    for (int j=1; j<n; j++) {
      int l = Hao[i][j-1].F+1, r = Hao[i][j].F;
      Hao[l].PB({r, Hao[i][j-1].S ^ Hao[i][j].S});
    }

    Hao[i].resize(1);
  }
}

int32_t main() {
  IOS;
  cin >> N >> M;
  for (int i=0; i<M; i++) {
    int l, r, v; cin >> l >> r >> v;
    Hao[l].PB({r, v});
  }

  haoboohao();
  M = 0;
  for (int i=1; i<=N; i++) {
    if (SZ(Hao[i])) {
      L[M] = i;
      R[M] = Hao[i][0].F;
      V[M] = Hao[i][0].S;
      M ++;
    }
  }

  for (int i=0; i<M; i++) {
    L[i] = N - L[i];
    R[i] = N - R[i];
    swap(L[i], R[i]);
    for (int j=L[i]; j<=R[i]; j++) {
      F[i] += (1LL << j);
    }
  }

  X = N/2;
  Y = N - X;

  for (int m = 0; m < (1<<X); m++) {
    int s = __builtin_popcountll(m);
    pll hs = 0;

    for (int i=0; i<M; i++) {

      int t = __builtin_popcountll(F[i] & m) % 2;
      if (t) {
        setll(hs, i);
      }
    }

    hsx.PB({hs, {s, m}});
  }

  for (int m=0; m<(1<<Y); m++) {
    int s = __builtin_popcountll(m);
    pll hs = 0;

    for (int i=0; i<M; i++) {
      LL mm = ((LL)m) << X;
      int t = (__builtin_popcountll(F[i] & mm) + V[i]) % 2;
      if (t) {
        setll(hs,i);
      }
    }

    hsy.PB({hs, {s, m}});
  }

  sort(ALL(hsx));
  sort(ALL(hsy));

  LL bx = 1LL<<62, bs = 123123123;
  for (int i=0, j=0; i<SZ(hsx); i++) {
    if (i and hsx[i].F == hsx[i-1].F) continue;
    auto h = hsx[i].F;
    while (j < SZ(hsy) and hsy[j].F < h) j++;

    if (j < SZ(hsy) and hsy[j].F == h) {
      int s = hsx[i].S.F + hsy[j].S.F;
      LL x = (((LL)hsy[j].S.S) << X) + hsx[i].S.S;
      if (bs > s) {
        bs = s;
        bx = x;
      } else if (bs == s and bx > x) {
        bs = s;
        bx = x;
      }
    }
  }

  for (int i=N-1; i>=0; i--) {
    cout << !!(bx&(1LL<<i)) << " \n"[i==0];
  }

  return 0;
}
