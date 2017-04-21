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

const int MAXN = 200005;
const int MEM = 16000004;
const int INF = -1029384756;
const int MAX = 1000000000;

int N,val[MAXN],sz[MAXN];
int vid[MAXN];
vector<int> child[MAXN];
multiset<int> vset[MAXN];

void DFS(int u) {
  sz[u] = 1;
  int bv = -1;
  for (auto v:child[u]) {
    DFS(v);
    sz[u] += sz[v];
    if (bv == -1 or sz[v] > sz[bv]) {
      bv = v;
    }
  }
  int &id = vid[u];
  if (bv == -1) id = u;
  else id = vid[bv];
  for (auto v:child[u]) {
    if (bv == v) continue;
    for (auto it:vset[vid[v]]) {
      vset[id].insert(it);
    }
  }
  auto it = vset[id].lower_bound(val[u]);
  if (it == end(vset[id])) {
    //cout<<u<<" NEW "<<val[u]<<endl;
    vset[id].insert(val[u]);
  } else {
    //cout<<u<<" MOVE "<<*it<<" -> "<<val[u]<<endl;
    vset[id].erase(it);
    vset[id].insert(val[u]);
  }
}
int main() {
  IOS;
  cin>>N;
  REP1(i,1,N) {
    int f;
    cin>>val[i]>>f;
    child[f].PB(i);
  }
  DFS(1);
  int ans = SZ(vset[vid[1]]);
  cout<<ans<<endl;

  return 0;
}

