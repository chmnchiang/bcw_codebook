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

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pip;

const int MAXN = 1010;
const int MAXF = 2048;
const ll MOD = 1000210433;
const ll ALPHA = 3;
const pii BAD = {0x34021501, 34021501};

int N, A, M;
ll X;
ll OFF;
map<int, pii> mp;
ll dp[MAXN], tmp[MAXN];
ll arr[MAXF], brr[MAXF];
ll fact[MAXN], mfact[2*MAXN];
map<int, int> rmp;
map<pip, int> _f;

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

ll omega[MAXF+1];
void pre_fft()
{
  assert((MOD-1) % MAXF == 0);
  ll r = lpow(ALPHA, (MOD-1)/MAXF);
  for(int i=0; i<=MAXF; i++)
    omega[i] = lpow(r, i);
}
void fft(int n, ll a[], bool inv=false)
{
  int basic = MAXF / n;
  int theta = basic;
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      ll w = omega[inv ? MAXF-(i*theta%MAXF) : i*theta%MAXF];
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        ll x = (a[j] - a[k] + MOD) % MOD;
        (a[j] += a[k]) %= MOD;
        a[k] = w * x % MOD;
      }
    }
    theta = (theta * 2) % MAXF;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  ll ninv = linv(n);
  if (inv)
    for (i = 0; i < n; i++)
      a[i] = (a[i] * ninv) % MOD;
}

void setX(ll x)
{
  X = max(0LL, x - MAXN);
  mfact[0] = 1;
  for(int i=1; i<2*MAXN; i++)
    mfact[i] = (mfact[i-1] * (X+i)) % MOD;
}

ll comb(int n, int m)
{
  if(n < 0 or m < 0 or m > n) return 0;
  ll ret = mfact[n-X] * linv(fact[m] * mfact[n-m-X] % MOD) % MOD;
  //cout<<"C("<<n<<","<<m<<") = "<<ret<<endl;
  return ret;
}

ll f(int n, int m, int l)
{
  if(n < 0) return 0;
  if(l == 0) return n == 0;

  pip pr = {n, {m, l}};
  if(_f.count(pr)) return _f[pr];

  //cout<<"Query : M = "<<m<<" , L = "<<l<<endl;

  setX(m);
  for(int nn=0; nn<MAXN; nn++)
  {
    pip pts = {nn, {m, l}};
    int lim = min(m, nn/(l+1));
    ll ans = 0;
    for(int i=0; i<=lim; i++)
    {
      ll val = comb(m, i) * comb(m+nn-i*(l+1)-1, nn-i*(l+1)) % MOD;
      if(i%2)
        val = -val;
      ans += val;
    }
    ans %= MOD;
    if(ans < 0) ans += MOD;
    //if(nn < 5) cout<<"FF "<<pts<<" : "<<ans<<endl;
    _f[pts] = ans;
  }

  return _f[pr];
}

void prepre()
{
  fact[0] = 1;
  for(int i=1; i<MAXN; i++)
    fact[i] = (fact[i-1] * i) % MOD;
}

void pre()
{
  mp.clear();
  mp[0] = {0, MAXN-5};
  mp[N] = {0, 0};
}

void update(int lb, int rb, int l, int r)
{
  if(!mp.count(lb))
    mp[lb] = BAD;
  if(!mp.count(rb))
    mp[rb] = BAD;
  pii lst = BAD;
  for(auto &p: mp)
  {
    if(p.S == BAD)
      p.S = lst;
    lst = p.S;
  }
  for(auto &p: mp)
    if(lb <= p.F and p.F < rb)
      p.S = {l, r};
}

void calc()
{
  OFF = 0;
  rmp.clear();
  int llst = -1;
  pii lpr;
  for(auto &p: mp)
  {
    int len = p.F - llst;
    if(llst != -1)
    {
      int dif = lpr.S - lpr.F;
      OFF += (ll)lpr.F * len;
      rmp[dif] += len;
    }
    llst = p.F;
    lpr = p.S;
  }

  //for(auto p: rmp) cout<<p<<" ";
  //cout<<endl<<" OFF "<<OFF<<endl;
  for(int j=0; j<MAXN; j++)
    dp[j] = 0;
  dp[0] = 1;

  for(auto p: rmp)
  {
    int x = p.S, del = p.F;
    swap(dp, tmp);
    for(int j=0; j<MAXN; j++)
      dp[j] = 0;

    for(int j=0; j<MAXF; j++)
      arr[j] = brr[j] = 0;
    for(int j=0; j<MAXN; j++)
      arr[j] = tmp[j];

    for(int k=0; k<MAXN; k++)
    {
      ll ff = f(k, x, del);
      brr[k] = ff;
      //if(k < 5)cout<<"F "<<k<<","<<x<<","<<del<<" = "<<ff<<endl;
      //for(int j=0; j+k<MAXN; j++)
        //dp[j+k] = (dp[j+k] + tmp[j] * ff) % MOD;
    }
    fft(MAXF, arr);
    fft(MAXF, brr);
    for(int i=0; i<MAXF; i++)
      arr[i] = (arr[i] * brr[i]) % MOD;
    fft(MAXF, arr, true);
    for(int j=0; j<MAXN; j++)
      dp[j] = arr[j];
  }
}

ll query()
{
  //cout<<"A "<<A<<" OFF "<<OFF<<endl;
  if(A < OFF) return 0;
  return dp[A-OFF];
}

int main() {
  IOS;
  prepre();
  pre_fft();

  while(cin>>N>>A>>M)
  {
    pre();
    calc();

    for(int i=0; i<M; i++)
    {
      int op;
      cin>>op;
      if(op == 1)
      {
        int lb, rb, l, r;
        cin>>lb>>rb>>l>>r;
        lb--;
        update(lb, rb, l, r);
        calc();
      }
      else
      {
        cin>>A;
      }
      ll ans = query();
      cout<<ans<<"\n";;
    }
  }

  return 0;
}

