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

const int MAXN = 2020;
const ll MOD = 1000000007;

int N;
string arr[3];
ll dp[MAXN][2][MAXN*3], tmp[MAXN*3], tmp2[MAXN*3];
int s[MAXN];
ll fact[MAXN*3];

ll lpow(ll a, ll p)
{
  ll ret = 1, cur = a % MOD;
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
  for(int i=1; i<MAXN*3; i++)
    fact[i] = (fact[i-1] * i) % MOD;
}

void trUp(ll v[MAXN*3], int sz)
{
  if(sz == 0) sz = 1;
  for(int i=0; i<=sz+1; i++)
  {
    tmp[i] = v[i];
    v[i] = 0;
  }

  //cout<<"XD ";
  //for(int i=0; i<=sz; i++) cout<<tmp[i]<<" ";
  //cout<<endl;

  ll sum = 0;
  for(int i=sz-1; i>=0; i--)
  {
    sum = (sum + tmp[i]) % MOD;
    v[i] = sum;
  }
  //cout<<"Res ";
  //for(int i=0; i<=sz+1; i++) cout<<v[i]<<" ";
  //cout<<endl;
}

void trDown(ll v[MAXN*3], int sz)
{
  if(sz == 0)
  {
    trUp(v, 1);
    return;
  }
  for(int i=0; i<=sz+1; i++)
  {
    tmp[i] = v[i];
    v[i] = 0;
  }

  ll sum = 0;
  for(int i=0; i<=sz; i++)
  {
    v[i] = sum;
    sum = (sum + tmp[i]) % MOD;
  }
}

void addUp(ll v[MAXN*3], int sz)
{
  for(int i=0; i<=sz+1; i++)
  {
    tmp[i] = v[i];
    v[i] = 0;
  }

  for(int i=0; i<=sz; i++)
  {
    v[i+1] = (v[i+1] + tmp[i] * (i+1)) % MOD;
  }
}

void addAny(ll v[MAXN*3], int sz)
{
  for(int i=0; i<=sz+1; i++)
  {
    tmp[i] = v[i];
    v[i] = 0;
  }

  for(int i=0; i<=sz; i++)
  {
    v[i+1] = (v[i+1] + tmp[i] * (i+1)) % MOD;
    v[i] = (v[i] + tmp[i] * (sz-i)) % MOD;
  }
}

ll calcint(int lb, int rb)
{
  for(int i=lb; i<=rb; i++)
    for(int j=0; j<2; j++)
      for(int k=0; k<MAXN*3; k++)
        dp[i][j][k] = 0;

  if(lb == 0)
    dp[lb][1][0] = 1;
  else
    dp[lb][0][0] = 1;

  for(int i=lb; i<rb; i++)
  {
    int sz = s[i] - s[lb];
    int nsz = s[i+1] - s[lb];
    int n = nsz - sz - 1;
    for(int j=0; j<2; j++)
    {
      for(int f=0; f<2; f++)
      {
        for(int k=0; k<=sz; k++)
          tmp2[k] = dp[i][f][k];
        int csz = sz;

        if(f == 0) trDown(tmp2, csz);
        else trUp(tmp2, csz);
        csz++;

        for(int x=0; x<n; x++)
        {
          if(j == 1 and f == 0) addAny(tmp2, csz);
          else addUp(tmp2, csz);
          csz++;
        }

        //cout<<i+1<<" "<<j<<" From "<<f<<" : ";
        //for(int k=0; k<=csz; k++) cout<<tmp2[k]<<" ";
        //cout<<endl;

        for(int k=0; k<=csz; k++)
          dp[i+1][j][k] = (dp[i+1][j][k] + tmp2[k]) % MOD;
      }
      //cout<<i+1<<" "<<j<<" // ";
      //for(int k=0; k<=nsz; k++) cout<<dp[i+1][j][k]<<" ";
      //cout<<endl;
    }
  }

  int z = (rb==N ? 0 : 1);
  ll ans = 0;
  for(int k=0; k<=s[rb]-s[lb]; k++)
    ans += dp[rb][z][k];

  ans %= MOD;

  return ans;
}

ll calc()
{
  for(int i=0; i<3; i+=2)
  {
    for(int j=0; j<N; j++)
    {
      if(arr[i][j] == 'x')
      {
        if(j==0 or arr[i][j-1] == 'x') return 0;
        if(j==N-1 or arr[i][j+1] == 'x') return 0;
      }
    }
  }

  s[0] = 0;
  for(int i=0; i<N; i++)
  {
    s[i+1] = s[i];
    for(int j=0; j<3; j++)
      if(arr[j][i] == 'x')
        s[i+1]++;
  }

  vector<int> vs;
  ll res = 1;

  int pos = 0;
  while(pos < N)
  {
    if(arr[1][pos] == 'o')
    {
      int n = s[pos+1] - s[pos];
      for(int i=0; i<n; i++)
        vs.PB(1);
      pos++;
      continue;
    }

    int rb = pos + 1;
    while(rb < N and arr[1][rb] == 'x')
      rb++;

    ll rv = calcint(pos, rb);
    int num = s[rb] - s[pos];
    vs.PB(num);
    res = (res * rv) % MOD;

    //cout<<"["<<pos<<","<<rb<<") : "<<rv<<" ("<<num<<")"<<endl;

    pos = rb;
  }

  ll sum = 0, pd = 1;
  for(auto x: vs)
  {
    sum += x;
    pd = (pd * fact[x]) % MOD;
  }

  ll ans = (fact[sum] * linv(pd)) % MOD;
  ans = (ans * res) % MOD;

  return ans;
}

int main() {
  IOS;
  pre();

  while(cin>>N)
  {
    for(int i=0; i<3; i++)
      cin>>arr[i];

    ll ans = calc();
    cout<<ans<<endl;
  }

  return 0;
}

