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

const int MX = 202020;
const int INF = 1029384756;

struct SegmentTree {
  struct Node {
    int val,tag;
    Node () { val = tag = 0; }
  } tree[MX*4];
  int n;
  void init(int tn) {
    n = tn;
    REP(i,n*4) tree[i] = Node();
  }
  void push(int id, int lc, int rc) {
    if (tree[id].tag == 0) return;
    tree[lc].tag += tree[id].tag;
    tree[lc].val += tree[id].tag;
    tree[rc].tag += tree[id].tag;
    tree[rc].val += tree[id].tag;
    tree[id].tag = 0;
  }
  void upd_tree(int l, int r, int x, int v, int id) {
    if (l == r) {
      tree[id].val = v;
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id,lc,rc);
    if (x <= m) upd_tree(l,m,x,v,lc);
    else upd_tree(m+1,r,x,v,rc);
    tree[id].val = min(tree[lc].val, tree[rc].val);
  }
  void add_tree(int l, int r, int ql, int qr, int v, int id) {
    if (r < ql) return;
    if (qr < l) return;
    if (ql <= l and r <= qr) {
      tree[id].val += v;
      tree[id].tag += v;
      return;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id,lc,rc);
    add_tree(l,m,ql,qr,v,lc);
    add_tree(m+1,r,ql,qr,v,rc);
    tree[id].val = min(tree[lc].val, tree[rc].val);
  }
  int qry_tree(int l, int r, int ql, int qr, int id) {
    if (r < ql) return INF;
    if (qr < l) return INF;
    if (ql <= l and r <= qr) {
      return tree[id].val;
    }
    int m = (l+r)/2, lc = id*2, rc = id*2+1;
    push(id,lc,rc);
    return min(qry_tree(l,m,ql,qr,lc), qry_tree(m+1,r,ql,qr,rc));
  }
  void upd(int x, int v) {
    upd_tree(0,n,x,v,1);
  }
  void add(int l, int r, int v) {
    add_tree(0,n,l,r,v,1);
  }
  int qry(int l, int r) {
    return qry_tree(0,n,l,r,1);
  }
} tree;

int C[MX], D[MX];
int H[MX], G[MX];
vector<int> ls[MX];
vector<int> idx;

int main() {
  IOS;

  int N;
  cin >> N;
  for (int i=N-1; i>=0; i--) {
    cin >> C[i] >> H[i];
  }

  for (int i=N-1; i>=0; i--) {
    cin >> D[i] >> G[i];
  }

  tree.init(N+5);

  int j = 0, ans = 0;
  for (int i=0; i<N; i++) {
    while (j < N and H[j] <= G[i]) {
      int c = C[j];
      ls[c].PB(j);
      j++;
    }

    int c = D[i];
    if (SZ(ls[c])) {
      int p = ls[c].back();
      ls[c].pop_back();
      int id = lower_bound(ALL(idx), p) - begin(idx);
      //cout << idx << endl;
      //cout << "P = " << p << ", sz = " << SZ(idx) << endl;
      if (id != SZ(idx)) {
        tree.add(id, SZ(idx)-1, -1);
        //cout << "[-] " << id << " ~ " << SZ(idx)-1 << endl;
      }
      int fl = tree.qry(0, SZ(idx)-1);
      if (fl < 0) {
        if (id != SZ(idx)) {
          tree.add(id, SZ(idx)-1, 1);
        }
      } else {
        ans++;
  //      cout << i << endl;
        continue;
      }
    }

    int t = j - i - 1;
    int s = SZ(idx);
    tree.upd(s, t);
    //cout << "Z = " << tree.qry(s, s) << endl;
    idx.PB(j-1);
  }

  cout << N-ans << endl;



  return 0;
}

