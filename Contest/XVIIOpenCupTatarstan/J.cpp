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

const int MAXN = 2020;
const int MAXM = 101010;
const ll INF = 1LL<<60;

int N, M, K;
int arr[MAXM];
int sz[MAXN], lst[MAXN];
ll dp[MAXM];

ll calc()
{
  for(int i=0; i<M; i++)
    sz[i] = lst[i] = 0;
  for(int i=0; i<N; i++)
  {
    int x = arr[i];
    sz[x]++;
    lst[x] = i+1;
  }

  for(int i=0; i<=K; i++)
    dp[i] = INF;
  dp[0] = 0;

  for(int i=0; i<M; i++)
  {
    int x = sz[i];
    if(x == 0) continue;
    ll l = lst[i];
    //cout<<"Group "<<i<<" Sz "<<x<<" Lst "<<l<<endl;
    for(int j=K-x; j>=0; j--)
      dp[j+x] = min(dp[j+x], max(dp[j], l));
  }

  ll ans = INF;

  for(int a=0; a<=K; a++)
  {
    int b = N - a;
    if(b > K) continue;
    if(dp[a] == INF) continue;
    ll cst = dp[a] * a + (ll)N * b;
    //cout<<a<<" LST "<<dp[a]<<" CST "<<cst<<endl;
    ans = min(ans, cst);
  }

  if(ans == INF)
    ans = -1;
  return ans;
}

int main() {
  IOS;

  while(cin>>N>>M>>K)
  {
    for(int i=0; i<N; i++)
    {
      cin>>arr[i];
      arr[i]--;
    }

    ll ans = calc();
    cout<<ans<<endl;
  }

  return 0;
}

