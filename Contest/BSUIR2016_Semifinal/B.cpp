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
// Let's Fight! ~OAO~~

using ll = long long;
const int MAXN = 300005;
const int LOG = __lg(MAXN)+1;
const ll INF = 1LL<<50;

struct SegmentTree {
  int n;
  struct Node {
    ll s,sa,tag;
  } tree[MAXN*4];
  ll s[MAXN],sa[MAXN],tag[MAXN];

  void init(int tn, ll arr[]) {
    n = tn;
    init_tree(0,n-1,1,arr);
    REP(i,n) {
      s[i] = arr[i];
      sa[i] = -INF;
      tag[i] = -INF;
    }
  }
  void init_tree(int l, int r, int id, ll arr[]) {
    if (l == r) {
      tree[id] = {arr[l], -INF, -INF};
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    init_tree(l, m, lc, arr);
    init_tree(m+1, r, rc, arr);
    tree[id].s = max(tree[lc].s, tree[rc].s);
    tree[id].sa = max(tree[lc].sa, tree[rc].sa);
    tree[id].tag = -INF;
  }

  void push(int id, int lc, int rc) {
    tree[lc].tag = max(tree[lc].tag, tree[id].tag);
    tree[lc].sa = max(tree[lc].sa, tree[lc].s+tree[lc].tag);
    tree[rc].tag = max(tree[rc].tag, tree[id].tag);
    tree[rc].sa = max(tree[rc].sa, tree[rc].s+tree[rc].tag);
  }
  void update(int l, int r, int fl, int fr, ll v, int id) {
    if (l == fl and r == fr) {
      tree[id].tag = max(tree[id].tag, v);
      tree[id].sa = max(tree[id].sa, tree[id].s + tree[id].tag);
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id,lc,rc);
    if (fr <= m) update(l,m,fl,fr,v,lc);
    else if (m < fl) update(m+1,r,fl,fr,v,rc);
    else {
      update(l,m,fl,m,v,lc);
      update(m+1,r,m+1,fr,v,rc);
    }
    tree[id].s = max(tree[lc].s, tree[rc].s);
    tree[id].sa = max(tree[lc].sa, tree[rc].sa);
  }
  ll query(int l, int r, int fl, int fr, int id) {
    if (l == fl and r == fr) return tree[id].sa;
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id,lc,rc);
    if (fr <= m) return query(l,m,fl,fr,lc);
    if (m < fl) return query(m+1,r,fl,fr,rc);
    return max(query(l,m,fl,m,lc), query(m+1,r,m+1,fr,rc));
  }
  void upd(int l, int r, ll v) {
    update(0,n-1,l,r,v,1);
    return;
    REP1(i,l,r) {
      tag[i] = max(tag[i], v);
      sa[i] = s[i] + tag[i];
    }
  }
  ll qry(int l, int r) {
    ll res = query(0,n-1,l,r,1);
    return res;
    ll r2 = -INF;
    REP1(i,l,r) {
      r2 = max(r2, sa[i]);
    }
    assert(r2 == res);
    return res;
  }
} tree;

struct RMQ {
  int n;
  int rmq[LOG][MAXN];

  void init(int tn, int arr[]) {
    n = tn;
    REP1(i,1,n) rmq[0][i] = abs(arr[i]);
    REP1(i,1,LOG-1) {
      REP1(j,1,n) {
        rmq[i][j] = rmq[i-1][j] & rmq[i-1][j+(1<<(i-1))];
      }
    }
  }
  int qry(int l, int r) {
    int i = __lg(r-l+1);
    r = r - (1 << i) + 1;
    return rmq[i][l] & rmq[i][r];
  }
} rmq;

int N,Q,ip[MAXN];
ll presum[MAXN];
ll ans[MAXN];
vector<pii> qqq[MAXN];

void calc_lseg(int l) {
  if (l == N) return;
  int lb = l+1;
  while(lb < N+1)
  {
    int cur = rmq.qry(l+1, lb);
    int lx = lb, rx = N;
    while(lx < rx)
    {
      int mx = (lx + rx + 1) / 2;
      if(rmq.qry(l+1, mx) == cur)
        lx = mx;
      else
        rx = mx - 1;
    }

    // [lb, lx] : cur

    //cout<<"L "<<l<<" LB "<<lb<<" LX "<<lx<<" CUR "<<cur<<endl;
    tree.upd(lb, lx, -presum[l] + cur);
    lb = lx + 1;
  }
}

void calc()
{
  for (int i=N-1; i>=0; i--) {
    calc_lseg(i);
    for (auto it:qqq[i]) {
      int r = it.F;
      int id = it.S;
      ans[id] = tree.qry(i,r);
    }
  }
}

int main() {
  IOS;
  cin>>N>>Q;
  REP1(i,1,N) {
    cin>>ip[i];
    presum[i] = presum[i-1] + ip[i];
  }
  rmq.init(N,ip);
  tree.init(N+1, presum);

  REP1(i,1,Q) {
    int l,r;
    cin>>l>>r;
    l--;
    qqq[l].PB({r,i});
  }

  calc();

  REP1(i,1,Q) cout<<ans[i]<<"\n";

  return 0;
}

