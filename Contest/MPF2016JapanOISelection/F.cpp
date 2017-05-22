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

const int MAXN = 400005;
const int SQ = 777;

struct Block {
  priority_queue<int> vpq;
  vector<int> q,v,todo;
  void init() {
    while (!vpq.empty()) vpq.pop();
    q.clear(); v.clear(); todo.clear();
  }
  void add(int x) {
    v.PB(x);
  }
  void make() {
    while (!vpq.empty()) vpq.pop();
    for (auto i:v) {
      vpq.push(i);
    }
  }
  int go(int l, int r, int p) {
    l = max(l, 0);
    r = min(r, SZ(v)-1);
    for (int i=l; i<=r; i++) {
      if (v[i] > p) {
        swap(v[i], p);
      }
    }
    make();
    return p;
  }
  int go(int p) {
    if (vpq.top() <= p) return p;
    todo.PB(p);
    int res = vpq.top();
    vpq.pop();
    vpq.push(p);
    return res;
  }
  void apply() {
    if (todo.empty()) return;
    priority_queue<int> pq;
    for (auto i:todo) pq.push(-i);
    todo.clear();

    for (auto &i:v) {
      int x = -pq.top();
      if (x >= i) continue;
      pq.pop();
      pq.push(-i);
      i = x;
    }

    make();
  }

} blk[SQ];

int N,M,B,ip[MAXN];

int main() {
  IOS;
  while (cin>>N>>M) {
    REP(i,SQ) blk[i].init();
    REP(i,N) {
      cin>>ip[i];
      blk[i/SQ].add(ip[i]);
    }

    B = (N-1) / SQ;
    REP1(i,0,B) blk[i].make();

    while (M--) {
      int s,t,p;
      cin>>s>>t>>p;
      s--; t--;

      int sid = s / SQ;
      int tid = t / SQ;

      blk[sid].apply();
      blk[tid].apply();
      if (s <= t) {
        if (sid == tid) {
          p = blk[sid].go(s-sid*SQ,t-tid*SQ,p);
        } else {
          p = blk[sid].go(s-sid*SQ,MAXN,p);
          REP1(i,sid+1,tid-1) {
            p = blk[i].go(p);
          }
          p = blk[tid].go(0,t-tid*SQ,p);
        }
      } else {
        p = blk[sid].go(s-sid*SQ,MAXN,p);
        REP1(i,sid+1,B) {
          p = blk[i].go(p);
        }
        REP1(i,0,tid-1) {
          p = blk[i].go(p);
        }
        p = blk[tid].go(0, t-tid*SQ, p);
      }
      cout<<p<<endl;
    }
  }

  return 0;
}

