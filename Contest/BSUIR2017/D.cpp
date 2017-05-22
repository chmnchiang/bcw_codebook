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

const int MX = 202020;
const ll INF = 1LL<<60;
const ll MOD = 1000000007;

struct Lisan {
  vector<int> seq;
  void init() { seq.clear(); }
  void add(int x) { seq.PB(x); }
  void make() {
    sort(ALL(seq));
    seq.resize(unique(ALL(seq))-begin(seq));
  }
  int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq)+1; }
} ls;
struct BIT {
  ll bit[MX];
  void add(int x, int v) {
    x += 2;
    v %= MOD;
    for (int i=x; i>0; i-=i&-i) {
      bit[i] += v;
      if (bit[i] >= MOD) bit[i] -= MOD;
    }
  }
  ll qry(int x) {
    x += 2;
    ll res = 0;
    for (int i=x; i<MX; i+=i&-i) {
      res += bit[i];
      if (res >= MOD) res -= MOD;
    }
    return res;
  }
} bit1, bit2;

int N;
ll dp[MX][2], dp2[MX][2];
vector<pll> ip;

int cost(int i, int k) {
  int res = 0;
  int a = ip[i].F;
  int b = ip[k].F;
  if (a > b) swap(a,b);
  for (int j=i; j<N; j++) if (a < ip[j].F and ip[j].F < b) res++;
  return res;
}
void build_dp() {
  static ll mx[MX],mn[MX];
  mx[N] = -INF;
  mn[N] = INF;
  for (int i=N-1; i>=0; i--) {
    mx[i] = max(mx[i+1], ip[i].F);
    mn[i] = min(mn[i+1], ip[i].F);
  }
  memset(dp,0,sizeof(dp));
  dp[N-1][0] = dp[N-1][1] = 1;
  bit1.add(ip[N-1].F, 1);
  bit2.add(ip[N-1].F, 1);
  for (int i=N-2; i>=0; i--) {
    int j = i;
    while (j>=0 and ip[i].S == ip[j].S) j--;
    j++;
    REP1(k,j,i) {
      dp[k][0] += bit1.qry(ip[k].F+1);
      dp[k][1] += (bit2.qry(0) - bit2.qry(ip[k].F) + MOD);
    }
    if (mx[i+1] <= ip[i].F) {
      REP1(k,j,i) dp[k][0]++;
    }
    if (mn[i+1] >= ip[i].F) {
      REP1(k,j,i) dp[k][1]++;
    }

    REP1(k,j,i) {
      dp[k][0] %= MOD;
      dp[k][1] %= MOD;
      bit1.add(ip[k].F, dp[k][1]);
      bit2.add(ip[k].F, dp[k][0]);
    }
    i = j;
  }
}

struct BJT {
  ll bit[MX];
  void init(int x) {
    fill(bit, bit+x+5, 0);
  }
  void add(int x, int v) {
    x += 2;
    v %= MOD;
    for (int i=x; i<MX; i+=i&-i) {
      bit[i] += v;
      if (bit[i] >= MOD) bit[i] -= MOD;
    }
  }
  ll qry(int x) {
    x += 2;
    ll res = 0;
    for (int i=x; i>0; i-=i&-i) {
      res += bit[i];
      if (res >= MOD) res -= MOD;
    }
    return res;
  }
} bjtUp, bjtDown, bjtSum2Up, bjtSum2Down, bjtSumUp, bjtSumDown;

struct ABT {
  int a[MX], v[MX];

  void init(int n) {
    fill(a, a+n+5, 0);
    fill(v, v+n+5, 0);
  }

  void add(int l, int r, int k) {
    k %= MOD;
    for (int i=l; i<=r; i++) {
      (v[i] += k * a[i]) %= MOD;
    }
  }

  void adda(int i, int k) {
    (a[i] += k) %= MOD;
  }

  void addv(int i, int k) {
    (v[i] += k) %= MOD;
  }

  int qry(int l, int r) {
    int t = 0;
    for (int i=l; i<=r; i++) {
      (t += v[i]) %= MOD;
    }
    return t;
  }
} tUp, tDown;

void build_dp2() {
  memset(dp2,0,sizeof(dp2));

  bjtSumUp.init(2*N);
  bjtSumDown.init(2*N);
  bjtSum2Up.init(2*N);
  bjtSum2Down.init(2*N);
  bjtUp.init(2*N);
  bjtDown.init(2*N);
  tUp.init(2*N);
  tDown.init(2*N);


  int r = N-1;
  while (r >= 0) {
    int l = r;
    while (l >= 0 and ip[r].S == ip[l].S) l--;
    l++;

    for (int i=l; i<=r; i++) {
      int RK = ip[i].F;
      {
        auto &up = dp2[i][0];
        int a1, a2, a3;
        up = (a1 = bjtSum2Down.qry(2*N) - bjtSum2Down.qry(RK));
        up += (a2 = tDown.qry(RK+1, 2*N));
        up -= (a3 = bjtDown.qry(RK) * (bjtSumDown.qry(2*N) - bjtSumDown.qry(RK))) % MOD;
        up = (up % MOD + MOD) % MOD;
        cout << a1 << ' ' << a2 << ' ' << a3  << ' ' << bjtSumDown.qry(2*N) << endl;
      }

      {
        auto &down = dp2[i][1];
        down = bjtSum2Up.qry(RK-1) - bjtSum2Up.qry(0);
        down -= tUp.qry(0, RK-1);
        down += bjtUp.qry(RK-1) * bjtSumUp.qry(RK-1) % MOD;
        down = (down % MOD + MOD) % MOD;
      }

      //cout << "i = " << i << ": " << dp[i][0] << ' ' << dp[i][1] << endl;
      cout << "i = " << i << ": " << dp2[i][0] << ' ' << dp2[i][1] << endl;
    }

    for (int i=l; i<=r; i++) {
      int RK = ip[i].F;
      bjtUp.add(RK, 1);
      bjtSumUp.add(RK, dp[i][0]);
      bjtSum2Up.add(RK, dp2[i][0]);

      bjtDown.add(RK, 1);
      bjtSumDown.add(RK, dp[i][1]);
      bjtSum2Down.add(RK, dp2[i][1]);

      tUp.add(0, RK+1, 1);
      tDown.add(0, RK, 1);
    }

    for (int i=l; i<=r; i++) {
      int RK = ip[i].F;
      tUp.addv(RK, dp[i][0] * bjtUp.qry(RK));
      tDown.addv(RK, dp[i][1] * bjtDown.qry(RK+1));
      tUp.adda(RK, dp[i][0]);
      tDown.adda(RK, dp[i][1]);
    }

    r = l-1;
  }
}

int main() {
  IOS;
  cin>>N;
  ls.init();
  ip.resize(N);
  for (int i=0; i<N; i++) {
    cin>>ip[i].S>>ip[i].F;
    ls.add(ip[i].F);
    ls.add(ip[i].S);
  }
  sort(ALL(ip));
  ls.make();
  for (auto &i: ip) {
    swap(i.F, i.S);
    i.F = ls.qry(i.F);
    i.S = ls.qry(i.S);
  }
  build_dp();
  for (int i=0; i<N; i++) {
    cout << dp[i][0] << ' ' << dp[i][1] << endl;
  }
  build_dp2();
  int ans = 0;
  REP(i,N) ans += dp2[i][0] + dp2[i][1];
  cout<<ans<<endl;

  return 0;
}

