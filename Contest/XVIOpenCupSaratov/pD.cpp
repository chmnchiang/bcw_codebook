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

const int MAXN = 12;

int N;
ld L;
ld l[MAXN];
ld ax[MAXN], ay[MAXN];

ld eval(ld fx, ld fy)
{
  ld cx = 0, cy = 0;
  for(int i=0; i<N; i++)
  {
    ld dx = fx, dy = fy - l[i] / 2.;
    ld r = sqrtl(dx*dx+dy*dy);
    dx *= l[i] / r;
    dy *= l[i] / r;
    cx += dx;
    cy += dy;
    ax[i] = cx;
    ay[i] = cy;
    fy -= l[i];
  }
  cx -= L;
  ld dif = sqrtl(cx*cx+cy*cy);
  return dif;
}

void calc()
{
  ld fx = 0, fy = 0;
  ld cost = eval(fx, fy);

  for(ld eps=1; eps>=1E-12; eps*=0.5)
  {
    for(int i=0; i<10000; i++)
    {
      ld dx = (rand() / (ld)RAND_MAX - 0.5) * eps;
      ld dy = (rand() / (ld)RAND_MAX - 0.5) * eps;
      ld nx = fx + dx, ny = fy + dy;
      ld ncost = eval(nx, ny);
      if(ncost < cost)
      {
        cost = ncost;
        fx = nx;
        fy = ny;
      }
    }
  }
}

int main() {
  IOS;
  cin>>N>>L;
  for(int i=0; i<N; i++)
    cin>>l[i];

  calc();

  for(int i=0; i<N-1; i++)
    cout<<fixed<<setprecision(12)<<ax[i]<<" "<<ay[i]<<endl;

  return 0;
}
