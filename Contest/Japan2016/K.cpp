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

const int MAXN = 42;

int N;
ll arr[MAXN];
int z[MAXN];

ll eval(string s)
{
  ll cur = 1LL<<42;
  char lst = s[0];
  bool st = false;
  ll res = 0;

  for(auto c: s)
  {
    if(c != lst)
      st = true;
    if(st) cur >>= 1;
    res += cur * (c == 'W' ? 1 : -1);
  }
  return res;
}

map<ll, int> ex(int n, vector<pll> v)
{
  map<ll, int> s;
  for(int i=0; i<(1<<n); i++)
  {
    ll x = 0;
    int p = 0;
    for(int j=0; j<n; j++)
      if(i&(1<<j))
        x += v[j].F, p += v[j].S;
    s[x] = max(s[x], p);
  }
  return s;
}

int calc()
{
  int M = N / 2;
  int L = N - M;
  vector<pll> s1, s2;
  for(int i=0; i<M; i++)
    s1.PB({arr[i], z[i]});
  for(int i=M; i<N; i++)
    s2.PB({arr[i], z[i]});

  map<ll, int> m1, m2;
  m1 = ex(M, s1);
  m2 = ex(L, s2);

  int ans = 0;
  for(auto x: m1)
  {
    if(m2.count(-x.F))
    {
      ans = max(ans, x.S + m2[-x.F]);
    }
  }
  return ans;
}

int main() {
  IOS;
  
  while(cin>>N)
  {
    for(int i=0; i<N; i++)
    {
      string s;
      cin>>s;
      arr[i] = eval(s);
      z[i] = SZ(s);
    }

    int ans = calc();
    cout<<ans<<endl;
  }

  return 0;
}

