//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(x) memset((x),0,sizeof(x))
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

const int LOG = 18;
const int MAXN = 200005;

struct RMQ {
  int n,mn[LOG][MAXN],mx[LOG][MAXN];
  void init(int tn, int arr[], int brr[]) {
    n = tn;
    REP1(i,1,n) {
      mn[0][i] = arr[i];
      mx[0][i] = brr[i];
    }
    REP1(i,1,LOG-1) {
      REP1(j,1,n) {
        if (j + (1<<i) - 1 > n) break;
        mn[i][j] = min(mn[i-1][j], mn[i-1][j+(1<<(i-1))]);
        mx[i][j] = max(mx[i-1][j], mx[i-1][j+(1<<(i-1))]);
      }
    }
  }
  int qmin(int l, int r) {
    int i = __lg(r-l+1);
    return min(mn[i][l], mn[i][r-(1<<i)+1]);
  }
  int qmax(int l, int r) {
    int i = __lg(r-l+1);
    return max(mx[i][l], mx[i][r-(1<<i)+1]);
  }
} rmq[LOG], rmq2;

int N,A[MAXN];
int lt[2][MAXN], rt[2][MAXN];
int arr[MAXN];
pii seg[MAXN];

bool check_ok(int step) {
  dump(step);
  REP1(i,1,N) {
    int l = i, r = i;
    REP(k,LOG) {
      if (step & (1<<k)) {
        int x = l;
        int y = r;
        l = rmq[k].qmin(x, y);
        r = rmq[k].qmax(x, y);
      }
    }
    seg[i] = {l,r};
    arr[i] = l;
    dump(i, seg[i]);
  }
  rmq2.init(N, arr, arr);
  REP1(i,1,N) {
    int lmax = rmq2.qmax(seg[i].S+1, N);
    if (seg[i].S >= N) continue;
    if (lmax > i) {
      //dump(i, lmax);
      return true;
    }
  }

  return false;
}
int main() {
  IOS;
  cin>>N;
  REP1(i,1,N) {
    cin>>A[i];
    lt[0][i] = max(i-A[i], 1);
    rt[0][i] = min(i+A[i], N);
  }

  rmq[0].init(N, lt[0], rt[0]);
  REP1(i,1,LOG-1) {
    REP1(j,1,N) {
      lt[i&1][j] = rmq[i-1].qmin(lt[(i&1)^1][j], rt[(i&1)^1][j]);
      rt[i&1][j] = rmq[i-1].qmax(lt[(i&1)^1][j], rt[(i&1)^1][j]);
    }
    rmq[i].init(N, lt[i&1], rt[i&1]);
  }

  int l = 0, r = N;
  while (l < r) {
    int m = (l+r+1)/2;
    if (check_ok(m)) l = m;
    else r = m - 1;
  }
  l += 1;
  cout<<l<<endl;

  return 0;
}

