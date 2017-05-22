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

using pii = pair<int, int>;
const int MX = 1111;
int W, N;
int S, T, V;
vector<pii> P;
bool vt1[MX], vt2[MX];

double dis(int i, int j) {
  if (i == j) return 0;
  if (i > j) swap(i, j);
  if (i == S) {
    if (j == T) return W;
    else return P[j].F;
  }
  if (j == T) {
    return W - P[i].F;
  }
  auto p = P[i], q = P[j];
  return hypot(p.F - q.F, p.S - q.S);
}

void dfs(int u, double d, bool *vt) {
  vt[u] = 1;
  for (int i=0; i<V; i++) {
    if (vt[i]) continue;
    double dd = dis(u, i);
    if (dd > d) continue;

    dfs(i, d, vt);
  }
} 

double aX, aY;

void mp(int i, int j) {
  if (i > j) swap(i, j);
  if (i == S) {
    if (j == T) {
      aX = 0.5 * W;
      aY = 0;
    } else {
      aX = 0.5 * P[j].F;
      aY = P[j].S;
    }
    return;
  }
  if (j == T) {
    aX = 0.5 * (W + P[i].F);
    aY = P[i].S;
    return;
  }

  aX = 0.5 * (P[i].F + P[j].F);
  aY = 0.5 * (P[i].S + P[j].S);
}
bool test(double d) {
  fill(vt1, vt1+V+2, 0);
  fill(vt2, vt2+V+2, 0);

  dfs(S, d, vt1);
  dfs(T, d, vt2);

  if (vt1[T]) {
    aX = 0.5;
    aY = 0.0;
    return true;
  } else {
    for (int i=0; i<V; i++) {
      if (!vt1[i]) continue;
      for (int j=0; j<V; j++) {
        if (!vt2[j]) continue;

        double dd = dis(i, j);
        if (dd < d*2) {
          mp(i, j);
          return true;
        }
      }
    }
  }
  return false;
}

int main() {
#ifndef HAO123
  FILEIO("froggy");
#endif
  IOS;

  cin >> W >> N;
  S = 0;
  T = N+1;
  V = N+2;
  P.resize(N+1);
  for (int i=1; i<=N; i++) {
    cin >> P[i].F >> P[i].S;
  }


  double l = 0, r = W+0.5;
  for (int i=0; i<50; i++) {
    double md = (l+r)/2;
    if (test(md)) {
      r = md;
    } else {
      l = md;
    }
  }

  cout << fixed << setprecision(3);
  cout << aX << ' ' << aY << endl;

  return 0;
}

