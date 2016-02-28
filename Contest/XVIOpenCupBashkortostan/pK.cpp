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
typedef pair<int, int> pii;
typedef pair<ld, pii> pdi;

const int MAXN = 2020;
const ld EPS = 1E-8;
const ld INF = 1E20;
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

int N;
pdd pt[MAXN], ot[MAXN];
ld th[MAXN];
bool btype[MAXN];
ld edge[MAXN][MAXN];
int root[MAXN];
pdd lpp[MAXN], rpp[MAXN];

void djInit()
{
  for(int i=0; i<2*N; i++)
    root[i] = i;
}

int djFind(int x)
{
  if(root[x] == x) return x;
  return root[x] = djFind(root[x]);
}

bool djUnion(int x, int y)
{
  int px = djFind(x), py = djFind(y);
  if(px == py) return false;
  root[px] = py;
  return true;
}

ld getdis(int a, ld theta)
{
  pdd p1 = ot[2*a], p2 = ot[2*a+1];
  pdd q1 = {0, 0}, q2 = unit(theta);
  ld f1 = cross(p2 - p1, q1 - p1);
  ld f2 = cross(p2 - p1, p1 - q2);
  ld f = f1 + f2;

  pdd p = q1 * (f2 / f) + q2 * (f1 / f);
  return abs(p);
}

bool cmp(int a, int b)
{
  return th[a] < th[b];
}

struct cmp2
{
  bool operator()(int a, int b)
  {
    if(a == b) return false;
    pdd lp = lpp[a], rp = rpp[a];
    bool sw = false;

    pdd q = ot[2*b];
    if(cross(q, lp) > 0 || cross(q, rp) < 0)
      q = ot[2*b+1];
    if(cross(q, lp) > 0 || cross(q, rp) < 0)
    {
      sw = true;
      lp = lpp[b], rp = rpp[b], q = ot[2*a]; 
    }

    assert(cross(q, lp) < 0 && cross(q, rp) > 0);

    return (cross(rp-lp, q-lp) < 0) ^ sw;
  }
};

ld calc()
{
  for(int i=0; i<2*N; i++)
    for(int j=0; j<2*N; j++)
      edge[i][j] = INF;

  for(int i=0; i<2*N; i++)
  {
    for(int j=0; j<2*N; j++)
    {
      ot[j] = pt[j] - pt[i];
      if(j == i) continue;
      th[j] = angle(ot[j]);
    }

    for(int j=0; j<N; j++)
    {
      if(i/2 == j) continue;
      if(cross(ot[2*j], ot[2*j+1]) > 0)
      {
        btype[2*j] = 0;
        btype[2*j+1] = 1;
      }
      else
      {
        btype[2*j] = 1;
        btype[2*j+1] = 0;
      }
    }

    for(int j=0; j<N; j++)
    {
      if(i/2 == j) continue;
      lpp[j] = ot[2*j], rpp[j] = ot[2*j+1];
      if(btype[2*j]) swap(lpp[j], rpp[j]);
    }

    vector<int> ord;
    for(int j=0; j<2*N; j++)
    {
      if(j == i) continue;
      ord.PB(j);
    }
    sort(ALL(ord), cmp);

    set<int, cmp2> st;

    for(int j=0; j<N; j++)
    {
      if(i/2 == j) continue;
      ld lb = th[2*j], rb = th[2*j+1];
      if(btype[2*j]) swap(lb, rb);
      if(lb > rb)
      {
        st.insert(j);
      }
    }

    for(auto v: ord)
    {
      if(v/2 == i/2)
      {
        edge[i][v] = 0;
        continue;
      }
      if(btype[v])
        st.erase(v/2);

      bool ok = true;
      if(!st.empty())
      {
        int l = *st.begin();
        ld d = getdis(l, th[v]);
        ld td = abs(ot[v]);
        if(td > d)
          ok = false;
      }
      if(ok)
        edge[i][v] = abs(ot[v]);

      if(!btype[v])
        st.insert(v/2);
    }
  }

  vector<pdi> vedge;
  for(int i=0; i<2*N; i++)
    for(int j=0; j<2*N; j++)
      vedge.PB({edge[i][j], {i, j}});

  sort(ALL(vedge));

  ld ans = 0;
  djInit();
  for(auto e: vedge)
  {
    if(djUnion(e.S.F, e.S.S))
      ans += e.F;
  }

  return ans;
}

int main() {
  IOS;
  cin>>N;
  for(int i=0; i<N; i++)
    cin>>pt[2*i].F>>pt[2*i].S>>pt[2*i+1].F>>pt[2*i+1].S;

  ld ans = calc();
  cout<<fixed<<setprecision(12)<<ans<<endl;

  return 0;
}
