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

const int MAXN = 305;
const int MAXM = 1005;

struct Block {
  vector<pii> vec;
} blk[MAXM];

int N,M;
bitset<MAXN> can[MAXN];
int fin[MAXN][MAXN],finb[MAXM];
vector<int> pset[MAXN][MAXN];
map<string, int> mp;

int getid(string s) {
  if (mp.count(s)) return mp[s];
  int sz = SZ(mp);
  mp[s] = sz;
  assert(sz < MAXN);
  return sz;
}

int main() {
  IOS;
  {
    string A,B;
    cin>>A>>B;
    int u = getid(A);
    int v = getid(B);
    can[u][v] = 1;
    //cout<<u<<" "<<v<<endl;
  }
  cin>>M;
  REP(i,M) {
    int x;
    cin>>x;
    blk[i].vec.resize(x);
    REP(j,x) {
      string A,B;
      cin>>A>>B;
      int u = getid(A);
      int v = getid(B);
      blk[i].vec[j].F = u;
      blk[i].vec[j].S = v;
      pset[u][v].PB(i);
    }
    //cout<<"BLOCK "<<i<<" : "<<blk[i].vec<<endl;
  }

  N = SZ(mp);
  while (true) {
    vector<int> todo;
    REP(i,N) REP(j,N) {
      if (fin[i][j]) continue;
      if (!can[i][j]) continue;
      fin[i][j] = 1;
      for (auto it:pset[i][j]) {
        if (finb[it]) continue;
        finb[it] = 1;
        todo.PB(it);
      }
    }
    if (todo.empty()) break;

    for (auto bid:todo) {
      for (auto z:blk[bid].vec) {
        int u = z.F;
        int v = z.S;
        can[u][v] = 1;
        can[u] |= can[v];
        REP(i,N) {
          if (can[i][u]) can[i] |= can[u];
        }
      }
    }
  }

  int ok = 1;
  REP(i,N) if (can[i][i]) ok = 0;

  REP(i,M) {
    if (finb[i]) continue;
    for (auto it:blk[i].vec) {
      int u = it.F;
      int v = it.S;
      if (can[u][v]) ok = 0;
    }
  }
  if (ok) cout<<"Yes"<<endl;
  else cout<<"No"<<endl;

  return 0;
}

