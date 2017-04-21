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

const int MAXN = 100005;
const int INF = 1029384756;

struct BIT {
  int bit[MAXN];
  void add(int x, int v) {
    x += 2;
    for (int i=x; i<MAXN; i+=i&-i)
      bit[i] += v;
  }
  int qry(int x) {
    x += 2;
    int res = 0;
    for (int i=x; i>0; i-=i&-i)
      res += bit[i];
    return res;
  }
} bit;

#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

int N,K,val[MAXN],presum[MAXN],cost[MAXN];
vector<pii> seq;
int at[MAXN];
string ip;
set_t st;

int calc(int pos) {
  int hao = (presum[0] - presum[pos]) % 2 == 0 ? 0 : 1;
  return max(K - (presum[0] + presum[N] - 2 * presum[pos]) / 2 - hao, 0);
  return max(K - ((presum[0] - presum[pos] + 1) / 2 + (presum[N] - presum[pos] + 1) / 2), 0);
  const int KOKO = 2;
  return KOKO;
}
int main() {
  IOS;

  ll base = 0;
  cin>>N>>K;
  cin>>ip;
  REP(i,N) {
    cin>>cost[i];
    val[i] = ip[i] == '(' ? 1 : -1;
    if (cost[i] < 0) {
      base += cost[i];
      cost[i] *= -1;
      val[i] *= -1;
    }
    seq.PB({cost[i],i});
  }
  sort(ALL(seq));
  REP(i,N) at[seq[i].S] = i;
  K++;

  REP(i,N) {
    presum[i+1] = presum[i] + val[i];
  }

  int ans = INF;


  REP(i,N) {
    if (val[i] > 0) continue;
    int j = at[i];
    bit.add(j, cost[i]);
    st.insert(j);
  }

  //REP1(i,0,N) {
    //dump(i,calc(i));
  //}

  if (SZ(st) >= calc(0)) {
    int zz = *st.find_by_order(calc(0)-1);
    ans = min(ans, bit.qry(zz));
  }

  REP(i,N) {
    int j = at[i];
    if (val[i] > 0) {
      bit.add(j, cost[i]);
      st.insert(j);
    } else {
      bit.add(j, -cost[i]);
      st.erase(j);
    }
    if (SZ(st) >= calc(i+1)) {
      int zz = *st.find_by_order(calc(i+1)-1);
      //dump(i,calc(i+1),bit.qry(zz));
      ans = min(ans, bit.qry(zz));
    }
  }

  if (N & 1) ans = 0;

  if (ans == INF) {
    cout<<"?"<<endl;
  } else {
    ans += base;
    cout<<ans<<endl;
  }

  return 0;
}

