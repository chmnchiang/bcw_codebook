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
typedef pair<ld, ld> pdd;

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

const ld PI = acosl(-1);
const ld EPS = 1E-13;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(ld a, pdd b){return {a*b.F, a*b.S};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
ld abs(pdd a){return sqrtl(dot(a, a));}
pdd unit(pdd a){return (1.l / abs(a)) * a;}
pdd ang(ld th){return {cosl(th), sinl(th)};}

pdd _A[3], pt[3];
int _cnt;
bool _res;

ld frand()
{
  return rand() / (ld)RAND_MAX;
}

pdd round(pdd p)
{
  return {roundl(p.F), roundl(p.S)};
}

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2, bool &res){
	ld f1 = cross(p2, q1, p1);
	ld f2 = -cross(p2, q2, p1);
	ld f = (f1 + f2);

	if(fabsl(f) < EPS) {
		res = false;
    return {};
  }

  res = true;
  return (f2 / f) * q1 + (f1 / f) * q2;
}

int query(pdd a, pdd b)
{
  _cnt++;
  //assert(_cnt <= 600);
  //assert(abs(a.F) <= 420000 and abs(a.S) <= 420000);
  //assert(abs(b.F) <= 420000 and abs(b.S) <= 420000);
#ifdef HAO123
  pdd d = b - a;
  int z[3];
  for(int i=0; i<3; i++)
    z[i] = (cross(d, _A[i]-a)>=0 ? -1 : 1);

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

void answer(vector<pdd> vec)
{
  vector<pii> vi;
  for(int i=0; i<3; i++)
  {
    int a = roundl(vec[i].F), b = roundl(vec[i].S);
    //assert(abs(a) <= 100000 and abs(b) <= 100000);
    vi.PB({a, b});
  }
#ifdef HAO123
  int perm[3];
  for(int i=0; i<3; i++)
    perm[i] = i;

  bool ok = false;
  do
  {
    bool good = true;
    for(int i=0; i<3; i++)
      if(abs(pt[perm[i]] - _A[i]) > EPS)
        good = false;
    if(good) ok = true;
  }while(next_permutation(perm, perm+3));
  assert(ok);
#else
  cout<<"A";
  for(int i=0; i<3; i++)
    cout<<" "<<vi[i].F<<" "<<vi[i].S;
  cout<<endl;
#endif
  exit(0);
}

ld query_off(ld th)
{
  pdd d = ang(th);
  pdd n = {d.S, -d.F};
  ld lb = -200000, rb = 200000;
  for(int i=0; i<90; i++)
  {
    ld mb = (lb + rb) / 2;
    int res = query(mb * d, mb * d + n);
    if(res >= 0) rb = mb;
    else lb = mb;
  }

  return (lb + rb) / 2;
}

pdd AngPnt(ld th1, ld v1, ld th2, ld v2)
{
  pdd d1 = ang(th1), d2 = ang(th2);
  pdd n1 = {d1.S, -d1.F}, n2 = {d2.S, -d2.F};
  pdd p1 = v1 * d1, p2 = v2 * d2;
  pdd q1 = p1 + n1, q2 = p2 + n2;
  return interPnt(p1, q1, p2, q2, _res);
}

ld query_ang(pdd p, ld lb, ld rb)
{
  for(int i=0; i<90; i++)
  {
    ld mb = (lb + rb) / 2;
    pdd d = ang(mb);
    pdd n = {d.S, -d.F};
    pdd p1 = p - EPS * d;
    int res = query(p1, p1+n);
    if(res == -1)
      lb = mb;
    else
      rb = mb;
  }
  return (lb + rb) / 2;
}

void calc()
{
  ld DELTA = 1E-6, DELTA2 = 1E-3;
  ld th = frand() * 2 * PI;
  ld v1 = query_off(th);
  ld v2 = query_off(th + DELTA2);

  pt[0] = AngPnt(th, v1, th+DELTA2, v2);
  th += DELTA2;
  pdd opt = pt[0];
  pt[0] = round(pt[0]);
  assert(abs(opt - pt[0]) < 1E-3);
  //cout<<pt[0]<<endl;

  th = query_ang(pt[0], th, th+PI);
  v1 = dot(ang(th), pt[0]);
  v2 = query_off(th + DELTA);

  pt[1] = AngPnt(th, v1, th+DELTA, v2);
  th += DELTA;
  pt[1] = round(pt[1]);
  //cout<<pt[1]<<endl;

  th = query_ang(pt[1], th, th+PI);
  v1 = dot(ang(th), pt[1]);
  v2 = query_off(th + DELTA);

  pt[2] = AngPnt(th, v1, th+DELTA, v2);
  th += DELTA;
  pt[2] = round(pt[2]);
  //cout<<pt[2]<<endl;

  vector<pdd> vec;
  for(int i=0; i<3; i++)
    vec.PB(pt[i]);
  answer(vec);
}

int main() {
  IOS;
  srand(time(0));
  cout<<fixed<<setprecision(19);

#ifdef HAO123
  for(int i=0; i<3; i++)
  {
    _A[i].F = rand() % 200000 - 100000;
    _A[i].S = rand() % 200000 - 100000;
  }
  //for(int i=0; i<3; i++) cout<<_A[i]<<" / ";
  //cout<<endl;
#endif

  calc();

  return 0;
}

