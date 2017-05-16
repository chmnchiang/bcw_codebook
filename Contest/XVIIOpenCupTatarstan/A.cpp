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
typedef pair<ll, int> pli;

const ll INF = 3E18;

vector<pli> vec;

void pre()
{
  ll ps[] = {2, 3, 5, 7, 11, 13};
  vec.PB({1, 0});
  for(auto p: ps)
  {
    ll res = 1;
    for(int i=0; i<p; i++)
      res *= p;

    for(int j=0; j<100; j++)
    {
      vector<pli> nvec;
      for(auto pr: vec)
      {
        ll a = pr.F;
        if(a <= INF/res)
        {
          nvec.PB({a*res, pr.S+1});
        }
      }
      for(auto x: nvec)
        vec.PB(x);
      nvec.clear();
      sort(ALL(vec));
      vec.resize(unique(ALL(vec)) - vec.begin());
    }
  }
}

int main() {
  IOS;
  pre();

  int k;
  ll r;
  cin>>k>>r;

  vector<ll> ans;
  for(auto p: vec)
  {
    if(p.S == k and p.F <= r)
      ans.PB(p.F);
  }

  int sz = SZ(ans);
  cout<<sz<<endl;
  for(int i=0; i<sz; i++)
    cout<<ans[i]<<(i==sz-1?"\n":" ");

  return 0;
}

