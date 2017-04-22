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

int N,ip[9][MAXN];
int arr[MAXN];

struct BIT {
  ll bit[MAXN];
  void init() {
    memset(bit,0,sizeof(bit));
  }
  void add(int x, int v) {
    x += 3;
    for (int i=x; i<MAXN; i+=i&-i)
      bit[i] += v;
  }
  ll qry(int x) {
    x += 3;
    ll res = 0;
    for (int i=x; i>0; i-=i&-i) 
      res += bit[i];
    return res;
  }
} bit;

ll calc_rp() {
  ll res = 0;
  bit.init();
  //REP(i,N) cout<<arr[i]<<" ";
  //cout<<endl;
  for (int i=N-1; i>=0; i--) {
    res += bit.qry(arr[i]);
    bit.add(arr[i], 1);
  }
  //cout<<res<<endl;
  return res;
}
void trans(int x[], int y[], int z[]) {
  static int tmp[MAXN];
  REP(i,N) tmp[x[i]] = i;
  REP(i,N) z[i] = tmp[y[i]];
}
ll calc(int a, int b, int c) {
  //cout<<"CALC "<<a<<" "<<b<<" "<<c<<endl;

  ll res = 0;
  trans(ip[a], ip[b], arr);
  res += calc_rp();

  trans(ip[b], ip[c], arr);
  res += calc_rp();

  trans(ip[a], ip[c], arr);
  res += calc_rp();

  //cout<<res<<endl;

  return res;
}
int main() {
  IOS;
  cin>>N;
  REP(i,9) {
    REP(j,N) {
      cin>>ip[i][j];
      ip[i][j]--;
    }
  }

  array<int,3> ans;
  ans[0] = ans[1] = ans[2] = -1;
  ll cost = -1;
  REP1(i,0,8) REP1(j,i+1,8) REP1(k,j+1,8) {
    ll tmp = calc(i,j,k);
    if (tmp > cost) {
      cost = tmp;
      ans[0] = i;
      ans[1] = j;
      ans[2] = k;
    }
  }
  cout<<ans[0]+1<<" "<<ans[1]+1<<" "<<ans[2]+1<<endl;

  return 0;
}

