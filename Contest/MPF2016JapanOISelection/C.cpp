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

#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> set_t;

const int minN = 200005;

int N,M,ip[minN];
set_t st, num;

int main() {
  IOS;
  while (cin>>N>>M) {
    int ts = 0;
    REP1(i,1,N) cin>>ip[i];
    st.clear();
    num.clear();

    REP1(i,2,N) {
      st.insert(pii{min(ip[i], ip[i-1]), ts++});
    }
    REP1(i,1,N) {
      num.insert(pii{ip[i], ts++});
    }

    REP(_,M) {
      //output();
      int t,a,b;
      cin>>t;
      if (t == 1) {
        cin>>a;
        int res = N-num.order_of_key(pii{a, -1});
        //cout<<res<<" ";
        res -= N-1-st.order_of_key(pii{a,-1});
        //cout<<N-1-st.order_of_key(pii{a,-1})<<endl;
        cout<<res<<"\n";
      } else {
        cin>>a>>b;
        if (a != 1) {
          st.erase(st.lower_bound(pii{min(ip[a], ip[a-1]),-1}));
          st.insert(pii{min(b, ip[a-1]),ts++});
        }
        if (a != N) {
          st.erase(st.lower_bound(pii{min(ip[a], ip[a+1]),-1}));
          st.insert(pii{min(b, ip[a+1]),ts++});
        }
        num.erase(num.lower_bound(pii{ip[a], -1}));
        ip[a] = b;
        num.insert(pii{b, ts++});
      }
    }
  }

  return 0;
}

