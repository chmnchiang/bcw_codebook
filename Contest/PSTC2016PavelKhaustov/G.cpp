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
// Let's Fight! !111111111!

static const int S = 30;
static const int K = 4;

struct Event {
  int cmd,x,y;
};

vector<int> BITS;

struct LAJI {
  int xmask;
  vector<int> seq, one[K];
  void init() {
    xmask = 0;
    seq.clear();
    REP(i,K) one[i].clear();
  }
  void append(int v) {
    v ^= xmask;
    seq.PB(v);
    REP(i,K) {  
      if ((v>>BITS[i]) & 1) one[i].PB(SZ(seq)-1);
    }
  }
  void rox(ll x) { xmask ^= x; }
  ll qry(int k) {
    if (k <= 0) return 0;
    ll res = 0;
    REP(i,K) {  
      int x = lower_bound(ALL(one[i]), k) - begin(one[i]);
      if ((xmask >> BITS[i]) & 1) x = k - x;
      res += (1LL << BITS[i]) * x;
    }
    return res;
  }
  vector<int> pop_all() {
    vector<int> res;
    for (auto i:seq) res.PB(i^xmask);
    init();
    return res;
  }
} laji;

int mem = 1;
struct SELE {
  static const int MEM = S * 200005;
  struct Node {
    int tot, lv;
    int ch[2], cnt[K];
    Node () {
      ch[0] = ch[1] = tot = lv = 0;
      REP(i,K) cnt[i] = 0;
    }
    void swap_child() {
      swap(ch[0], ch[1]);
    }
  } tree[MEM];

  int root, gxor, sxor, res[K][2];

  int get_node() {
    tree[mem] = Node();
    assert(mem < MEM);
    return mem++;
  }
  void init() {
    mem = 1;
    root = get_node();
    tree[root].lv = S-1;
    gxor = 0;
    sxor = 0;
  }
  void add(int v) {
    v ^= sxor;
    static vector<int> vec;
    vec.clear();
    int id = root;
    for (int i=S-1; i>=0; i--) {
      int b = (v >> i) & 1;
      auto &ch = tree[id].ch[b];
      if (ch == 0) ch = get_node();
      tree[ch].lv = i-1;
      vec.PB(id);
      id = ch;
    }
    vec.PB(id);
    for (auto i:vec) {
      tree[i].tot++;
      REP(j,K) {
        if ((v>>BITS[j])&1) tree[i].cnt[j]++;
      }
    }
  }
  void rox(ll x) {
    gxor ^= x;
  }
  void sort() {
    sxor ^= gxor;
    gxor = 0;
  }
  int size() { return tree[root].tot; }

  ll qry(int k) {
    memset(res, 0, sizeof(res));
    int id = root;
    while (id) {
      if (tree[id].lv == -1 or tree[id].tot <= k) {

        REP(i,K) {
          res[i][0] += min(tree[id].tot - tree[id].cnt[i], k);
          res[i][1] += min(tree[id].cnt[i], k);
        }
        break;
      }
      int lc = tree[id].ch[0 ^ ((sxor>>tree[id].lv)&1)];
      int rc = tree[id].ch[1 ^ ((sxor>>tree[id].lv)&1)];
      if (tree[lc].tot >= k) id = lc;
      else {
        REP(i,K) {
          res[i][0] += tree[lc].tot - tree[lc].cnt[i];
          res[i][1] += tree[lc].cnt[i];
        }
        id = rc;
        k -= tree[lc].tot;
      }
    }
    //qry_trie(k, root);
    ll r = 0;
    REP(i,K) {
      if (((sxor^gxor) >> BITS[i]) & 1) r += (1LL<<BITS[i]) * res[i][0];
      else r += (1LL<<BITS[i]) * res[i][1];
    }
    return r;
  }
} hitler;

const int MAXN = 200005;

int N,Q,ip[MAXN];
ll ans[MAXN];
vector<Event> events;

ll query_psum(int k) {
  return hitler.qry(k) + laji.qry(k-hitler.size());
}
int main() {
  IOS;
  cin>>N;
  REP(i,N) {
    cin>>ip[i];
  }
  cin>>Q;
  REP(_,Q) {
    int cmd,x,y;
    cin>>cmd;
    x = y = 0;
    if (cmd == 1 or cmd == 3) {
      cin>>x;
    } else if (cmd == 2) {
      cin>>x>>y;
    }
    events.PB({cmd,x,y});
  }
  int nans = 0;
  for (int bb=0; bb<S; bb+=K) {
    BITS.clear();
    REP(i,K) BITS.PB(bb+i);

    laji.init();
    REP(i,N) {
      laji.append(ip[i]);
    }
    hitler.init();

    nans = 0;
    for (auto eee:events) {
      int cmd = eee.cmd, x = eee.x, y = eee.y;
      if (cmd == 1) {
        laji.append(x);
      } else if (cmd == 2) {
        //cout<<"QUERY "<<x<<" "<<y<<" "<<(query_psum(y) - query_psum(x-1))<<endl;
        ans[nans++] += (query_psum(y) - query_psum(x-1));
      } else if (cmd == 3) {
        laji.rox(x);
        hitler.rox(x);
      } else {
        auto vec = laji.pop_all();
        hitler.sort();
        sort(ALL(vec));
        for (auto i:vec) hitler.add(i);
      }
    }
  }

  REP(i,nans) cout<<ans[i]<<"\n";


  return 0;
}


