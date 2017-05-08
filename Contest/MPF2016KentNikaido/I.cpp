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

const int MAXN = 10030303;
const ll MOD = 1000000007;

ll A, B, C, D;
ll fact[MAXN], prod[MAXN];

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
  fact[0] = 1;
  prod[0] = 1;
  for(int i=1; i<MAXN; i++)
  {
    fact[i] = (fact[i-1] * i) % MOD;
    prod[i] = (prod[i-1] * fact[i]) % MOD;
  }
}

ll f(ll a, ll b, ll x=0)
{
  ll ans = prod[a+b-1+x] * linv(prod[a-1+x] * prod[b-1+x] % MOD) % MOD;
  if(x > 0)
    ans = ans * prod[x-1] % MOD;
  return ans;
}

ll calc()
{
  pii p1 = {A, B}, p2 = {C, D};
  if(p1 > p2)
  {
    swap(A, C);
    swap(B, D);
  }

  ll n = 0, func = 0;
  if(B <= D)
  {
    n = C * D;
    func = f(C, D);
  }
  else
  {
    n = A * B + (C-A) * D;
    func = (f(A, B-D) * f(C-A, D) % MOD) * f(A, D, B+C-A-D) % MOD;
  }

  ll ans = fact[n] * linv(func) % MOD;
  return ans;
}

int main() {
  IOS;
  pre();

  int T;
  cin>>T;
  while(T--)
  {
    cin>>A>>B>>C>>D;
    A = A-B+1;
    C = C-D+1;
    ll ans = calc();
    cout<<ans<<"\n";
  }

  return 0;
}


