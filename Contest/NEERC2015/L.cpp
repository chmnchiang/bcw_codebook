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

const int MAXN = 100005;
const int LOG = 20;
const ll INF = 1LL<<40;

int lt[MAXN],rt[MAXN];
ll N,M,A[MAXN],psum[MAXN];
ll rmq1[LOG][MAXN], rmq2[LOG][MAXN];

ll get_rmq(int l, int r, ll rmq[LOG][MAXN]) {
  int i = __lg(r - l + 1);
  return max(rmq[i][l], rmq[i][r-(1<<i)+1]);
}
bool check_ok(ll H) {
  //cout<<H<<endl;
  REP1(i,1,N) if (A[i] >= H) return true;

  REP1(i,1,N) {
    int l = 0, r = i;
    while (l < r) {
      int m = (l + r + 1) / 2;
      if (get_rmq(m, i, rmq1) >= H-i) l = m;
      else r = m - 1;
    }
    lt[i] = l;
  }

  for (int i=N; i>=0; i--) {
    int l = i, r = N+1;
    while (l < r) {
      int m = (l + r) / 2;
      if (get_rmq(i, m, rmq2) >= H+i) r = m;
      else l = m+1;
    }
    rt[i] = l;
  }

  for (int i=1; i<=N; i++) {
    if (lt[i] <= 0) continue;
    if (rt[i] > N) continue;
    //dump(i,lt[i],rt[i]);
    ll need = 0;
    ll z = H - (i - lt[i]) + 1;
    need += (H + z) * (i - lt[i]) / 2;
    z = H - (rt[i] - i) + 1;
    need += (H + z) * (rt[i] - i) / 2;
    need -= H;
    need -= psum[rt[i]-1] - psum[lt[i]];
    if (need <= M) return true;
  }

  return false;
}
int main() {
#ifndef HAO123
  FILEIO("landscape");
#endif
  IOS;
  cin>>N>>M;
  psum[0] = 0;
  REP1(i,1,N) {
    cin>>A[i];
    psum[i] = psum[i-1] + A[i];
  }
  A[0] = A[N+1] = -INF;

  REP1(i,0,N+1) {
    rmq1[0][i] = A[i] - i;
    rmq2[0][i] = A[i] + i;
  }

  REP1(i,1,LOG-1) {
    REP1(j,0,N+1) {
      if (j + (1<<i) - 1 > N+1) continue;
      rmq1[i][j] = max(rmq1[i-1][j], rmq1[i-1][j+(1<<(i-1))]);
      rmq2[i][j] = max(rmq2[i-1][j], rmq2[i-1][j+(1<<(i-1))]);
    }
  }

  //cout<<check_ok(5);

  //return 0;

  ll l = 0, r = 2000000000;
  while (l < r) {
    ll m = (l + r + 1) / 2;
    if (check_ok(m)) l = m;
    else r = m-1;
  }
  cout<<l<<endl;

  return 0;
}

