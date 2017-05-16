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
const int INF = 1029384756;

struct SegmentTree {
  int n;
  int tree[MAXN*4];
  void init(int l, int r, int id, int arr[]) {
    if (l == r) {
      tree[id] = arr[l];
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    init(l,m,lc,arr);
    init(m+1,r,rc,arr);
    tree[id] = max(tree[lc], tree[rc]);
  }
  void upd(int l, int r, int x, int v, int id) {
    if (l == r) {
      tree[id] = v;
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    if (x <= m) upd(l,m,x,v,lc);
    else upd(m+1,r,x,v,rc);
    tree[id] = max(tree[lc], tree[rc]);
  }
  int qry(int l, int r, int ql, int qr, int id) {
    if (qr < l) return -INF;
    if (r < ql) return -INF;
    if (ql <= l and r <= qr) {
      return tree[id];
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    return max(qry(l,m,ql,qr,lc), qry(m+1,r,ql,qr,rc));
  }
  void init(int _n, int arr[]) {
    n = _n;
    init(1,n,1,arr);
  }
  void upd(int x, int v) {
    upd(1,n,x,v,1);
  }
  int qry(int l, int r) {
    int res = qry(1,n,l,r,1);
    return res;
  }
} tree1, tree2, tree3;

int N,M,Q,ip[MAXN],arr[MAXN],height[MAXN];
ll ans;

int main() {
  IOS;
  cin>>N>>M;
  ans = 0;
  REP1(i,1,N) {
    cin>>ip[i];
    ans += ip[i];
    height[i] = 0;
  }

  REP1(i,1,N) arr[i] = height[i] - i;
  tree1.init(N,arr);
  REP1(i,1,N) arr[i] = height[i] + i;
  tree2.init(N,arr);

  REP1(i,1,N) arr[i] = -ip[i];
  tree3.init(N,arr);

  cin>>Q;
  REP(_,Q) {
    int x,v;
    cin>>x>>v;
    int l,r;

    l = 1, r = x;
    while (l < r) {
      int m = (l + r) / 2;
      int mnh = tree1.qry(m, x);
      if (mnh < M-x) r = m;
      else l = m+1;
    }
    
    if (l > 1 and tree1.qry(l-1,x) == M-x) l--;
    int ql = l;

    l = x, r = N;
    while (l < r) {
      int m = (l + r + 1) / 2;
      int mnh = tree2.qry(x, m);
      if (mnh < M+x) l = m;
      else r = m-1;
    }

    if (r < N and tree2.qry(x,r+1) == M+x) r++;
    int qr = r;

    int mnv = -tree3.qry(ql, qr);

    l=0, r = max(x-ql,qr-x);
    while (l < r) {
      int m = (l + r) / 2;
      int z1 = max(x - m, ql);
      int z2 = min(x + m, qr);
      int qv = -tree3.qry(z1, z2);
      if (qv <= mnv) r = m;
      else l = m+1;
    }

    //dump(x,v,ql,qr,mnv);

    int at = x - l;
    if (at < ql or ip[at] != mnv) at = x + l;
    assert(ql <= at and at <= qr);
    assert(ip[at] == mnv);

    //dump(at,v);
    ans -= ip[at];
    ans += v;

    ip[at] = v;
    height[at]++;

    tree1.upd(at, height[at]-at);
    tree2.upd(at, height[at]+at);
    tree3.upd(at, -v);


    cout<<ans<<endl;
  }

  return 0;
}

