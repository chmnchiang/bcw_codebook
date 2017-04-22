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

const ll MOD = 1000000007;
const int MAXN = 205;
const int MAXK = 27;

int N, M, K;
string ss[MAXN];
char kc[MAXN];
ll qq[MAXN], gg[MAXN], q[MAXN], g[MAXN];
int ord[MAXN];
map<char, int> smp;
ll ssum[MAXN][MAXN][MAXK];
ll s[MAXN][MAXK], t[MAXN][MAXK];
ll lb[MAXK], rb[MAXK];
ll cnt[MAXN];
ll badcnt;

bool cmp(int a, int b)
{
  return qq[a] < qq[b];
}

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

inline void inccnt(int pos)
{
  //cout<<pos<<" : "<<cnt[pos]<<" -> "<<cnt[pos]+1<<endl;
  if(cnt[pos] == 0) badcnt++;
  cnt[pos]++;
}

inline void deccnt(int pos)
{
  //cout<<pos<<" : "<<cnt[pos]<<" -> "<<cnt[pos]-1<<endl;
  cnt[pos]--;
  if(cnt[pos] == 0) badcnt--;
}

ll calc2()
{
  for(int i=0; i<=M; i++)
  {
    t[i][0] = 0;
    for(int j=1; j<=K; j++)
      t[i][j] = t[i][j-1] + s[i][j-1];
    cnt[i] = 0;
  }

  //cout<<"S"<<endl;
  //for(int i=0; i<K; i++){for(int j=0; j<=M; j++) cout<<s[j][i]<<" "; cout<<endl;}
  //cout<<"T"<<endl;
  //for(int i=0; i<K; i++){for(int j=0; j<=M; j++) cout<<t[j][i]<<" "; cout<<endl;}

  badcnt = 0;
  ll ans = 0;

  for(int i=0; i<K; i++)
  {
    lb[i] = 1;
    rb[i] = 0;
  }
  for(int cur=0; cur<M; cur++)
  {
    for(int j=0; j<K; j++)
    {
      while(lb[j] < M+1 and s[lb[j]][j] <= s[cur][j])
      {
        if(lb[j] <= rb[j])
          deccnt(lb[j]);
        lb[j]++;
      }
      while(rb[j] < M and t[rb[j]+1][j] < t[cur][j] + q[j])
      {
        if(lb[j] <= rb[j] + 1)
          inccnt(rb[j]+1);
        rb[j]++;
      }
    }
    //cout<<"CUR = "<<cur<<endl;
    //for(int k=0; k<K; k++)
    //{
      //cout<<k<<" : "<<lb[k]<<" ~ "<<rb[k]<<endl;
    //}
    ll val = (M - cur) - badcnt;
    //cout<<"BAD "<<badcnt<<" GOOD "<<val<<" !!!!!!!!!!!!!"<<endl;
    ans += val;
  }

  return ans;
}

ll calc()
{
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<=K; j++)
      ssum[i+1][0][j] = 0;
    for(int j=1; j<=M; j++)
    {
      for(int k=0; k<=K; k++)
        ssum[i+1][j][k] = ssum[i+1][j-1][k];
      int c = smp[ss[i][j-1]];
      ssum[i+1][j][c] += g[c];
    }
  }
  for(int i=1; i<=N; i++)
    for(int j=0; j<=M; j++)
      for(int k=0; k<=K; k++)
        ssum[i][j][k] += ssum[i-1][j][k];

  ll ans = 0;
  for(int l=0; l<N; l++)
  {
    for(int r=l+1; r<=N; r++)
    {
      for(int i=0; i<=M; i++)
        for(int j=0; j<=K; j++)
          s[i][j] = ssum[r][i][j] - ssum[l][i][j];
      ans += calc2();
    }
  }

  return ans;
}


int main() {
  IOS;

  cin>>N>>M;
  for(int i=0; i<N; i++)
    cin>>ss[i];
  cin>>K;
  for(int i=0; i<K; i++)
  {
    char c;
    cin>>c>>qq[i]>>gg[i];
    kc[i] = c;
  }

  for(int i=0; i<K; i++)
    ord[i] = i;
  sort(ord, ord+K, cmp);

  for(int i=0; i<K; i++)
  {
    int v = ord[i];
    q[i] = qq[v];
    g[i] = gg[v];
    smp[kc[v]] = i;
  }

  ll ans = calc();
  cout<<ans<<endl;

  return 0;
}

