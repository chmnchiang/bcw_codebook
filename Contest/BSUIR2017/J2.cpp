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
typedef __int128 lll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<pll, pll> ppp;

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

//#undef HAO123

const ll INF = 1LL<<40;

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
pll operator-(pll a){return {-a.F, -a.S};}
pll operator*(ll a, pll b){return {a*b.F, a*b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
ll cross(pll a, pll b, pll o){return cross(a-o, b-o);}
ll abs2(pll a){return dot(a, a);}

pll _A[3], pt[3];
int _cnt;

pll gcd(ll a, ll b){
	if(b == 0) return make_pair(1, 0);
	else{
		ll p = a / b;
		pll q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}

pll interPnt(pll p1, pll p2, pll q1, pll q2)
{
	ll f1 = cross(p2, q1, p1);
	ll f2 = -cross(p2, q2, p1);
	ll f = (f1 + f2);

  pll res = f2 * q1 + f1 * q2;
  res.F /= f;
  res.S /= f;
  return res;
}

ppp vPts(pll d, ll v)
{
  pll n = {d.S, -d.F};
  int s1 = (d.F >= 0 ? 1 : -1);
  int s2 = (d.S >= 0 ? 1 : -1);
  pll off = gcd(abs(d.F), abs(d.S));
  off.F *= s1;
  off.S *= s2;
  assert(d.F * off.F + d.S * off.S == 1);
  pll p = v * off;
  ll dif = ((lll)n.F * p.F + (lll)n.S * p.S) / abs2(n);
  p = p - dif * n;
  if(dot(n, p) > 0)
    p = p - n;
  //cout<<"QRY "<<d<<" "<<v<<endl;
  //cout<<dot(n, p)<<" / "<<dot(n, n+p)<<endl;
  //cout<<dot(p, d)<<" "<<p<<" "<<p+n<<endl;
  return {p, p+n};
}

pll valIntPnt(pll d1, ll v1, pll d2, ll v2)
{
  ppp p1 = vPts(d1, v1), p2 = vPts(d2, v2);
  return interPnt(p1.F, p1.S, p2.F, p2.S);
}

int query(pll a, pll b)
{
  _cnt++;
  assert(_cnt <= 600);
  assert(abs(a.F) <= 420000 and abs(a.S) <= 420000);
  assert(abs(b.F) <= 420000 and abs(b.S) <= 420000);
#ifdef HAO123
  pll d = b - a;
  int z[3];
  for(int i=0; i<3; i++)
  {
    ll c = cross(d, _A[i]-a);
    if(c == 0) return 0;
    z[i] = (cross(d, _A[i]-a)>=0 ? -1 : 1);
  }

  if(z[0] != z[1] or z[0] != z[2] or z[1] != z[2])
    return 0;
  else
    return z[0];
#else
  cout<<"Q "<<a.F<<" "<<a.S<<" "<<b.F<<" "<<b.S<<endl;
  string s;
  cin>>s;
  if(s[0] == '-') return -1;
  else if(s[0] == '+') return 1;
  else return 0;
#endif
}

void answer(vector<pll> vec)
{
  for(int i=0; i<3; i++)
    assert(abs(vec[i].F) <= 100000 and abs(vec[i].S) <= 100000);
#ifdef HAO123
  int perm[3];
  for(int i=0; i<3; i++)
    perm[i] = i;

  bool ok = false;
  do
  {
    bool good = true;
    for(int i=0; i<3; i++)
      if(vec[perm[i]] == _A[i])
        good = false;
    if(good) ok = true;
  }while(next_permutation(perm, perm+3));
  assert(ok);
#else
  cout<<"A";
  for(int i=0; i<3; i++)
    cout<<" "<<vec[i].F<<" "<<vec[i].S;
  cout<<endl;
#endif
}

ll query_off(pll dir)
{
  ll g = __gcd(abs(dir.F), abs(dir.S));
  pll d = {dir.F/g, dir.S/g};
  ll lim = 150000 * sqrt(abs2(d));

  ll lb = -lim, rb = lim;
  while(lb < rb)
  {
    ll mb = (lb + rb + 2*INF) / 2 - INF;
    ppp p = vPts(d, mb);
    //cout<<d<<" "<<mb<<" PTS "<<p<<endl;
    int res = query(p.F, p.S);    
    if(res >= 0) rb = mb;
    else lb = mb + 1;
  }

  return lb * g;
}

void calc()
{
  _cnt = 0;
  pll d1 = {1, 0}, d2 = {200001, 1};
  ll v1 = query_off(d1);
  ll v2 = query_off(d2);
  pt[0] = valIntPnt(d1, v1, d2, v2);

  d1 = {-1, 0}, d2 = {-200001, -1};
  v1 = query_off(d1);
  v2 = query_off(d2);
  pt[1] = valIntPnt(d1, v1, d2, v2);

  pll n = pt[1] - pt[0];
  ll g = __gcd(abs(n.F), abs(n.S));
  n.F /= g;
  n.S /= g;
  pll d = {-n.S, n.F};
  v1 = -query_off(-d);

  if(v1 == dot(d, pt[0]))
  {
    //cout<<"SWAP!!"<<endl;
    swap(pt[0], pt[1]);
    d = -d;
    n = -n;
    v1 = -query_off(-d);
  }

  //cout<<"V1 "<<v1<<" / "<<dot(d, pt[0])<<endl;
  //for(int i=0; i<3; i++) cout<<dot(d, _A[i])<<" ";
  //cout<<endl;

  pll p = vPts(d, v1).F;
  ll lim = 150000 / sqrt(abs2(n)) + 1;
  ll lb = -lim, rb = lim;
  while(lb < rb)
  {
    ll mb = (lb + rb + 2*INF) / 2 - INF;
    pll q = p + mb * n;
    pll nn = q - pt[1];
    ll gg = __gcd(abs(nn.F), abs(nn.S));
    nn.F /= gg;
    nn.S /= gg;
    pll dd = {-nn.S, nn.F};
    ll vv = dot(dd, q);
    ppp zz = vPts(dd, vv-1);
    ll res = query(zz.F, zz.S);
    if(res == -1)
      rb = mb;
    else
      lb = mb + 1;
  }

  //cout<<"LIM = "<<lim<<" / "<<(p-lim*n)<<" ~ "<<(p+lim*n)<<endl;
  //cout<<"LB = "<<lb<<endl;
  pt[2] = p + lb * n;

  vector<pll> vec;
  for(int i=0; i<3; i++)
    vec.PB(pt[i]);
  answer(vec);
}

int main() {
  IOS;
  srand(time(0));
  //srand(13);
  cout<<fixed<<setprecision(19);

#ifdef HAO123
  for(int i=0; i<3; i++)
  {
    _A[i].F = rand() % 200000 - 100000;
    _A[i].S = rand() % 200000 - 100000;
  }
  for(int i=0; i<3; i++) cout<<_A[i]<<" / ";
  cout<<endl;
#endif

  calc();

  return 0;
}

