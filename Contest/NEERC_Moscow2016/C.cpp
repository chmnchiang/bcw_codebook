#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

typedef long double ld;
typedef pair<ld, ld> pdd;

const ld PI = acosl(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld operator%(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs2(pdd a){return dot(a, a);}
ld abs(pdd a){return sqrtl(abs2(a));}

ld dis;
int paw;
pdd pos;
pdd corr;

ld R;

ld frand(ld mx)
{
  ld x = (ld)rand() / RAND_MAX;
  return x * mx;
}

ld norm(ld th)
{
  while(th < 0) th += 2*PI;
  while(th >= 2*PI) th -= 2*PI;
  return th;
}

#ifdef ONLINE_JUDGE
void interact(ld th)
{
  th = norm(th);
  ld zz = th * 180 / PI;
  assert(zz >= 0 and zz <= 360);
  cout<<zz<<endl;
  cin>>dis>>paw;
  if(cin.fail()) exit(0);
  pos.F += dis * cosl(th);
  pos.S += dis * sinl(th);
}
#else
int gpaw(pdd p)
{
  int d = (abs(p - corr) / R) - 1e-8;
  return d+1;
}

void interact(ld th)
{
//  cout<<"Act Th = "<<th<<endl;
  pdd orig = pos;
  pdd vec = {cosl(th)*1e-5, sinl(th)*1e-5};
//  cout<<vec<<endl;

  while(gpaw(pos) == paw)
  {
    pdd npos = pos + vec;
    if(gpaw(npos) > paw)
    {
      break;
    }
    else
      pos = npos;
  }

  dis = abs(orig - pos);

//  cout<<orig<<" => "<<pos<<" DIS "<<dis<<endl;
//  cout<<"PAW "<<paw<<" => "<<gpaw(pos)<<endl;
  paw = gpaw(pos);

//  cout<<"RD = "<<abs(pos-corr)/R<<endl;
}
#endif

pdd center(pdd p0, pdd p1, pdd p2) {
  pdd a = p1-p0;
  pdd b = p2-p0;
  double c1=abs2(a)*0.5;
  double c2=abs2(b)*0.5;
  double d = a % b;
  double x = p0.F + (c1 * b.S - c2 * a.S) / d;
  double y = p0.S + (a.F * c2 - b.F * c1) / d;
  return pdd(x,y);
}

int main() {
//  srand(134);
  srand(time(0));
  IOS;
  cout<<fixed<<setprecision(10);
//  cerr<<fixed<<setprecision(10);

  R = frand(99) + 1;
  ld ct = frand(2*PI);
  corr = {cosl(ct)*R*3, sinl(ct)*R*3};
  paw = 3;
//  cerr<<corr<<endl;

  pdd p0 = pos;
  ld th = frand(2 * PI);
  interact(th);
  if(dis < 1E-10)
  {
    th = norm(th + PI);
    interact(th);
  }

  if(paw == 3)
  {
    pdd p1 = pos;
//    cerr<<"P1 "<<p1<<endl;
    ld phi = atan2l(p1.S, p1.F);
    th = norm(phi + PI - 0.005);
    interact(th);

    //  assert(paw == 3);

    pdd p2 = pos;
//    cerr<<"P2 "<<p2<<endl;

    pdd cen = center(p0, p1, p2);

//    cerr<<"CEN = "<<cen<<endl;

    pdd v = cen - pos;
    th = atan2l(v.S, v.F);
    while(1) interact(th);
  }
  else
  {
    pdd p1 = {0, 0};
    pdd p2 = pos;
    interact(th);
    pdd p3 = pos;

    pdd np1, np2;

    if(paw == 2)
    {

      pdd c = (p2 + p3) * 0.5;
      ld d1 = abs(c - p2), d2 = abs(c - p1);
      ld r = sqrtl((d2 * d2 - d1 * d1) / (2 * paw + 1));
      ld h = sqrtl(paw * paw * r * r - d1 * d1);
      ld th1 = norm(th - PI/2), th2 = norm(th + PI/2);
      np1 = {c.F + h * cosl(th1), c.S + h * sinl(th1)};
      np2 = {c.F + h * cosl(th2), c.S + h * sinl(th2)};

      //cout<<"D1 "<<d1<<" D2 "<<d2<<endl;
      //cout<<"Solved R = "<<r<<" H = "<<h<<endl;
    }
    else
    {
      //cout<<abs(p1-corr)<<" "<<abs(p2-corr)<<" "<<abs(p3-corr)<<endl;

      ld d1 = abs(p3 - p2), d2 = abs(p3 - p1);
      //cout<<"D1 "<<d1<<" D2 "<<d2<<endl;
      ld x = (3 * d2 * d2 - 8 * d1 * d1) / (16 * d1 - 6 * d2); 
      //cout<<"X = "<<x<<endl;

      pdd c = p3 + pdd(cosl(th), sinl(th)) * x;

      d1 += x;
      d2 += x;

      ld r = sqrtl((d2 * d2 - d1 * d1) / 5);
//      r =  sqrtl((d1 * d1 - (d1-x) * (d1-x)) / 3);
      ld h = sqrtl(r * r - x * x);
      ld th1 = norm(th - PI/2), th2 = norm(th + PI/2);
      np1 = {c.F + h * cosl(th1), c.S + h * sinl(th1)};
      np2 = {c.F + h * cosl(th2), c.S + h * sinl(th2)};

      //cout<<"Solved R = "<<r<<" H = "<<h<<endl;

    }
    
//    cerr<<"PAW "<<paw<<" CEN = "<<np1<<" OR "<<np2<<endl;

    int npaw = paw;
    pdd v = np1 - pos;
    th = atan2l(v.S, v.F);
    interact(th);

    if(paw == npaw)
    {
    v = np2 - pos;
    th = atan2l(v.S, v.F);
    }
    while(1) interact(th);
  }

  return 0;
}
