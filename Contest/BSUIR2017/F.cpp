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

const int MAXN = 100005;
const ll INF = 1LL<<50;

int N,prv[3][MAXN][2][2];
ll A[MAXN],dp[3][MAXN][2][2];

void check(int i, int j, int k, int l) {
  assert(0<=i and i<3);
  assert(0<=j and j<MAXN);
  assert(0<=k and k<2);
  assert(0<=l and l<2);
}
int main() {
  IOS;
  cin>>N;
  REP(i,N) cin>>A[i];

  REP(i,3) REP(j,MAXN) REP(k,2) REP(l,2) {
    dp[i][j][k][l] = -INF;
  }

  dp[0][0][0][0] = 0;
  REP(r,3) REP1(i,0,N) REP(x,2) REP(y,2) {

    if (dp[r][i][x][y] != -INF and r<2 and dp[r+1][i][x][y] < dp[r][i][x][y]) {
      dp[r+1][i][x][y] = dp[r][i][x][y];
      prv[r+1][i][x][y] = 1;
    }
    if (dp[r][i][0][x] != -INF and r != 1 and dp[r][i+1][1][x] < dp[r][i][0][x] + A[i]) {
      dp[r][i+1][1][x] = dp[r][i][0][x] + A[i];
      prv[r][i+1][1][x] = 2;
    }
    if (dp[r][i][1][x] != -INF and r != 1 and dp[r][i+1][1][x] < dp[r][i][1][x]) {
      dp[r][i+1][1][x] = dp[r][i][1][x];
      prv[r][i+1][1][x] = 3;
    }
    if (dp[r][i][0][x] != -INF and r != 1 and dp[r][i+1][0][x]< dp[r][i][0][x]) {
      dp[r][i+1][0][x] = dp[r][i][0][x];
      prv[r][i+1][0][x] = 4;
    }
    if (dp[r][i][x][0] != -INF and r == 1 and dp[r][i+1][x][0] < dp[r][i][x][0] + A[i]) {
      dp[r][i+1][x][0] = dp[r][i][x][0] + A[i];
      prv[r][i+1][x][0] = 5;
    }
    if (dp[r][i][x][0] != -INF and r == 1 and dp[r][i+1][x][1] < dp[r][i][x][0]) {
      dp[r][i+1][x][1] = dp[r][i][x][0];
      prv[r][i+1][x][1] = 6;
    }
    if (dp[r][i][x][1] != -INF and r == 1 and dp[r][i+1][x][1] < dp[r][i][x][1] + A[i]) {
      dp[r][i+1][x][1] = dp[r][i][x][1] + A[i];
      prv[r][i+1][x][1] = 7;
    }
  }


  if (dp[2][N][1][1] < dp[2][N][0][0]) {
    if (dp[2][N][0][0] == 0) {
      ll mx = -INF;
      REP(i,N) mx = max(mx, A[i]);
      cout<<mx<<endl;
      cout<<"1 2"<<endl;
    } else {
      int r = 2;
      int i = N;
      int bl=-1, br=-1;
      while (i >= 0) {
        if (prv[r][i][0][0] == 1) {
          r--;
          if (r == 1) br = i-1;
          else bl = i;
        } else {
          i--;
        }
      }
      assert(bl != -1 and br != -1);
      cout<<dp[2][N][0][0]<<endl;
      bl++; br++;
      if (N == 2) {
        cout<<"1 2"<<endl;
      } else if (bl != br) {
        cout<<bl<<" "<<br<<endl;
      } else {
        vector<int> vec;
        REP1(j,1,N) {
          if (j != bl) vec.PB(j);
          if (SZ(vec) >= 2) break;
        }
        assert(SZ(vec) == 2);
        cout<<vec[0]<<" "<<vec[1]<<endl;
      }
    }
  } else {
    int r = 2;
    int i = N;
    int j = 1;
    int k = 1;

    int in = -1, out = -1;
    int bl = 0;
    int br = -1;
    while (i > 0) {
      assert(prv[r][i][j][k]);
      //cout<<r<<" "<<i<<" "<<j<<" "<<k<<" "<<prv[r][i][j][k]<<endl;
      if (prv[r][i][j][k] == 1) {
        r--;
        if (r == 1) br = i-1;
        else bl = i;
      } else if (prv[r][i][j][k] == 2) {
        i--;
        j = 0;
        in = i;
      } else if (prv[r][i][j][k] == 3) {
        i--;
      } else if (prv[r][i][j][k] == 4) {
        i--;
      } else if (prv[r][i][j][k] == 5) {
        i--;
      } else if (prv[r][i][j][k] == 6) {
        i--;
        k = 0;
        out = i;
      } else if (prv[r][i][j][k] == 7) {
        i--;
      }
    }
    assert(in != -1);
    assert(out != -1);
    ll sum = 0;
    REP1(z,bl,br) sum += A[z];
    sum += A[in];
    sum -= A[out];
    cout<<sum<<endl;
    assert(sum == dp[2][N][1][1]); 
    cout<<in+1<<" "<<out+1<<endl;
  }

  return 0;
}

