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

typedef pair<string, ll> psl;

const int MAXN = 42;
const ll MOD = (1LL<<42);

ll tenpow[MAXN];

//void pre()
//{
  //tenpow[0] = 1;
  //for(int i=1; i<MAXN; i++)
    //tenpow[i] = (tenpow[i-1] * 10) % MOD;

  //vector<psl> v1, v2;

  //v1.PB({"", 0});
  //for(int i=0; i<MAXN/2; i++)
  //{
    //vector<psl> v;
    //v.swap(v1);
    //for(auto p: v)
    //{
      //v1.PB({"1"+p.F, (p.S+tenpow[i])%MOD});
      //v1.PB({"2"+p.F, (p.S+2*tenpow[i])%MOD});
    //}
  //}

  //v2.PB({"", 0});
  //for(int i=MAXN/2; i<MAXN; i++)
  //{
    //vector<psl> v;
    //v.swap(v2);
    //for(auto p: v)
    //{
      //v2.PB({"1"+p.F, (p.S+tenpow[i])%MOD});
      //v2.PB({"2"+p.F, (p.S+2*tenpow[i])%MOD});
    //}
  //}

  //map<ll, string> m2;
  //for(auto p: v2)
    //m2[p.S] = p.F;

  //for(auto p: v1)
  //{
    //ll v = (MOD - p.S) % MOD;
    //if(m2.count(v))
    //{
      //string s2 = m2[v];
      //cout<<s2<<p.F<<endl;
      //cout<<p<<" "<<v<<" "<<s2<<endl;
      //return;
    //}
  //}
//}

int main() {
  IOS;

  string s = "212121112121121122111112111211111212122112";

  //pre();
  int N;
  cin>>N;
  cout<<s<<endl;

  return 0;
}

