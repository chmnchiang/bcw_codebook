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
typedef pair<double, double> pdd;

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

const int MAXN = 12;
const double EPS = 1E-9;
const double PI = acos(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator-(pdd b){return {-b.F, -b.S};}
pdd operator*(double a, pdd b){return {a*b.F, a*b.S};}
double dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
double abs(pdd a){return sqrt(dot(a, a));}
double rad(pdd a){return atan2(a.S, a.F);}
pdd unit(pdd a){return (1. / abs(a)) * a;}
pdd ang(double th){return {cos(th), sin(th)};};

int N;
double R;
pdd pt[MAXN], qt[MAXN];

bool inside_poly(pdd x)
{
  for(int i=0; i<N; i++)
  {
    if(cross(qt[(i+1)%N] - qt[i], x - qt[i]) < -EPS) return false;
  }
  return true;
}

bool inside_circle(pdd x)
{
  return abs(x) <= R;
}

double eval(pdd off)
{
  for(int i=0; i<N; i++)
    qt[i] = pt[i] + off;

  double ans = 0;
  vector<double> angles;
  angles.PB(0);
  for(int i=0; i<N; i++)
  {
    pdd p1 = qt[i], p2 = qt[(i+1)%N];
    pdd d = p2 - p1;
    pdd m = p1 + (1. / dot(d, d)) * dot(d, -p1) * d;
    double tm = dot(m - p1, d) / dot(d, d);
    double y = abs(m);
    
    vector<double> vt;
    vt.PB(0);
    vt.PB(1);
    if(y < R)
    {
      double h = sqrt(R*R-y*y);
      double t = h / abs(d);
      double t1 = tm - t, t2 = tm + t;
      if(0 < t1 and t1 < 1)
      {
        vt.PB(t1);
        angles.PB(rad(p1 + t1 * d));
      }
      if(0 < t2 and t2 < 1)
      {
        vt.PB(t2);
        angles.PB(rad(p1 + t2 * d));
      }
    }

    sort(ALL(vt));
    int sz = SZ(vt);
    //cout<<p1<<"~"<<p2<<" : "<<vt<<endl;
    for(int j=0; j<sz-1; j++)
    {
      double z1 = vt[j], z2 = vt[j+1];
      pdd q1 = p1 + z1 * d, q2 = p1 + z2 * d;
      pdd pc = 0.5 * (q1 + q2);
      //cout<<pc<<" : "<<inside_circle(pc)<<endl;
      if(inside_circle(pc))
        ans += cross(q1, q2) / 2;
    }
  }

  sort(ALL(angles));
  int sz = SZ(angles);
  for(int i=0; i<sz; i++)
  {
    double th1 = angles[i], th2 = angles[(i+1)%sz];
    if(th1 > th2) th2 += 2*PI;
    double thm = (th1 + th2) / 2;
    pdd pm = R * ang(thm);
    if(inside_poly(pm))
      ans += R * R * (th2 - th1) / 2;
  }

  if(ans < EPS)
    ans = -abs(off);

  //cout<<off<<" : "<<ans<<endl;
  return ans;
}

double search(function<double(double)> f, double lb, double rb)
{
  for(int _=0; _<100; _++)
  {
    if(rb - lb < 1E-15) break;
    double m1 = (lb+lb+rb)/3, m2 = (lb+rb+rb)/3;
    double v1 = f(m1), v2 = f(m2);
    if(v1 > v2)
      rb = m2;
    else
      lb = m1;
  }
  double x = (lb + rb) / 2;
  double val = f(x);
  return val;
}

double max_y(double x)
{
  double res = search([x](double y){return eval({x, y});}, -1000, 1000);
  return res;
}

double max_val()
{
  double res = search([](double x){return max_y(x);}, -1000, 1000);
  return res;
}

int main() {
  IOS;
  cout<<fixed<<setprecision(10);

  while(cin>>N>>R)
  {
    for(int i=0; i<N; i++)
      cin>>pt[i].F>>pt[i].S;

    pdd cen = {0, 0};
    for(int i=0; i<N; i++)
      cen = cen + pt[i];
    cen = (1. / N) * cen;
    for(int i=0; i<N; i++)
      pt[i] = pt[i] - cen;

    double ans = max_val();
    cout<<ans<<endl;
  }

  return 0;
}

