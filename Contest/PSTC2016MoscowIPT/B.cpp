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

const int MAXN = 500005;
const int INF = 2147483647;

struct SegmentTree {
  struct Node {
    int mask, tmask, tag, val;
  } tree[MAXN*4];
  
  void init(int l, int r, int id, int arr[]) {
    tree[id].mask = -1;
    tree[id].tag = 0;
    tree[id].tmask = 0;
    if (l == r) {
      tree[id].val = arr[l];
      return;
    }
    int m = (l + r) / 2, lc = id * 2, rc = id * 2 + 1;
    init(l, m, lc, arr);
    init(m+1, r, rc, arr);
    tree[id].val = min(tree[lc].val, tree[rc].val);
  }

  void push(int id, int ch, int cl, int cr) {
    tree[ch].tag = (tree[ch].tag & ~tree[id].tmask) + (tree[id].tag & tree[id].tmask);
    tree[ch].tmask |= tree[id].tmask;
    tree[ch].val = (tree[ch].val & ~tree[ch].tmask) + (tree[ch].tag & tree[ch].tmask);
  }

  void push(int id, int lc, int rc, int l, int r) {
    if (!tree[id].tmask) return;
    int m = (l + r) / 2;
    push(id, lc, l, m);
    push(id, rc, m+1, r);
    tree[id].tag = 0;
    tree[id].tmask = 0;
  }

  void update(int l, int r, int ql, int qr, int mask, int val, int id) {
    if (qr < l) return;
    if (r < ql) return;
    int m = (l + r) / 2, lc = id * 2, rc = id * 2 + 1;
    if (l < r) push(id, lc, rc, l, r);
    if (ql <= l and r <= qr) {
      tree[id].tag = (tree[id].tag & mask) + (val & ~mask);
      tree[id].tmask |= ~mask;
      tree[id].val = (tree[id].val & mask) + (val & ~mask);
      if (l < r and (tree[id].mask & mask) != tree[id].mask) {
        push(id, lc, rc, l, r);

        if ((tree[lc].mask & mask) != tree[lc].mask)
          update(l, m, ql, qr, mask, val, lc);
        if ((tree[rc].mask & mask) != tree[rc].mask)
          update(m+1, r, ql, qr, mask, val, rc);

        tree[id].val = min(tree[lc].val, tree[rc].val);
      }
      tree[id].mask &= mask;
    } else {
      update(l, m, ql, qr, mask, val, lc);
      update(m+1, r, ql, qr, mask, val, rc);
      tree[id].mask |= ~mask;
      tree[id].val = min(tree[lc].val, tree[rc].val);
    }
  }

  int query(int l, int r, int ql, int qr, int id) {
    if (qr < l) return INF;
    if (r < ql) return INF;
    if (ql <= l and r <= qr) return tree[id].val;
    int m = (l + r) / 2, lc = id * 2, rc = id * 2 + 1;
    push(id, lc, rc, l, r);
    return min(query(l, m, ql, qr, lc), query(m+1, r, ql, qr, rc));
  }

} tree;

int N,Q,ip[MAXN];

int main() {
  IOS;
  cin>>N;
  REP1(i,1,N) cin>>ip[i];
  tree.init(1,N,1,ip);
  cin>>Q;
  REP(_,Q) {
    int l,r,v;
    string s;
    cin>>s>>l>>r;
    if (s == "&") {
      cin>>v;
      int mask = -1;
      REP(i,32) if (!(v & (1<<i))) mask -= 1<<i;
      tree.update(1,N,l,r,mask,v,1);
    } else if (s == "|") {
      cin>>v;
      int mask = -1;
      REP(i,32) if (v & (1<<i)) mask -= 1<<i;
      tree.update(1,N,l,r,mask,v,1);
    } else if (s == "?") {
      int res = tree.query(1,N,l,r,1);
      cout<<res<<endl;
    } else {
      assert(false);
    }
  }

  return 0;
}


