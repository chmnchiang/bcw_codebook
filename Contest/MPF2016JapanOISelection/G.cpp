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

#define int long long
const int MX = 111111;
int V;
using pii = pair<int, int>;
int nx[MX];
vector<pii> el[MX];
bool vt[MX];
bool isl[MX];
int dp[MX];
int dp2[MX];
int lpe[MX];

bool simple() {
  int u = 1;
  for (int i=0; i<V; i++) {
    if (vt[u]) return false;
    vt[u] = 1;
    u = nx[u];
  }
  return (u == 1);
}

void dfs(int u) {
  vt[u] = 1;
  int bs = 0;
  dp[u] = 0;
  for (auto e: el[u]) {
    int v = e.F;
    if (isl[v]) continue;

    dfs(v);
    dp[u] += dp[v];
    bs = max(bs, e.S);
  }
  dp[u] += bs;
}

int calc(int u) {
  vector<int> vec;
  while (!vt[u]) {
    vt[u] = 1;
    vec.PB(u);
    u = nx[u];
  }

  vector<int> loop;
  while (1) {
    int v = vec.back();
    vec.pop_back();
    loop.PB(v);
    if (v == u) break;
  }


  for (auto v: loop) {
    isl[v] = 1;
  }

  int shao = 0;
  for (auto v: loop) {
    dfs(v);
    for (auto e: el[v]) {
      int w = e.F;
      if (isl[w]) {
        lpe[v] = e.S;
      } else {
        dp2[v] += dp[w];
      }
    }
    shao += max(dp[v], dp2[v] + lpe[v]);
    //cout << v << ":  " << dp[v] << ' ' << dp2[v] << endl;
  }

  int ba = 0;
  
  for (auto v: loop) {
    int t = shao;
    t -= max(dp[v], dp2[v] + lpe[v]);
    t += dp[v];
    ba = max(ba, t);
  }
  //cout << ba << endl;

  return ba;
}

int32_t main() {
  IOS;

  cin >> V;
  int tot = 0;
  for (int i=1; i<=V; i++) {
    int v, c; cin >> v >> c;
    nx[i] = v;
    el[v].PB({i, c});
    tot += c;
  }
  
  if (simple()) {
    cout << 0 << endl;
    return 0;
  }
  fill(vt, vt+V+5, 0);

  int ans = 0;
  for (int i=1; i<=V; i++) {
    if (!vt[i]) {
      ans += calc(i);
    }
  }

  cout << tot - ans << endl;
  return 0;
}

