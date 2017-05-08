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

const int MAXN = 102020;
const ll MOD = 1000000007;

int H, W, N;
int hass[MAXN], wass[MAXN];
bool h0[MAXN], h1[MAXN], w0[MAXN], w1[MAXN];
bool h0s[MAXN], h1s[MAXN], h0e[MAXN], h1e[MAXN];
bool w0s[MAXN], w1s[MAXN], w0e[MAXN], w1e[MAXN];
ll twopow[MAXN];

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
  twopow[0] = 1;
  for(int i=1; i<MAXN; i++)
    twopow[i] = (twopow[i-1] * 2) % MOD;
}

ll calc()
{
  for(int i=0; i<H; i++)
  {
    h0[i] = h1[i] = true;
    if(hass[i] == i%2)
      h1[i] = false;
    else if(hass[i] == 1-(i%2))
      h0[i] = false;
  }
  h0s[0] = h1s[0] = true;
  for(int i=0; i<H; i++)
  {
    h0s[i+1] = h0s[i] and h0[i];
    h1s[i+1] = h1s[i] and h1[i];
  }
  h0e[H] = h1e[H] = true;
  for(int i=H-1; i>=0; i--)
  {
    h0e[i] = h0e[i+1] and h0[i];
    h1e[i] = h1e[i+1] and h1[i];
  }

  for(int i=0; i<W; i++)
  {
    w0[i] = w1[i] = true;
    if(wass[i] == i%2)
      w1[i] = false;
    else if(wass[i] == 1-(i%2))
      w0[i] = false;
  }
  w0s[0] = w1s[0] = true;
  for(int i=0; i<W; i++)
  {
    w0s[i+1] = w0s[i] and w0[i];
    w1s[i+1] = w1s[i] and w1[i];
  }
  w0e[W] = w1e[W] = true;
  for(int i=W-1; i>=0; i--)
  {
    w0e[i] = w0e[i+1] and w0[i];
    w1e[i] = w1e[i+1] and w1[i];
  }

  int hfree = 0, wfree = 0;
  for(int i=0; i<H; i++)
    if(hass[i] == -1)
      hfree++;
  for(int i=0; i<W; i++)
    if(wass[i] == -1)
      wfree++;

  //for(int i=0; i<H; i++){cout<<hass[i]<<" ";}cout<<endl;
  //for(int i=0; i<W; i++){cout<<wass[i]<<" ";}cout<<endl;
  //for(int i=0; i<H; i++){cout<<h0[i]<<" ";}cout<<endl;
  //for(int i=0; i<H; i++){cout<<h1[i]<<" ";}cout<<endl;
  //for(int i=0; i<W; i++){cout<<w0[i]<<" ";}cout<<endl;
  //for(int i=0; i<W; i++){cout<<w1[i]<<" ";}cout<<endl;

  ll ans = 0;
  if(h0s[H]) ans += twopow[wfree];
  if(h1s[H]) ans += twopow[wfree];
  if(w0s[W]) ans += twopow[hfree];
  if(w1s[W]) ans += twopow[hfree];
  if(h0s[H] and w0s[W]) ans--;
  if(h0s[H] and w1s[W]) ans--;
  if(h1s[H] and w0s[W]) ans--;
  if(h1s[H] and w1s[W]) ans--;

  ll h10 = 0, h01 = 0, w10 = 0, w01 = 0;
  for(int i=1; i<H; i++)
  {
    if(h1s[i] and h0e[i]) h10++;
    if(h0s[i] and h1e[i]) h01++;
  }
  for(int i=1; i<W; i++)
  {
    if(w1s[i] and w0e[i]) w10++;
    if(w0s[i] and w1e[i]) w01++;
  }

  ans += h10 * w01 + h01 * w10;

  ans %= MOD;
  if(ans < 0) ans += MOD;
  return ans;
}

int main() {
  IOS;
  pre();

  while(cin>>H>>W>>N)
  {
    for(int i=0; i<H; i++)
      hass[i] = -1;
    for(int i=0; i<W; i++)
      wass[i] = -1;

    bool hungshihaowentiJ111111111J = false;
    for(int i=0; i<N; i++)
    {
      int r, c, d;
      cin>>r>>c>>d;
      r--;
      c--;
      int hv = (d == 2 or d == 3), wv = (d == 3 or d == 4);
      hv ^= (c%2);
      wv ^= (r%2);
      if(hass[r] == 1-hv)
        hungshihaowentiJ111111111J = true;
      else
        hass[r] = hv;
      if(wass[c] == 1-wv)
        hungshihaowentiJ111111111J = true;
      else
        wass[c] = wv;
    }

    if(hungshihaowentiJ111111111J)
    {
      cout<<0<<endl;
    }
    else
    {
      ll ans = calc();
      cout<<ans<<endl;
    }
  }

  return 0;
}


