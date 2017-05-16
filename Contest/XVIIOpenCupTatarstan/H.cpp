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

const int MAXN = 10005;
const int INF = 1029384756;

int N,M,st,ed,nv;
pii ip[MAXN];
int dp[MAXN][4];
vector<pii> vec[MAXN];

int main() {
  IOS;
  cin>>N>>M;
  cin>>st>>ed;

  REP1(i,2,N) {
    cin>>ip[i].F>>ip[i].S;
  }
  nv = 0;
  for (int i=2; i<=N;) {
    if (ip[i].F == 1) {
      vec[++nv].PB(pii(ip[i].S, ip[i].S));
      i++;
      continue;
    }
    int j = i;
    int mxl,mnl,mxr,mnr;
    mxl = mxr = 0;
    mnl = mnr = 1029384756;
    while (j <= N and ip[j].F == 2) {
      int x = ip[j].S;
      int y = M - ip[j].S + 1;
      if (x > y) swap(x, y);
      mxl = max(mxl, x);
      mnl = min(mnl, x);
      mxr = max(mxr, y);
      mnr = min(mnr, y);
      j++;
    }
    ++nv;
    vec[nv].PB(pii(mnl,mxl));
    vec[nv].PB(pii(mxl,mnl));
    vec[nv].PB(pii(mnr,mxr));
    vec[nv].PB(pii(mxr,mnr));
    i = j;
  }
  REP(i,MAXN) REP(j,4) dp[i][j] = INF;
  vec[0].PB(pii(st,st));
  dp[0][0] = 0;

  REP1(i,1,nv) {
    int sz = SZ(vec[i]);
    int psz = SZ(vec[i-1]);
    REP(j,sz) {
      REP(k,psz) {
        int prve = vec[i-1][k].S;
        int s = vec[i][j].F;
        int e = vec[i][j].S;
        dp[i][j] = min(dp[i][j], dp[i-1][k] + abs(s-prve) + abs(e-s));
      }
    }
  }

  int ans = INF;
  int sz = SZ(vec[nv]);
  REP(j,sz) {
    ans = min(ans, dp[nv][j] + abs(vec[nv][j].S - ed));
  }
  cout<<ans<<endl;

  return 0;
}

