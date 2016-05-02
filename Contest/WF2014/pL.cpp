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
typedef pair<int, int> pii;
typedef pair<ld, ld> pdd;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrt(dot(a, a));}
ld angle(pdd a){return atan2(a.S, a.F);}
pdd norm(pdd a){return a * (1. / abs(a));}

const int MAXM = 217;
const int MAXN = 11111;
const int IINF = 102938;
const ld EPS = 1E-11;
const pdd BAD = {1E23, 4E56};
const pdd PINF = {123456, 234567};

int M, N, E, P;
pdd ss, tt;
pdd pt[MAXM], qt[MAXM], ipt[MAXM][MAXM];
int pti[MAXM], qti[MAXM], ipti[MAXM][MAXM];
vector<pdd> vpt;
double zz[MAXN];
vector<int> edge[MAXN];
int vis[MAXN][MAXM];
pii rev[MAXN][MAXM];
vector<int> poly[MAXN];
double parea[MAXN];
vector<pii> pedge[MAXN];
vector<int> ssin, ttin;
int pdis[MAXN];

bool online(pdd p, pdd p1, pdd p2)
{
  pdd d = p2 - p1;
  ld a = abs(d);
  if(abs(cross(d, p-p1)) / a > EPS) return false;
  ld dt = dot(d, p-p1) / a;
  return -EPS < dt and dt < a+EPS;
}

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	ld f1 = cross(p2 - p1, q1 - p1);
	ld f2 = cross(p2 - p1, p1 - q2);
	ld f = (f1 + f2);
  if(f < 0)
  {
    f = -f;
    f1 = -f1;
    f2 = -f2;
  }

	if(f < EPS or f1 < EPS or f2 < EPS) return BAD;
	pdd x = q1 * (f2 / f) + q2 * (f1 / f);
  if(!online(x, p1, p2)) return BAD;
  return x;
}

bool cmp(pdd a, pdd b)
{
  if(abs(a.F-b.F) < EPS)
    return a.S < b.S - EPS;
  return a.F < b.F - EPS;
}

bool equ(pdd a, pdd b)
{
  return abs(a.F-b.F)<EPS && abs(a.S-b.S)<EPS;
}

bool cmp2(int a, int b)
{
  return zz[a] < zz[b];
}

void dfs(int v, int ve, int p)
{
  if(vis[v][ve] != -1) return;
  vis[v][ve] = p;
  poly[p].PB(v);
  int u = edge[v][ve];
  int ue = 0;
  while(edge[u][ue] != v)
    ue++;
  rev[v][ve] = {u, ue};
  ue++;
  if(ue >= SZ(edge[u]))
    ue = 0;
  dfs(u, ue, p);
}

bool inpoly(vector<int> &vec, pdd p)
{
  int s = SZ(vec);
  int cnt = 0;
  for(int j=0; j<s; j++)
  {
    int k = (j==s-1 ? 0 : j+1);
    if(interPnt(vpt[vec[j]], vpt[vec[k]], p, PINF) != BAD)
      cnt++;
  }
  return cnt % 2;
}

int calc()
{
  if(M == 0) return 0;

  for(int i=0; i<M; i++)
  {
    vpt.PB(pt[i]);
    vpt.PB(qt[i]);

    for(int j=i+1; j<M; j++)
    {
      ipt[i][j] = interPnt(pt[i], qt[i], pt[j], qt[j]);
      if(ipt[i][j] != BAD)
        vpt.PB(ipt[i][j]);
    }
  }

  sort(ALL(vpt), cmp);
  N = unique(ALL(vpt), equ) - vpt.begin();
  vpt.resize(N);

  for(int i=0; i<M; i++)
  {
    vector<int> vec;
    for(int j=0; j<N; j++)
      if(online(vpt[j], pt[i], qt[i]))
        vec.PB(j);
    pdd d = qt[i] - pt[i];
    for(int j=0; j<(int)vec.size(); j++)
      zz[vec[j]] = dot(d, vpt[vec[j]] - pt[i]);
    sort(ALL(vec), cmp2);

    for(int j=0; j<SZ(vec)-1; j++)
    {
      edge[vec[j]].PB(vec[j+1]);
      edge[vec[j+1]].PB(vec[j]);
    }
  }

  for(int i=0; i<N; i++)
    for(int j=0; j<MAXM; j++)
      vis[i][j] = -1;

  for(int i=0; i<N; i++)
  {
    for(auto x: edge[i])
      zz[x] = angle(vpt[x] - vpt[i]);
    sort(ALL(edge[i]), cmp2);
  }

  for(int i=0; i<N; i++)
    for(int j=0; j<SZ(edge[i]); j++)
      if(vis[i][j] == -1)
        dfs(i, j, P++);

  for(int i=0; i<P; i++)
  {
    for(int j=0; j<SZ(poly[i]); j++)
    {
      int k = (j==SZ(poly[i])-1 ? 0 : j+1);
      parea[i] -= cross(vpt[poly[i][j]], vpt[poly[i][k]]);
    }
  }

  for(int i=0; i<N; i++)
  {
    for(int j=0; j<SZ(edge[i]); j++)
    {
      int p1 = vis[i][j];
      pii r = rev[i][j];
      int p2 = vis[r.F][r.S];
      pedge[p1].PB({p2, 1});
    }
  }

  for(int i=0; i<P; i++)
  {
    if(i == 0 or  inpoly(poly[i], ss))
      ssin.PB(i);
    if(i == 0 or inpoly(poly[i], tt))
      ttin.PB(i);
  }

  for(int i=0; i<SZ(ssin)-1; i++)
  {
    int a = ssin[i], b = ssin[i+1];
    if(parea[a] > 0 && parea[b] < 0)
    {
      pedge[a].PB({b, 0});
      pedge[b].PB({a, 0});
    }
  }
  for(int i=0; i<SZ(ttin)-1; i++)
  {
    int a = ttin[i], b = ttin[i+1];
    if(parea[a] > 0 && parea[b] < 0)
    {
      pedge[a].PB({b, 0});
      pedge[b].PB({a, 0});
    }
  }

  int sp = ssin.back(), tp = ttin.back();
  priority_queue<pii, vector<pii>, greater<pii> > pq;
  for(int i=0; i<N; i++)
    pdis[i] = IINF;
  pdis[sp] = 0;
  pq.push({0, sp});
  while(!pq.empty())
  {
    int d = pq.top().F, v = pq.top().S;
    pq.pop();
    if(pdis[v] != d) continue;
    for(auto e: pedge[v])
    {
      int u = e.F, c = e.S;
      if(pdis[u] > d + c)
      {
        pdis[u] = d + c;
        pq.push({pdis[u], u});
      }
    }
  }

  return pdis[tp];
}

int main() {
  IOS;
  cin>>M;
  cin>>ss.F>>ss.S>>tt.F>>tt.S;
  for(int i=0; i<M; i++)
    cin>>pt[i].F>>pt[i].S>>qt[i].F>>qt[i].S;

  pt[M]={-IINF, IINF}; qt[M]={-IINF, -IINF}; M++;
  pt[M]={-IINF, -IINF}; qt[M]={IINF, -IINF}; M++;
  pt[M]={IINF, -IINF}; qt[M]={IINF, IINF}; M++;
  pt[M]={IINF, IINF}; qt[M]={-IINF, IINF}; M++;

  int ans = calc();
  cout<<ans<<endl;

  return 0;
}
