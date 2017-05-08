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

int N;
vector<int> vec;
map<vector<int>,int>mp;

int go(vector<int> v, int tot) {
  if (tot == 0) return 0;
  sort(ALL(v));
  if (mp.count(v)) return mp[v];
  auto &it = mp[v];
  if (v[0]) {
    for (auto &i:v) i--;
    tot -= SZ(v);
    if (!go(v, tot)) return it = 1;
    for (auto &i:v) i++;
    tot += SZ(v);
  }

  for (auto &i:v) {
    if (!i) continue;
    i--;
    if (!go(v, tot-1)) return it = 1;
    i++;
  }

  return it = 0;
}

int main() {
  IOS;
  cin>>N;
  vec.resize(N);
  int tot = 0;
  int mn = 333;
  int odd = 0;
  REP(i,N) {
    cin>>vec[i];
    mn = min(mn, vec[i]);
    tot += vec[i];
    if (vec[i] & 1) odd++;
  }
//  int tmp = go(vec, tot);
  
  int res;
  if (N % 2 == 0) {
    if (mn & 1) res = 1;
    else res = (mn + odd) & 1;
  } else {
    res = tot & 1;
  }
//  cout<<tmp<<endl;
//  assert(tmp == res);
  if (res) cout<<"Iori"<<endl;
  else cout<<"Yayoi"<<endl;

  return 0;
}


