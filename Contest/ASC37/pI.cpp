#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<pdd, pdd> Line;

const int MAXN = 10;
const ld EPS = 1E-8;
const ld EPS2 = 1E-7;

pdd operator+(pdd a, pdd b) {return MP(a.F+b.F, a.S+b.S);}
pdd operator-(pdd a, pdd b) {return MP(a.F-b.F, a.S-b.S);}
pdd operator*(pdd a, ld b) {return MP(a.F*b, a.S*b);}
ld dot(pdd a, pdd b) {return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b) {return a.F*b.S-a.S*b.F;}
ld abs(pdd a) {return sqrt(dot(a, a));}

int N, L, P, Z;
Line lin[MAXN];
vector<Line> vlin;
vector<pdd> vpts;
vector<pdd> vips;

pdd intersection(Line a, Line b)
{
  pdd ret;
  pdd d1 = a.S - a.F, d2 = b.S - b.F;
  ld crs = cross(d2, d1);
  if(abs(crs) < EPS)
  {
    ret.F = nan("");
    return ret;
  }

  ld t = cross(d2, b.F - a.F) / crs;
  ret = a.F + d1 * t;
  return ret;
}

ld has_int(Line a, Line b)
{
  pdd d1 = a.S - a.F, d2 = b.S - b.F;
  ld crs = cross(d2, d1);
  if(abs(crs) < EPS)
    return false;

  pdd dif = b.F - a.F;
  ld t = cross(d2, dif) / crs;
  ld s = cross(d1, dif) / crs;

  // bool prnt = (abs(a.F.F - -39900.07980249997156) < EPS) && (abs(a.F.S - 99.99900000312493) < EPS);
  // if(prnt){
    // cout<<fixed<<setprecision(15);
  // cout<<"Has int ";
  // cout<<a.F.F<<","<<a.F.S<<" -- "<<a.S.F<<","<<a.S.S<<endl;
  // cout<<b.F.F<<","<<b.F.S<<" -- "<<b.S.F<<","<<b.S.S<<endl;
  // cout<<"S "<<s<<" T "<<t<<endl; 
  // }

  if(t < -EPS2 || t > 1+EPS2) return false;
  if(s < -EPS2 || s > 1+EPS2) return false;
  // if(prnt)cout<<"True !!"<<endl;
  return true;
}

bool online(Line a, pdd p)
{
  ld x = cross(a.S-a.F, p-a.F);
  return abs(x) < EPS;
}

pdd mid(Line a, pdd p)
{
  pdd d = a.S - a.F;
  ld t = dot(p - a.F, d) / dot(d, d);
  return (p + a.F + d * t) * 0.5;
}

int main()
{
  FILEIO("shooting");
  IOS;

  cin>>N;
  for(int i=0; i<N; i++)
    cin>>lin[i].F.F>>lin[i].F.S>>lin[i].S.F>>lin[i].S.S;

  for(int i=0; i<N; i++)
  {
    pdd d = lin[i].S - lin[i].F;
    double t = 1E-4;
    lin[i].F = lin[i].F - d * t;
    lin[i].S = lin[i].S + d * t;
  }

  for(int i=0; i<N; i++)
    vlin.PB(lin[i]);
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<i; j++)
    {
      vlin.PB(MP(lin[i].F, lin[j].F));
      vlin.PB(MP(lin[i].F, lin[j].S));
      vlin.PB(MP(lin[i].S, lin[j].F));
      vlin.PB(MP(lin[i].S, lin[j].S));
    }
  }
  vlin.PB(MP(MP(-101, -101), MP(-101, 101)));
  vlin.PB(MP(MP(-101, -101), MP(101, -101)));
  vlin.PB(MP(MP(101, 101), MP(-101, 101)));
  vlin.PB(MP(MP(101, 101), MP(101, -101)));

  L = vlin.size();

  for(int i=0; i<L; i++)
  {
    for(int j=0; j<i; j++)
    {
      pdd ret = intersection(vlin[i], vlin[j]);
      if(ret.F != ret.F) continue;
      vpts.PB(ret);

      pdd d1 = vlin[i].S - vlin[i].F;
      pdd d2 = vlin[j].S - vlin[j].F;
      d1 = d1 * (1 / abs(d1));
      d2 = d2 * (1 / abs(d2));
      pdd d3 = d1 + d2;
      pdd d4 = d1 - d2;
      const ld len = 1E-3;
      d3 = d3 * (len / abs(d3));
      d4 = d4 * (len / abs(d4));
      vips.PB(ret + d3);
      vips.PB(ret - d3);
      vips.PB(ret + d4);
      vips.PB(ret - d4);
    }
  }

  P = vpts.size();

  // for(int i=0; i<L; i++)
  // {
    // for(int j=0; j<P; j++)
    // {
      // pdd p = mid(vlin[i], vpts[j]);
      // bool ok = true;
      // for(int k=0; k<L; k++)
      // {
        // if(online(vlin[k], p))
        // {
          // ok = false;
          // break;
        // }
      // }
      // if(ok)
        // vips.PB(p);
    // }
  // }

  Z = vips.size();

  // cout<<N<<" "<<L<<" "<<P<<" "<<Z<<endl;

  int ansv = 1111;
  pdd ansp;

  for(int i=0; i<Z; i++)
  {
    int curmax = 0;
    for(int j=0; j<2*N; j++)
    {
      int jj = j % N;
      double t = (j>=N ? 0 : 1);
      pdd y = lin[jj].F + (lin[jj].S - lin[jj].F) * t;
      pdd d = y - vips[i];
      ld ratio = max(1.01l, 111111 / abs(d));
      y = vips[i] + d * ratio;
      Line l = MP(vips[i], y);

      // cout<<d.F<<","<<d.S<<endl;
      // cout<<(y-vips[i]).F<<","<<(y-vips[i]).S<<endl;
      // ld crs = cross(d, y-vips[i]);
      // cout<<crs<<endl;
      // assert(abs(cross(d, (y - vips[i]))) < EPS);

      // cout<<l.F.F<<","<<l.F.S<<" "<<l.S.F<<","<<l.S.S<<endl;
      int cnt = 0;
      for(int k=0; k<N; k++)
        if(has_int(l, lin[k]))
          cnt++;
      curmax = max(curmax, cnt);
    }

    if(curmax < ansv)
    {
      ansv = curmax;
      ansp = vips[i];
    }
  }

  cout<<ansv<<endl;
  cout<<fixed<<setprecision(15)<<ansp.F<<endl<<ansp.S<<endl;

  return 0;
}
