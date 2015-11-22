#include <bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef double ld;
typedef pair<ld, ld> pdd;

const int MAXN = 1010;
const ld PI = acosl(-1);
const ld EPS = 1E-9;

pdd operator+(pdd a, pdd b) {return MP(a.F+b.F, a.S+b.S);}
pdd operator-(pdd a, pdd b) {return MP(a.F-b.F, a.S-b.S);}
pdd operator*(pdd a, ld b) {return MP(a.F*b, a.S*b);}
ld dot(pdd a, pdd b) {return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b) {return a.F*b.S-a.S*b.F;}
ld abs(pdd a) {return sqrt(dot(a, a));}
ld arg(pdd a) {return atan2(a.S, a.F);}
void print(pdd a){cout<<a.F<<","<<a.S;}

int N, M;
ld TH, R, T;

pdd P;
double Vth, Dth;
pdd pt[MAXN];
bool alive[MAXN];

ld corr(ld x, ld cen)
{
  ld diff = x - cen;
  while(diff <= -PI) diff += 2*PI;
  while(diff > PI) diff -= 2*PI;
  return cen + diff;
}

bool point_inline(pdd p, pdd p1, pdd p2)
{
  //cout<<"INLINE ";print(p);cout<<endl;
  pdd d = p2 - p1;
  if(abs(cross(d, p-p1)) > EPS) return false;
  if(dot(p1-p, p2-p) > EPS) return false;
  return true;
  return abs(p-p1) + abs(p-p2) < abs(p1-p2) + EPS;
}

bool point_insect(pdd p, ld phi, ld span)
{
  //cout<<"CHECK ";print(p);cout<<" PHI "<<phi<<" SPAN "<<span<<endl;
  if(abs(p) < EPS) return true;
  ld theta = corr(arg(p), phi);
  if(abs(p) > R + EPS) return false;
  if(theta < phi - span - EPS || theta > phi + span + EPS) return false;
  return true;
}

pdd intersection(pdd p1, pdd dp, pdd q1, pdd dq)
{
  ld crs = cross(dq, dp);
  if(abs(crs) < EPS) return p1;
  ld t = cross(dq, q1 - p1) / crs;
  return p1 + dp * t;
}

pdd point_theta(ld theta)
{
  return MP(cosl(theta), sinl(theta));
}

bool insect(pdd p1, pdd p2, ld phi, ld span)
{
  vector<pdd> vec;
  vec.PB(p1);
  vec.PB(p2);
  for(auto v: vec)
    if(point_inline(v, p1, p2) && point_insect(v, phi, span))
      return true;
  pdd dir = p2 - p1;
  if(abs(dir) < EPS)
    dir = MP(1, 0);
  ld t = -dot(p1, dir) / dot(dir, dir);
  pdd cen = p1 + dir * t;
  //cout<<"DIR ";print(dir);cout<<" CEN ";print(cen);cout<<endl;
  
  if(point_inline(cen, p1, p2) && point_insect(cen, phi, span))
    return true;
  pdd i1 = intersection(p1, dir, MP(0, 0), point_theta(phi+span));
  pdd i2 = intersection(p1, dir, MP(0, 0), point_theta(phi-span));

  vec.clear();
  vec.PB(i1);
  vec.PB(i2);

  for(auto v: vec)
    if(point_inline(v, p1, p2) && point_insect(v, phi, span))
      return true;
  return false;
}

void act(pdd pp, pdd diffpp, ld cen, ld span)
{
  //cout<<"ACT ";print(pp);cout<<" ";print(diffpp);cout<<" "<<cen<<" "<<span<<endl;
  for(int j=0; j<N; j++)
  {
    if(insect(pt[j]-pp, pt[j]-pp-diffpp, cen, span))
      alive[j] = false;
  }
}

int main() {
  IOS;

  /*
  pdd aa, bb;
  R = 3;
  while(cin>>aa.F>>aa.S>>bb.F>>bb.S)
    cout<<insect(aa, bb, 0, PI/4)<<endl;
    */

  int TT;
  cin>>TT;
  for(int tt=1; tt<=TT; tt++)
  {
    cin>>N>>M>>TH>>R;
    T = 0;
    TH = TH / 2 * PI / 180;
    cin>>P.F>>P.S;
    pdd x;
    cin>>x.F>>x.S;
    Dth = arg(x);
    cin>>x.F>>x.S;
    Vth = arg(x);

    for(int i=0; i<N; i++)
      cin>>pt[i].F>>pt[i].S;
    for(int i=0; i<N; i++)
      alive[i] = true;

    for(int i=0; i<M; i++)
    {
      pdd nxtP = P;
      ld nxtVth = Vth;
      ld nxtDth = Dth;
      ld nxtT;
      int p;
      ld alpha;

      ld centh;
      ld span = 0;
      bool sweep = false;
      if(i < M)
      {
        cin>>p>>nxtT>>alpha;
        alpha *= PI / 180;
        if(p == 1)
        {
          sweep = true;
          centh = nxtDth - TH - alpha / 2;
          span = alpha / 2;
          nxtDth -= alpha;
          nxtDth = corr(nxtDth, 0);
        }
        else
        {
          nxtVth -= alpha;
          nxtVth = corr(nxtVth, 0);
        }
      }
      else
      {
        nxtT = 20000;
      }

      ld dt = nxtT - T;

      pdd diffP = point_theta(Vth) * dt;
      nxtP = diffP + P;

      //print(P);cout<<" => ";print(nxtP);cout<<endl;

      act(P, diffP, Dth, TH);
      if(sweep)
        act(P+diffP, MP(0, 0), centh, span);

      P = nxtP;
      T = nxtT;
      Vth = nxtVth;
      Dth = nxtDth;
    }

    cout<<"Case #"<<tt<<": ";
    for(int i=0; i<N; i++)
      cout<<alive[i];
    cout<<endl;
  }

  return 0;
}
