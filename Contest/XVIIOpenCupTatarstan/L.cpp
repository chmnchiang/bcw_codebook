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

const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
const int MAXN = 2005;

struct DisjoinSet {
  int sz[MAXN*MAXN], fa[MAXN*MAXN];
  void init() {
    REP(i,MAXN*MAXN) fa[i]=i, sz[i]=1;
  }
  int f(int x) { return x == fa[x] ? x : fa[x] = f(fa[x]); }
  void uni(int x, int y) {
    x = f(x);
    y = f(y);
    if (x == y) return;
    fa[y] = x;
    sz[x] += sz[y];
    sz[y] = 0;
  }
} djs;

int R,C,atR[MAXN],atC[MAXN];
string mp[MAXN];

bool inr(int x, int y) {
  return 0 <= x and x < R and 0 <= y and y < C;
}
int gid(int x, int y) { return x * C + y; }
int main() {
  IOS;
  cin>>R>>C;
  djs.init();
  REP(i,R) {
    cin>>mp[i];
  }
  memset(atR, -1, sizeof(atR));
  memset(atC, -1, sizeof(atC));

  REP(i,R) {
    REP(j,C) {
      if (mp[i][j] == '+') {
        atR[i] = j;
        atC[j] = i;
        REP(d,4) {
          int x = i;
          int y = j;
          while (true) {
            x += dir[d][0];
            y += dir[d][1];
            if (!inr(x,y)) break;
            if (mp[x][y] == '+') {
              djs.uni(gid(i,j), gid(x,y));
              break;
            }
          }
        }
      }
    }
  }

  int ans = 0;
  pii pt;

  REP(i,R) REP(j,C) {
    if (mp[i][j] == '+') continue;
    int tmp = 0;
    int a = atR[i] == -1 ? -1 : gid(i, atR[i]);
    int b = atC[j] == -1 ? -1 : gid(atC[j], j);
    if (a >= 0) a = djs.f(a);
    if (b >= 0) b = djs.f(b);
    tmp = a >= 0 ? djs.sz[a] : 0;
    if (a != b) tmp += b >= 0 ? djs.sz[b] : 0;

    if (tmp > ans) {
      ans = tmp;
      pt = pii(i+1,j+1);
    }
  }

  cout<<ans<<endl;
  if (ans) cout<<pt.F<<" "<<pt.S<<endl;

  return 0;
}

