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

typedef double ld;
typedef pair<ld, ld> pdd;
typedef pair<pdd, pdd> Line;

const ld PI = acosl(-1);
const ld EPS = 1E-9;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(ld a, pdd b){return {a*b.F, a*b.S};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
ld abs(pdd a){return sqrtl(dot(a, a));}
ld ang(pdd a){return atan2l(a.S, a.F);}
pdd unit(ld th){return {cosl(th), sinl(th)};}

pdd A, B;
bool Ain, Bin;
ld A0, A1, A2, B0, B1, B2;
bool trash;

bool pnan(pdd x)
{
  return isnanl(x.F) or isnanl(x.S);
}

pdd interPnt(Line p, Line q, bool &res){
  pdd p1 = p.F, p2 = p.S, q1 = q.F, q2 = q.S;
	double f1 = cross(p2, q1, p1);
	double f2 = -cross(p2, q2, p1);
	double f = (f1 + f2);

	if(fabs(f) < EPS) {
		res = false;
		return {};
  }

	res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}

vector<Line> tangent(ld r1, ld r2)
{
  pdd p1 = A, p2 = B;
  if(r1 > r2)
  {
    swap(r1, r2);
    swap(p1, p2);
  }

  ld d = abs(p1-p2);
  ld phi = ang(p2-p1);
  vector<Line> res;
  if(r1 + r2 <= d + EPS)
  {
    ld th = acosl(min((ld)1.l, (r1+r2)/d));
    res.PB({p1 + r1 * unit(phi + th), p2 + r2 * unit(phi + PI + th)});
    res.PB({p1 + r1 * unit(phi - th), p2 + r2 * unit(phi + PI - th)});
  }
  if(r2 - r1 <= d + EPS)
  {
    ld th = asinl(min((ld)1.l, (r2-r1)/d));
    res.PB({p1 + r1 * unit(phi + PI/2 + th), p2 + r2 * unit(phi + PI/2 + th)});
    res.PB({p1 + r1 * unit(phi - PI/2 - th), p2 + r2 * unit(phi - PI/2 - th)});
  }

  res.PB({p1 + r1 * unit(phi), p1 + r1 * unit(phi) + unit(phi + PI/2)});
  
  vector<Line> vl;
  for(auto l: res)
    if(abs(l.F - l.S) > 1E-5 and !isnanl(l.F.F) and !isnanl(l.S.F))
      vl.PB(l);

  return vl;
}

bool checkIn(pdd p, vector<pdd> &v)
{
  assert(cross(v[2], v[1], v[0]) < 0);
  for(int i=0; i<3; i++)
    if(cross(v[(i+1)%3]-v[i], p-v[i]) < 0) return false;
  return true;
}

ld dis2line(pdd p, pdd p1, pdd p2)
{
  pdd d = p2 - p1;
  return abs(cross(d, p-p1) / abs(d));
}

bool _isint(ld x)
{
  return abs(x-roundl(x)) < 1E-6;
}

bool isint(pdd p)
{
  return _isint(p.F) and _isint(p.S);
}

void calc()
{
  vector<Line> v0, v1, v2;
  v0 = tangent(A0, B0);
  v1 = tangent(A1, B1);
  v2 = tangent(A2, B2);

  if(abs(A - B) < 1E-6)
  {
    pdd x, y, z;
    if(Ain)
    {
      y = {-A1, -A0};
      x = {A0 + A2 * sqrt(2), -A0};
      z = {-A1, A1 + A2 * sqrt(2)};
    }
    else
    {
      y = {A0, -A1};
      x = {A0, A2 * sqrt(2) - A0};
      z = {A1 + A2 * sqrt(2), -A1};
    }

    x = x + A;
    y = y + A;
    z = z + A;

    v0.PB({x, y});
    v1.PB({z, y});
    v2.PB({x, z});

    //cout<<x.F<<" "<<x.S<<endl;
    //cout<<y.F<<" "<<y.S<<endl;
    //cout<<z.F<<" "<<z.S<<endl;
    //return;
  }


  for(auto l0: v0)
  {
    for(auto l1: v1)
    {
      for(auto l2: v2)
      {
        pdd Y = interPnt(l0, l1, trash);
        if(!trash) continue;
        pdd Z = interPnt(l1, l2, trash);
        if(!trash) continue;
        pdd X = interPnt(l0, l2, trash);
        if(!trash) continue;

        //if(!isint(X) or !isint(Y) or !isint(Z)) continue;

        vector<pdd> v;
        v.PB(X);
        v.PB(Y);
        v.PB(Z);
        if(cross(v[1]-v[0], v[2]-v[0]) < 0)
          swap(v[1], v[2]);

        if(abs(X-Y) < 1E-6 or abs(Y-Z) < 1E-6 or abs(Z-X) < 1E-6) continue;
        if(abs(cross(X-Y, X-Z)) < 1E-6) continue;

        if(Ain != checkIn(A, v) or Bin != checkIn(B, v))
          continue;
        
        if(pnan(X) or pnan(Y) or pnan(Z)) continue;

        if(abs(X.F) > 1e9 or abs(X.S) > 1e9) assert(0);
        if(abs(Y.F) > 1e9 or abs(Y.S) > 1e9) assert(0);
        if(abs(Z.F) > 1e9 or abs(Z.S) > 1e9) assert(0);

        if(abs(dis2line(A, X, Y) - A0) > 1E-6) assert(0);
        if(abs(dis2line(A, Z, Y) - A1) > 1E-6) assert(0);
        if(abs(dis2line(A, X, Z) - A2) > 1E-6) assert(0);
        if(abs(dis2line(B, X, Y) - B0) > 1E-6) assert(0);
        if(abs(dis2line(B, Z, Y) - B1) > 1E-6) assert(0);
        if(abs(dis2line(B, X, Z) - B2) > 1E-6) assert(0);


        //assert(abs(X.F - 5.52) < 1E-6);
        cout<<X.F<<" "<<X.S<<endl;
        cout<<Y.F<<" "<<Y.S<<endl;
        cout<<Z.F<<" "<<Z.S<<endl;
        //if (abs(X.S) > 1.0) while(1);

        return;
        //cout<<dis2line(A, X, Y)<<" / "<<dis2line(A, Y, Z)<<" / "<<dis2line(A, Z, X)<<endl;
        //cout<<dis2line(B, X, Y)<<" / "<<dis2line(B, Y, Z)<<" / "<<dis2line(B, Z, X)<<endl;
      }
    }
  }
  assert(false);
}

int main() {
  IOS;
  cout<<fixed<<setprecision(12);
  //cout << 0 << ' ' << 0 << endl;
  //cout << 0 << ' ' << 12 << endl;
  //cout << 16 << ' ' << 0 << endl;
  //return 0;

  //cout << 5.520000000000 << ' ' << 7.360000000000 << endl;
//cout << -6.000000000000 << ' ' << 4.000000000000 << endl;
//cout << 10.000000000000 << ' ' << -8.000000000000 << endl;
//return 0;


  while(cin>>A.F>>A.S)
  {
    assert(!cin.fail());
    cin>>A0>>A1>>A2;
    assert(!cin.fail());
    Ain = Bin = true;
    if(A0 < 0 or A1 < 0 or A2 < 0)
    {
      Ain = false;
      A0 = -A0;
      A1 = -A1;
      A2 = -A2;
    }

    cin>>B.F>>B.S;
    assert(!cin.fail());
    cin>>B0>>B1>>B2;
    assert(!cin.fail());
    if(B0 < 0 or B1 < 0 or B2 < 0)
    {
      Bin = false;
      B0 = -B0;
      B1 = -B1;
      B2 = -B2;
    }

    assert(A0 > 0 and A1 > 0 and A2 > 0 and B0 > 0 and B1 > 0 and B2 > 0);

    calc();
  }

  return 0;
}

