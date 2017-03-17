//bcw0x1bd2 {{{
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
// Let's Fight! ~OAO~~

using LL = long long;
const int MX = 1.2e6;
const int MD = 1000000007;
struct LISAN {
  vector<int> val;

  void PB(int x) {
    val.PB(x);
  }

  void make() {
    sort(ALL(val));
    val.resize(unique(ALL(val))-begin(val));
  }
  int qry(int x) {
    return lower_bound(ALL(val),x)-begin(val);
  }
} lisan;

inline int lb(int x) {
  return x&(-x);
}

struct BIT {
  int val[MX];
  vector<int> vvv;
  void rollback() {
    for (auto x:vvv) {
      for (int i=x; i<MX; i+=lb(i))
        val[i] = 0;
    }
    vvv.clear();
  }
  void add(int x, int v) {
    x += 5;
    vvv.PB(x);
    for (int i=x; i<MX; i+=lb(i)) {
      (val[i] += v);
      if (val[i] >= MD) val[i] -= MD;
    }
  }

  int qry(int x) {
    x += 5;
    int res = 0;
    for (int i=x; i; i-=lb(i)) {
      (res += val[i]);
      if (res >= MD) res -= MD;
    }
    return res;
  }
} bit;


int N;
vector<LL> A, B;
vector<int> fac[MX];
vector<int> hao[MX];
LL ans[MX];
int phi[MX];

int lis(int id) {
  auto &vec = hao[id];
  int aa = 0;
  for (auto x: vec) {
    int as = bit.qry(x-1)+1;
    (aa += as);
    if (aa >= MD) aa -= MD;
    bit.add(x, as);
  }

  bit.rollback();

  return aa;
}

void init() {

  for (int i=1; i<MX; i++) phi[i] = i;

  for (int i=1; i<MX; i++) {
    for (int j=i; j<MX; j+=i) {
      fac[j].PB(i);
      if (j != i) phi[j] -= phi[i];
    }
  }

}

int main() {
  IOS;
  init();

  cin >> N;
  for (int i=0; i<N; i++) {
    int x;  cin >> x;
//    int x = rand()%1000000000+1;
    lisan.PB(x);
    A.PB(x);
  }

  lisan.make();
  transform(ALL(A), begin(A), [](int x){ return lisan.qry(x); });

  LL mx = 0;
  B.resize(N);
  for (int i=0; i<N; i++) {
    cin >> B[i];
 //   B[i] = 2*2*2*3*3*3*5*7*11;
    mx = max(mx, B[i]);
  }

  for (int i=0; i<N; i++) {
    int x = B[i];
    for (auto f: fac[x]) {
      hao[f].PB(A[i]);
    }
  }

  for (int i=1; i<=mx; i++) {
    ans[i] += 1LL * lis(i) * phi[i];
    ans[i] %= MD;
  }

  LL aa = 0;
  for (int i=0; i<=mx; i++) {
    (aa += ans[i]) %= MD;
  }
  cout << aa << endl;
  

  return 0;
}
