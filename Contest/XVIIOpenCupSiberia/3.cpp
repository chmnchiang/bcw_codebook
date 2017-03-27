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

const ld EPS = 1E-14;
const ld PI = acosl(-1);

typedef pair<pdd, pdd> Line;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(ld a, pdd b){return {a*b.F, a*b.S};}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}

int cnt = 0;
pdd pt[3];
ld area;

pdd unit(ld th){return {cosl(th), sinl(th)};}

pdd interPnt(Line l1, Line l2, bool &res){
    pdd p1, p2, q1, q2;
    tie(p1, p2) = l1;
    tie(q1, q2) = l2;
	ld f1 = cross(p2, q1, p1);
    ld f2 = -cross(p2, q2, p1);
	ld f = (f1 + f2);

    if(fabs(f) < EPS) {
        res = false;
        return {0, 0};
    }

    res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}

bool isin(Line l0, Line l1, Line l2) {
    // Check inter(l1, l2) in l0
    bool res;
    pdd p = interPnt(l1, l2, res);
    return cross(l0.S, p, l0.F) > EPS;
}

/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F).cross(p - l.F) > 0
 */
vector<Line> halfPlaneInter(vector<Line> lines) {
    int sz = lines.size();
    vector<ld> ata(sz), ord(sz);
    for (int i=0; i<sz; i++) {
        ord[i] = i;
        pdd d = lines[i].S - lines[i].F;
        ata[i] = atan2l(d.S, d.F);
    }
    sort(ALL(ord), [&](int i, int j) {
        if (abs(ata[i] - ata[j]) < EPS) {
            return cross(lines[i].S, lines[j].S, lines[i].F) < 0;
        }
        return ata[i] < ata[j];
    });
    vector<Line> fin;
    for (int i=0; i<sz; i++) {
        if (!i or fabs(ata[ord[i]] - ata[ord[i-1]]) > EPS) {
            fin.PB(lines[ord[i]]);
        }
    }
    
    deque<Line> dq;
    for (int i=0; i<SZ(fin); i++) {
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
            dq.pop_back();
        }
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[0], dq[1])) {
            dq.pop_front();
        }
        dq.push_back(fin[i]);
    }

    while (SZ(dq) >= 3 and
           not isin(dq[0], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
        dq.pop_back();
    }

    while (SZ(dq) >= 3 and
           not isin(dq[SZ(dq)-1], dq[0], dq[1])) {
        dq.pop_front();
    }
    vector<Line> res(ALL(dq));
    return res;
}

#ifdef HAO123
ld qry(pdd d, ld c)
{
  vector<Line> vec;
  for(int i=0; i<3; i++)
    vec.PB({pt[i], pt[(i+1)%3]});
  pdd a = c * d;
  pdd n = {-d.S, d.F};
  vec.PB({a, a+n});

  vec = halfPlaneInter(vec);
  if(SZ(vec) < 3) return 0;
  ld ans = 0;
  int S = SZ(vec);
  vector<pdd> vpt;
  bool trash = 0;
  for(int i=0; i<S; i++)
    vpt.PB(interPnt(vec[i], vec[(i+1)%S], trash));
  for(int i=0; i<S; i++)
    ans += cross(vpt[i], vpt[(i+1)%S]);
  ans /= 2;
  ans /= area;
  return ans;
}
#else
ld qry(pdd d, ld c)
{
  cnt++;
  assert(cnt < 1000);
  assert(abs(d.F) <= 2000 and abs(d.S) <= 2000 and abs(c) <= 4000000);
  ld r = d.F*d.F+d.S*d.S;
  assert(1./4000000 <= r and r <= 4000000);
  cout<<"? "<<d.F<<" "<<d.S<<" "<<c<<endl;
  ld p, q;
  cin>>p>>q;
  return p;
}
#endif

ld query_bound(pdd d)
{
  ld lb = -2000, rb = 2000;
  for(int i=0; i<100; i++)
  {
    ld mb = (lb + rb) / 2;
    ld p = qry(d, mb);
    if(p < EPS) lb = mb;
    else rb = mb;
  }
  return lb;
}

ld query_angle(pdd p, ld th0)
{
  ld lb = th0, rb = th0 + PI;
  for(int i=0; i<100; i++)
  {
    ld mb = (lb + rb) / 2;
    pdd d = unit(mb);
    ld pp = qry(d, d.F*p.F+d.S*p.S);
    if(pp < EPS) lb = mb;
    else rb = mb;
  }
  return lb;
}

int main() {
  IOS;

  pt[0] = {0, 0};
  pt[1] = {300, 0};
  pt[2] = {100, 200};
  area = cross(pt[0], pt[1], pt[2]) / 2;
  cout<<fixed<<setprecision(15);

  ld th = 0.34021501;

  vector<int> vec;
  for(int i=0; i<3; i++)
  {
    pdd d = unit(th), dp = unit(th + 1E-3);
    ld a1 = query_bound(d);
    ld a2 = query_bound(dp);


    ld del = d.F*dp.S-d.S*dp.F; 
    ld xx = (a1 * dp.S - a2 * d.S) / del;
    ld yy = (-a1 * dp.F + a2 * d.F) / del;
    ld rx = roundl(xx);
    ld ry = roundl(yy);
    pdd p = {rx, ry};

    //cout<<d<<" : "<<a1<<" , "<<dp<<" : "<<a2<<endl;
    //cout<<"INTERSECT "<<p<<" ORIG "<<xx<<" "<<yy<<endl;

    //assert(abs(rx - xx) < 1E-3);
    //assert(abs(ry - yy) < 1E-3);
    vec.PB(rx);
    vec.PB(ry);

    th = query_angle(p, th);
    //cout<<"NEW ANGLE = "<<th<<endl;
  }

  cout<<"!";
  for(int i=0; i<6; i++) cout<<" "<<vec[i];
  cout<<endl;

  return 0;
}

