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

const int MAXN = 1024;
const ll MOD = 1000000007;

int N, M;
vector<int> E[MAXN];
ll dp[MAXN][2][MAXN];
ll tmp[MAXN], tmp2[MAXN];
int wei[MAXN];

void mult(ll *a, int n1, ll *b, int n2)
{
  for(int i=0; i<=n1+n2; i++)
    tmp[i] = 0;
  for(int i=0; i<=n1; i++)
    for(int j=0; j<=n2; j++)
      tmp[i+j] = (tmp[i+j] + a[i] * b[j]) % MOD;
  for(int i=0; i<=n1+n2; i++)
    a[i] = tmp[i];
}

void dfs(int v, int p)
{
  wei[v] = 1;
  dp[v][0][0] = dp[v][1][0] = 1;

  for(auto c: E[v])
  {
    if(c == p) continue;
    dfs(c, v);
    int cw = wei[c];
    for(int i=0; i<=cw; i++)
      tmp2[i] = (dp[c][0][i] + dp[c][1][i]) % MOD;
    mult(dp[v][1], wei[v], tmp2, cw);
    for(int i=0; i<=cw; i++)
      tmp2[i] = (2 * dp[c][0][i] + dp[c][1][i] + (i==0 ? 0 : dp[c][1][i-1])) % MOD;
    mult(dp[v][0], wei[v], tmp2, cw);
    wei[v] += cw;
  }

  for(int i=0; i<=wei[v]; i++)
    dp[v][0][i] = (dp[v][0][i] - dp[v][1][i] + MOD) % MOD;
  //assert(dp[v][1][wei[v]] == 0);
  //for(int i=wei[v]; i>=1; i--)
    //dp[v][1][i] = dp[v][1][i-1];
  //dp[v][1][0] = 0;
  //cout<<v<<" WEI "<<wei[v]<<" USE ";
  //for(int i=0; i<=wei[v]; i++) cout<<dp[v][1][i]<<" ";
  //cout<<" NONUSE ";
  //for(int i=0; i<=wei[v]; i++) cout<<dp[v][0][i]<<" ";
  //cout<<endl;
}

ll calc()
{
  dfs(0, -1);
  ll ans = dp[0][0][M];
  if(M > 0) ans = (ans + dp[0][1][M-1]) % MOD;
  if(ans < 0) ans += MOD;
  return ans;
}

int main() {
  IOS;
  cin>>N>>M;
  REP(_,N-1) {
    int u,v;
    cin>>u>>v;
    u--;
    v--;
    E[u].PB(v);
    E[v].PB(u);
  }

  ll ans = calc();
  cout<<ans<<endl;

  return 0;
}

