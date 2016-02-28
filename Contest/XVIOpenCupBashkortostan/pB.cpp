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

const int MAXN = 2020;
const ld EPS = 1E-10;
const ld PI = acosl(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrtl(dot(a, a));}
ld angle(pdd a){return atan2l(a.S, a.F);}
ld reg(ld a)
{
  while(a < -PI) a += 2*PI;
  while(a >= PI) a -= 2*PI;
  return a;
}
pdd unit(ld a){return {cosl(a), sinl(a)};}

int P, N, V;
pdd cpt[MAXN], pt[MAXN];
ld pr[MAXN];
bool covered[MAXN];
vector<pdd> seg[MAXN];
pdd ans[MAXN];

void calc()
{
  ld area = 0;
  pdd moment = {0, 0};

  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      ld dis = abs(pt[i] - pt[j]);
      if(pr[i] - pr[j] > EPS && dis < pr[i] - pr[j] + EPS)
        covered[j] = true;
      else if(dis < EPS && abs(pr[i] - pr[j]) < EPS && i < j)
        covered[j] = true;
    }
  }

  for(int i=0; i<N; i++)
  {
    if(covered[i]) continue;
    for(int j=0; j<N; j++)
    {
      if(j == i || covered[j]) continue;
      ld d = abs(pt[i] - pt[j]);
      ld r1 = pr[i], r2 = pr[j];
      if(d > r1 + r2 - EPS) continue;
      ld theta = angle(pt[j] - pt[i]);
      ld phi = acosl((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));

      ld lb = reg(theta - phi), rb = reg(theta + phi);
      if(lb < rb)
        seg[i].PB({lb, rb});
      else
      {
        seg[i].PB({lb, PI});
        seg[i].PB({-PI, rb});
      }
    }

    seg[i].PB({PI, PI});
    sort(ALL(seg[i]));

    vector<pdd> bseg;

    ld cur = -PI;
    for(auto p: seg[i])
    {
      if(cur < p.F - EPS)
        bseg.PB({cur, p.F});
      cur = max(cur, p.S);
    }

    pdd p = pt[i];
    ld r = pr[i];
    ld da = 0;
    pdd dm = {0, 0};
    for(auto x: bseg)
    {
      ld th1 = x.F, th2 = x.S;
      pdd p1 = p + unit(th1) * r, p2 = p + unit(th2) * r;

      ld a = -cross(p1-p, p2-p) / 2;
      pdd cen = (p + p1 + p2) * (1. / 3);
      da += a;
      dm = dm + cen * a;

      a = cross(p1, p2) / 2;
      cen = (p1 + p2) * (1. / 3);
      da += a;
      dm = dm + cen * a;

      a = (th2 - th1) * r * r / 2;
      da += a;
      dm = dm + pdd(sinl(th2) - sinl(th1), -cosl(th2) + cosl(th1)) * (r * r * r / 3);
      dm = dm + p * a;
    }

    area += da;
    moment = moment + dm;
  }

  area *= -1;
  moment = moment * (-1);

  for(int i=0; i<P; i++)
  {
    pdd p = cpt[i], q = cpt[(i+1)%P];
    ld a = cross(p, q) / 2;
    pdd cen = (p + q) * (1. / 3);
    area += a;
    moment = moment + cen * a;
  }

  pdd gcen = moment * (1 / area);

  ld dth = -PI/2 - angle(gcen - cpt[V]);
  ld sdth = sinl(dth), cdth = cosl(dth);

  for(int i=0; i<P; i++)
  {
    pdd dp = cpt[i] - cpt[V];
    ans[i] = cpt[V] + pdd(cdth * dp.F - sdth * dp.S, sdth * dp.F + cdth * dp.S);
  }
}

int main() {
  IOS;
  cin>>P>>N>>V;
  V--;

  for(int i=0; i<P; i++)
    cin>>cpt[i].F>>cpt[i].S;
  for(int i=0; i<N; i++)
    cin>>pt[i].F>>pt[i].S>>pr[i];

  calc();

  cout<<fixed<<setprecision(10);
  for(int i=0; i<P; i++)
  {
    cout<<ans[i].F<<" "<<ans[i].S<<"\n";
  }

  return 0;
}
