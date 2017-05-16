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
typedef pair<ll, ll> pll;

pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
pll operator*(ll a, pll b){return {a*b.F, a*b.S};}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}

ll A, B;

pll gcd(ll a, ll b){
	if(b == 0) return make_pair(1, 0);
	else{
		ll p = a / b;
		pll q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}

pll get(ll a, ll b)
{
  pll p = gcd(a, b);
  //cout<<a * p.F + b * p.S<<endl;
  p = {-p.S, p.F};
  //cout<<a * p.S - b * p.F<<endl;
  while(p.F < 0 or p.S < 0)
  {
    p.F += a;
    p.S += b;
  }
  //cout<<a * p.S - b * p.F<<endl;
  return p;
}

vector<pll> calc()
{
  vector<pll> res;

  ll g = __gcd(A, B);
  //cout<<"G = "<<g<<endl;
  if(g < 45000)
  {
    pll p = get(A/g, B/g);
    res.PB({0, 0});
    res.PB({A, B});
    res.PB(p);
  }
  else
  {
    res.PB({0, 0});
    res.PB({A, B-1});
    res.PB({A/g, B/g});
    res.PB({A-1, B});
  }

  ll area = 0;
  int sz = SZ(res);
  for(int i=0; i<sz; i++)
  {
    assert(0 <= res[i].F and res[i].F <= A and 0 <= res[i].S and res[i].S <= B);
    area += cross(res[i], res[(i+1)%sz]);
  }
  //cout<<"A = "<<area<<endl;
  assert(0 < area and area < 50000);

  return res;
}

int main() {
  IOS;

  int T;
  cin>>T;
  while(T--)
  {
    cin>>A>>B;
    //A = rand() % 1000000000;
    //B = rand() % 1000000000;
    //cout<<pll(A, B)<<endl;
    vector<pll> res = calc();
    cout<<SZ(res)<<endl;
    for(auto p: res)
      cout<<p.F<<" "<<p.S<<endl;
  }

  return 0;
}

