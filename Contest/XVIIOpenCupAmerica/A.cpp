//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(x) memset((x),0,sizeof(x))
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

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
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

const int INF = 1029384756;
const int MAX = 100005;
using A34 = array<int,3>;

int N, dp1[MAX], dp2[MAX], presum[MAX];
string ip[304];

void solve(vector<A34> vec, int dp[]) {
  sort(ALL(vec));
  int n = SZ(vec);
  //cout<<vec<<endl;
  REP(i,n) {
    int a = vec[i][0];
    int b = vec[i][1];
    int c = vec[i][2];
    for (int j=MAX-b-1; j>=a; j--) {
      assert(j+b<MAX);
      dp[j+b] = max(dp[j+b], dp[j]+c);
    }
  }
  //REP(i,15) cout<<dp[i]<<" ";
  //cout<<endl;
}
int main() {
  IOS;
  cin>>N;
  vector<A34> vec1, vec2;
  REP(i,N) {
    string s;
    cin>>s;
    presum[0] = 0;
    int sz = SZ(s);

    REP(j,sz) {
      int v = 1;
      if (s[j] == ')') v = -1;
      presum[j+1] = presum[j] + v;
    }
    A34 item;
    item[0] = -presum[sz];
    item[1] = presum[sz];
    item[2] = sz;
    REP(j,sz) item[0] = max(item[0], -presum[j]);

    if (presum[sz] >= 0) {
      vec1.PB(item);
    } else {
      reverse(ALL(s));
      REP(j,sz) {
        int v = 1;
        if (s[j] == '(') v = -1;
        presum[j+1] = presum[j] + v;
      }
      item[0] = -presum[sz];
      item[1] = presum[sz];
      item[2] = sz;
      REP(j,sz) item[0] = max(item[0], -presum[j]);
      vec2.PB(item);
    }
  }

  REP(i,MAX) dp1[i] = dp2[i] = -INF;
  dp1[0] = dp2[0] = 0;

  solve(vec1,dp1);
  solve(vec2,dp2);

  int ans = 0;
  REP(i,MAX) ans = max(ans, dp1[i] + dp2[i]);
  cout<<ans<<endl;

  return 0;
}

