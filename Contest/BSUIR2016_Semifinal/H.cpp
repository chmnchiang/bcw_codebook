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
const int S = 63;
const ll MOD = 1000000007;

int ip[S];
ll dp[S][2][2];

ll go(int p, int x, int any) {
  if (p == -1) return x;
  ll &res = dp[p][x][any];
  if (res != -1) return res;
  res = 0;
  if (any) {
    res = go(p-1,x,1) + go(p-1,(x+1)&1,1);
  } else {
    REP1(i,0,ip[p]) {
      res += go(p-1,(x+i)&1,i<ip[p]);
    }
  }
  return res;
}
ll calc(ll x) {
  memset(dp,-1,sizeof(dp));
  REP(i,S) ip[i] = (x >> i) & 1;
  ll res = go(S-1,0,0);

  /*
  ll a = 0;
  REP1(i,1,x) {
    if (__builtin_popcount(i) & 1) a++;
  }
  assert(a == res);
  */

  return res;
}
int main() {
  IOS;
  int N;
  cin>>N;
  ll A = 0;
  ll B = 0;
  ll ans = 0;
  REP(_,N) {
    ll L,R;
    cin>>L>>R;
    ll x = calc(R) - calc(L-1);
    ll y = R - L + 1 - x;
    x %= MOD;
    y %= MOD;
    A += x;
    B += y;
    ans += x * y % MOD;
  }
  A %= MOD;
  B %= MOD;
  ans %= MOD;
  ans = A * B % MOD - ans;
  ans %= MOD;
  ans = (ans + MOD) % MOD;

  cout<<ans<<endl;


  return 0;
}

