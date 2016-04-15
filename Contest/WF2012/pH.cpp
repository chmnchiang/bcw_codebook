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
pdd operator/(pdd a, ld b){return {a.F/b, a.S/b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrt(dot(a, a));}
pdd norm(pdd a){return a / abs(a);}

const int MAXN = 412;
const ld EPS = 1E-8;
const ld INF = 1E20;

int N, V;
pdd P;
pdd pt[MAXN]; 
pdd rP[MAXN], rpt[MAXN][MAXN];
pdd ept[MAXN];
ld dis[MAXN][MAXN];

bool inter(pdd p1, pdd p2, pdd q1, pdd q2)
{
  ld d = abs(p1-p2), dq = abs(q1-q2);
  if(abs(q1-p1) + abs(q1-p2) < d + EPS) return true;
  if(abs(q2-p1) + abs(q2-p2) < d + EPS) return true;

	double f1 = cross(p2 - p1, q1 - p1);
	double f2 = cross(p2 - p1, p1 - q2);
	double f = (f1 + f2);
  if(fabs(f) < EPS) return false;

  pdd p = q1 * (f2 / f) + q2 * (f1 / f);
  if(abs(p-p1) + abs(p-p2) < d + EPS && abs(p-q1) + abs(p-q2) < dq + EPS) return true;
  return false;
}

ld calc()
{
  rP[0] = P;
  for(int i=0; i<N; i++)
    rpt[0][i] = pt[i];

  for(int i=1; i<2*N; i++)
  {
    pdd p1 = rpt[i-1][(i-1)%N], p2 = rpt[i-1][i%N];
    pdd d = norm(p2 - p1);
    pdd n = {-d.S, d.F};

    ld g = dot(n, rP[i-1] - p1);
    rP[i] = rP[i-1] - n * (2*g);
    for(int j=0; j<N; j++)
    {
      g = dot(n, rpt[i-1][j] - p1);
      rpt[i][j] = rpt[i-1][j] - n * (2*g);
    }
  }

  V = 4*N;
  for(int i=0; i<2*N; i++)
  {
    ept[i] = rP[i];
    ept[2*N+i] = rpt[i][i%N];
  }

  for(int i=0; i<V; i++)
    for(int j=0; j<V; j++)
      dis[i][j] = INF;
  for(int i=0; i<V; i++)
    dis[i][i] = 0;

  for(int i=0; i<2*N; i++)
  {
    for(int j=i+1; j<2*N; j++)
    {
      for(int a=0; a<2; a++)
      {
        for(int b=0; b<2; b++)
        {
          int ii = i + a * 2*N;
          int jj = j + b * 2*N;
          bool ok = true;
          for(int k=i; k<j; k++)
          {
            if(!inter(ept[ii], ept[jj], ept[2*N+k], ept[2*N+k+1]))
            {
              ok = false;
              break;
            }
          }
          if(ok)
            dis[ii][jj] = abs(ept[jj] - ept[ii]);
        }
      }
    }
  }

  for(int k=0; k<V; k++)
    for(int i=0; i<V; i++)
      for(int j=0; j<V; j++)
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

  ld ans = INF;
  
  for(int i=0; i<N; i++)
    ans = min(ans, dis[i][N+i]);

  return ans;
}

int main() {
  IOS;

  int cas = 0;
  while(cin>>N)
  {
    cas++;
    cin>>P.F>>P.S;
    for(int i=0; i<N; i++)
      cin>>pt[i].F>>pt[i].S;

    ld ans = calc();
    cout<<"Case "<<cas<<": "<<fixed<<setprecision(2)<<ans<<endl;
  }
  return 0;
}
