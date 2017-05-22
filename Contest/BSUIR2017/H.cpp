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

const int MX = 333;
string A, B;
int N, M, K;
int lcs[MX][MX];

void pre() {
  for (int i=N-1; i>=0; i--) {
    for (int j=M-1; j>=0; j--) {
      if (A[i] != B[j]) lcs[i][j] = 0;
      else {
        if (i != N-1 and j != M-1)
          lcs[i][j] = lcs[i+1][j+1] + 1;
        else lcs[i][j] = 1;
      }
    }
  }
}

inline bool eq(int i, int j, int l) {
  return lcs[i][j] >= l;
}

const int INF = 1029384756;
using A34 = array<int, 4>;
map<A34, int> mem;

int dp(int i, int j, int pi, int pj) {
  if (i > N) return INF;
  if (j > M) return INF;
  if (i == N and j == M and pi == 0 and pj == 0) {
    return 0;
  }

  if (mem.count(A34{i, j, pi, pj}))
    return mem[A34{i, j, pi, pj}];

  int t = INF;
  if (pi == 0 and pj == 0) {
    t = min(t, dp(i+1, j, 1, 0) + 1);
    t = min(t, dp(i, j+1, 0, 1) + 1);
    if (eq(i, j, K))
      t = min(t, dp(i+K, j+K, K, K) + K);
  } else if (pi == 0 and pj != K) {
    int x = pj;
    t = min(t, dp(i, j+1, 0, x+1) + 1);
    if (eq(i, j, K-x))
      t = min(t, dp(i+K-x, j+K-x, K-x, K) + (K-x));
  } else if (pj == 0 and pi != K) {
    int x = pi;
    t = min(t, dp(i+1, j, x+1, 0) + 1);
    if (eq(i, j, K-x))
      t = min(t, dp(i+K-x, j+K-x, K, K-x) + (K-x));
  } else if (pi == K and pj != K) {
    int x = pj;
    t = min(t, dp(i, j, 0, x));
    if (!x) t = min(t, dp(i+1, j, K, 0) + 1);
    if (eq(i, j, 1)) t = min(t, dp(i+1, j+1, K, x+1) + 1);
  } else if (pj == K and pi != K) {
    int x = pi;
    t = min(t, dp(i, j, x, 0));
    if (!x) t = min(t, dp(i, j+1, 0, K) + 1);
    if (eq(i, j, 1)) t = min(t, dp(i+1, j+1, x+1, K) + 1);
  } else if (pi == K and pj == K) {
    t = min(t, dp(i, j, K, 0));
    t = min(t, dp(i, j, 0, K));
    t = min(t, dp(i, j, 0, 0));
    if (eq(i, j, 1)) t = min(t, dp(i+1, j+1, K, K) + 1);
  } else {
    assert(false);
  }

  mem[A34{i, j, pi, pj}] = t;
 // cout << "dp(" << i << ", " << j << ", " << pi << ", " << pj << ") = " << t << endl;
  return t;
}

int main() {
  IOS;
  cin >> K;
  cin >> A >> B;
  N = SZ(A);
  M = SZ(B);

  pre();

  cout << dp(0, 0, 0, 0) << endl;

  return 0;
}

