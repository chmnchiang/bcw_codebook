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

const int MAXN = 2010101;
const ll MOD = 1000000007;

int N, K, L;
ll fact[MAXN], ifact[MAXN];

ll lpow(ll a, ll p)
{
  ll ret = 1, cur = a%MOD;
  while(p)
  {
    if(p&1LL)
      ret = ret * cur % MOD;
    cur = cur * cur % MOD;
    p >>= 1;
  }
  return ret;
}

ll linv(ll a)
{
  return lpow(a, MOD-2);
}

void pre()
{
  fact[0] = ifact[0] = 1;
  for(int i=1; i<MAXN; i++)
  {
    fact[i] = (fact[i-1] * i) % MOD;
    ifact[i] = linv(fact[i]);
  }
}

ll comb(ll n, ll m)
{
  if(n < 0 or m < 0 or m > n) return 0;
  return fact[n] * (ifact[n-m] * ifact[m] % MOD) % MOD;
}

ll calc()
{
  ll ans = 0;
  if(L == N)
  {
    for(int i=1; i<=N; i++)
      ans += lpow(K, __gcd(i, N));
    ans %= MOD;
    ans = ans * linv(N) % MOD;
  }
  else if(L % 2 == 0)
  {
    ans = comb(N+K-1, N);
  }
  else
  {
    ans = comb(N+K-1, N) + comb(K, N);
  }

  return ans % MOD;
}

int main() {
  IOS;
  pre();

  while(cin>>N>>K>>L)
  {
    ll ans = calc();
    cout<<ans<<endl;
  }

  return 0;
}


