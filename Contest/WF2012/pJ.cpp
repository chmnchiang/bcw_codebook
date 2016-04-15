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

#define acosl acos
#define asinl asin
#define cosl cos
#define sinl sin
#define atan2l atan2
#define sqrtl sqrt

struct Point
{
  ld x, y, z;
};

Point operator+(Point a, Point b){return {a.x+b.x, a.y+b.y, a.z+b.z};}
Point operator-(Point a, Point b){return {a.x-b.x, a.y-b.y, a.z-b.z};}
Point operator*(Point a, ld b){return {a.x*b, a.y*b, a.z*b};}
ld dot(Point a, Point b){return a.x*b.x+a.y*b.y+a.z*b.z;}
Point cross(Point a, Point b){return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};}
ld abs(Point a){return sqrtl(dot(a, a));}
Point norm(Point a){return a * (1.l / abs(a));}
ostream& operator <<(ostream &s, const Point &p) {
  return s<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
}

const int MAXN = 27;
const int MAXM = 700;
const ld EPS = 1E-8;
const ld INF = 1E20;
const ld PI = acosl(-1);
const ld RE = 6370;

int N, Q, V;
ld R;
ld alpha, calpha;

ld pphi[MAXN], ptheta[MAXN];
Point pt[MAXN];
Point rpt[MAXM];
ld edge[MAXM][MAXM], dis[MAXM][MAXM];
bool used[MAXM];
ld qdis[MAXM];

ld reg(ld th)
{
  while(th < 0) th += 2*PI;
  while(th > 2*PI) th -= 2*PI;
  return th;
}

ld acosln(ld x)
{
  x = min(x, 1.);
  x = max(x, -1.);
  return acosl(x);
}

ld get_edge(Point p1, Point p2)
{
  ld dt = dot(p1, p2);
  if(dt < -1+EPS) return INF;
  ld phi = acosln(dt); 
  Point n = norm(cross(p1, p2));
  Point g = norm(p1);
  Point h = norm(cross(n, g));

  vector<pdd> vseg;
  for(int i=0; i<N; i++)
  {
    ld sgamma = dot(pt[i], n);
    ld cgamma = sqrtl(1 - sgamma * sgamma);
    if(cgamma < calpha) continue;
    ld rat = calpha / cgamma;
    ld delta = acosl(rat);
    ld xx = dot(pt[i], g), yy = dot(pt[i], h);
    ld cen = atan2l(yy, xx);
    ld lb = reg(cen - delta - EPS), rb = reg(cen + delta + EPS);
    if(lb < rb)
      vseg.PB({lb, rb});
    else
    {
      vseg.PB({0, rb});
      vseg.PB({lb, 2*PI});
    }
  }
  sort(ALL(vseg));
  ld curr = EPS;
  for(auto p: vseg)
  {
    if(p.F > curr)
      break;
    curr = max(curr, p.S);
  }

  if(curr < phi) return INF;
  return RE * phi;
}

void calc()
{
  alpha = R / RE;
  calpha = cosl(alpha);

  for(int i=0; i<N; i++)
  {
    pphi[i] *= PI / 180;
    ptheta[i] *= PI / 180;
    pt[i] = {cosl(ptheta[i]) * cosl(pphi[i]), cosl(ptheta[i]) * sinl(pphi[i]), sinl(ptheta[i])};
  }

  V = N;
  for(int i=0; i<N; i++)
    rpt[i] = pt[i];

  for(int i=0; i<N; i++)
  {
    for(int j=i+1; j<N; j++)
    {
      ld dt = dot(pt[i], pt[j]);
      if(dt < -1+EPS) continue;
      ld beta = acosl(dt) / 2;
      ld cbeta = cosl(beta);
      if(cbeta < calpha) continue;
      ld rat = calpha / cbeta;
      ld delta = acosl(rat);

      Point t = norm(pt[i] + pt[j]);
      Point n = norm(cross(pt[i], pt[j]));
      Point x1 = t * cosl(delta) + n * sinl(delta);
      Point x2 = t * cosl(delta) - n * sinl(delta);
      rpt[V++] = norm(x1);
      rpt[V++] = norm(x2);
    }
  }

  for(int i=0; i<V; i++)
  {
    for(int j=0; j<V; j++)
    {
      if(j<i)
        edge[i][j] = edge[j][i];
      else
        edge[i][j] = get_edge(rpt[i], rpt[j]);
    }
  }

  for(int i=0; i<N; i++)
  {
    for(int j=0; j<V; j++)
    {
      dis[i][j] = INF;
      used[j] = false;
    }
    dis[i][i] = 0;
    for(int j=0; j<V; j++)
    {
      int bst = -1;
      for(int k=0; k<V; k++)
      {
        if(used[k]) continue;
        if(bst == -1 || dis[i][k] < dis[i][bst])
          bst = k;
      }
      used[bst] = true;
      for(int k=0; k<V; k++)
      {
        ld nc = dis[i][bst] + edge[bst][k];
        if(dis[i][k] > nc)
          dis[i][k] = nc;
      }
    }
  }
}

ld query(int s, int t, ld c)
{
  for(int i=0; i<N; i++)
  {
    used[i] = false;
    qdis[i] = INF;
  }
  qdis[s] = 0;

  for(int i=0; i<N; i++)
  {
    int bst = -1;
    for(int j=0; j<N; j++)
    {
      if(used[j]) continue;
      if(bst == -1 || qdis[j] < qdis[bst])
        bst = j;
    }
    used[bst] = true;
    for(int j=0; j<N; j++)
    {
      if(dis[bst][j] > c) continue;
      ld nc = qdis[bst] + dis[bst][j];
      if(qdis[j] > nc)
        qdis[j] = nc;
    }
  }

  return qdis[t];
}

int main() {
  IOS;

  int tt = 0;
  while(cin>>N>>R)
  {
    tt++;
    cout<<"Case "<<tt<<":"<<endl;
    
    for(int i=0; i<N; i++)
      cin>>pphi[i]>>ptheta[i];

    calc();

    cin>>Q;
    for(int i=0; i<Q; i++)
    {
      int s, t;
      ld c;
      cin>>s>>t>>c;
      s--;
      t--;

      ld ans = query(s, t, c);
      if(ans == INF)
        cout<<"impossible"<<endl;
      else
        cout<<fixed<<setprecision(3)<<ans<<endl;
    }
  }

  return 0;
}
