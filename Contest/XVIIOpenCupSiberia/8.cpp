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

struct SegmentTree {
  int n;
  double tree[4*MAXN];
  void init(int tn) {
    n = tn;
    REP(i,n*4) tree[i] = 0;
  }
  void update_tree(int l, int r, int x, double v, int id) {
    if (l == r) {
      tree[id] = v;
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    if (x <= m) update_tree(l,m,x,v,lc);
    else update_tree(m+1,r,x,v,rc);
    tree[id] = tree[lc] + tree[rc];
  }
  double query_tree(int l, int r, int fl, int fr, int id) {
    if (fr < l) return 0;
    if (fl > r) return 0;
    if (fl <= l and r <= fr) return tree[id];
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    return query_tree(l,m,fl,fr,lc) + query_tree(m+1,r,fl,fr,rc);
  }
  void update(int x, double v) {
    update_tree(1,n,x,v,1);
  }
  double query(int l, int r) {
    return query_tree(1,n,l,r,1);
  }
} tree;

int N,K,V,lt[MAXN],rt[MAXN];
double ip[MAXN], laji[MAXN];
int step,st[MAXN],ed[MAXN];
int root;

void DFS(int u) {
  if (u == 0) return;
  st[u] = ++step;
  DFS(lt[u]);
  DFS(rt[u]);
  ed[u] = step;
}

int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;
  cin >> N >> K;
  V = 2*N+1;
  root = 1;
  REP1(i,N+1,2*N+1) cin >> ip[i];
  REP1(i,1,N) {
    cin >> laji[i] >> lt[i] >> rt[i];
    if (lt[i] < 0) lt[i] = N + (-lt[i]);
    if (rt[i] < 0) rt[i] = N + (-rt[i]);
  }
  step = 0;
  DFS(root);

  tree.init(step);
  REP1(i,N+1,V) {
    tree.update(st[i], ip[i]);
  }

  REP1(i,1,K) {
    int cmd,x;
    double y;
    cin>>cmd;
    if (cmd == 1) {
      cin >> x >> y;
      // x zhe ge ye zi => y
      x = N + x;
      tree.update(st[x], y);
    } else {
      cin >> x;
      int a = lt[x];
      int b = rt[x];
      double ra = tree.query(st[a], ed[a]);
      double rb = tree.query(st[b], ed[b]);
      double res = rb / (ra+rb) * laji[x];
      cout<<fixed<<setprecision(15)<<res<<"\n";
    }
  }


  return 0;
}

