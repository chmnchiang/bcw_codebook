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

typedef double ld;
typedef pair<ld, ld> pdd;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrtl(dot(a, a));}
pdd norm(pdd a){return a * (1. / abs(a));}

const int MAXN = 50505;
const ld EPS = 1E-10;

int N[2];
pdd pt[2][MAXN];
ld len[2][MAXN], slen[2][MAXN];
pdd dir[2][MAXN];

ld min_dis(pdd p1, pdd p2, pdd q1, pdd q2)
{
  ld res = min(abs(p1-q1), abs(p2-q2));

  pdd d = p2 - p1, e = q2 - q1;
  pdd de = d - e, p12 = p1 - q1;
  ld dt = dot(de, de);
  if(dt > EPS)
  {
    ld t = -dot(de, p12) / dt;
    if(t > 0 && t < 1)
    {
      pdd a1 = p1 + d * t, a2 = q1 + e * t;
      res = min(res, abs(a1 - a2));
    }
  }

  return res;
}

bool test(ld D)
{
  int idx[2];
  ld t[2];
  idx[0] = idx[1] = 0;
  t[0] = t[1] = 0;
  ld rem = D;
  while(rem > 0)
  {
    if(rem >= len[1][idx[1]] && idx[1] < N[1]-1)
    {
      rem -= len[1][idx[1]];
      idx[1]++;
      t[1] = 0;
    }
    else
    {
      t[1] = rem;
      rem = 0;
      break;
    }
  }

  while(idx[0] < N[0]-1 && idx[1] < N[1]-1)
  {
    int nidx[2];
    ld nt[2];

    ld rt0 = len[0][idx[0]] - t[0];
    ld rt1 = len[1][idx[1]] - t[1];
    if(rt0 < rt1)
    {
      nidx[0] = idx[0] + 1;
      nt[0] = 0;
      nidx[1] = idx[1];
      nt[1] = t[1] + rt0;
    }
    else
    {
      nidx[0] = idx[0];
      nt[0] = t[0] + rt1;
      nidx[1] = idx[1] + 1;
      nt[1] = 0;
    }

    pdd p1 = pt[0][idx[0]] + dir[0][idx[0]] * t[0];
    pdd p2 = pt[0][nidx[0]] + dir[0][nidx[0]] * nt[0];
    pdd q1 = pt[1][idx[1]] + dir[1][idx[1]] * t[1];
    pdd q2 = pt[1][nidx[1]] + dir[1][nidx[1]] * nt[1];

    ld rdis = min_dis(p1, p2, q1, q2);
    if(rdis < D + EPS) return true;
    
    for(int j=0; j<2; j++)
    {
      idx[j] = nidx[j];
      t[j] = nt[j];
    }
  }

  return false;
}

ld calc()
{
  for(int x=0; x<2; x++)
  {
    for(int i=0; i<N[x]-1; i++)
    {
      dir[x][i] = pt[x][i+1] - pt[x][i];
      len[x][i] = abs(dir[x][i]);
      dir[x][i] = dir[x][i] * (1. / len[x][i]);
      slen[x][i+1] = slen[x][i] + len[x][i];
    }
  }

  if(abs(pt[1][N[1]-1] - pt[0][0]) > slen[1][N[1]-1] + EPS)
    return 1E7;

  ld lb = 0, rb = slen[1][N[1]-1];
  for(int i=0; i<100; i++)
  {
    if(rb - lb < 1E-7) break;
    ld mb = (lb + rb) / 2;
    if(test(mb))
      rb = mb;
    else
      lb = mb;
  }

  return lb;
}

int main() {
  IOS;
  for(int x=0; x<2; x++)
  {
    cin>>N[x];
    for(int i=0; i<N[x]; i++)
    {
      double a, b;
      cin>>a>>b;
      pt[x][i] = {a, b};
    }
  }

  double ans = calc();
  if(ans > 5E6)
    cout<<"impossible"<<endl;
  else
    cout<<fixed<<setprecision(7)<<ans<<endl;

  return 0;
}
