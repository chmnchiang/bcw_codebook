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

typedef pair<int, int> pii;

const int MAXN = 77;
const int INF = 1029384756;

int N, M, L, U;
int x[MAXN][MAXN];
bool valid[MAXN][MAXN];
int rs[MAXN], cs[MAXN];

struct Edge
{
  int v, c, f, re;
  Edge() {v=f=re=-1;c=0;}
  Edge(int _v, int _c, int _f, int _r)
  {
    v=_v; c=_c; f=_f; re=_r;
  }
};

int V, SS, TT;
int dis[MAXN*2];
int prv[MAXN*2], prl[MAXN*2];
vector<pii> sedge[MAXN*2];
vector<Edge> edge[MAXN*2];

void init()
{
  V = N+M+2;
  SS = N+M;
  TT = N+M+1;
  for(int i=0; i<V; i++)
  {
    edge[i].clear();
    sedge[i].clear();
    dis[i] = INF;
  }
  for(int i=0; i<N; i++)
    rs[i] = 0;
  for(int i=0; i<M; i++)
    cs[i] = 0;
}

void add_edge(int u, int v, int cc, int f)
{
  edge[u].PB(Edge(v, cc, f, edge[v].size()));
  edge[v].PB(Edge(u, -cc, 0, edge[u].size()-1));
}

void make_edge()
{
  for(int i=0; i<N; i++)
    add_edge(SS, i, 0, rs[i]);
  for(int i=0; i<M; i++)
    add_edge(N+i, TT, 0, cs[i]);
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      if(valid[i][j])
      {
        add_edge(i, N+j, U-x[i][j], INF);
        add_edge(N+j, i, -L+x[i][j], INF);
      }
}

bool feasible()
{
  dis[SS] = 0;
  int cnt = 0;
  queue<pii> Q;
  Q.push({SS, 0});
  while(!Q.empty())
  {
    pii p = Q.front();
    Q.pop();
    int v = p.F, cc = p.S;
    if(dis[v] < cc) continue;
    cnt++;
    if(cnt > (V+4)*(V+4))
      return false;
    for(auto e: edge[v])
    {
      if(e.f == 0) continue;
      int newdis = dis[v] + e.c;
      if(dis[e.v] > newdis)
      {
        dis[e.v] = newdis;
        Q.push({e.v, newdis});
      }
    }
  }
  return true;
}

int cost_flow()
{
  int cst = 0;
  int f = 0;
  while(1)
  {
    for(int i=0; i<V; i++)
      dis[i] = INF;
    dis[SS] = 0;
    
    queue<int> Q;
    Q.push(SS);
    while(!Q.empty())
    {
      int v = Q.front();
      Q.pop();

      for(int i=0; i<(int)edge[v].size(); i++)
      {
        auto e = edge[v][i];
        if(e.f == 0) continue;
        int newdis = dis[v] + e.c;
        if(newdis < dis[e.v])
        {
          dis[e.v] = newdis;
          prv[e.v] = v;
          prl[e.v] = i;
          Q.push(e.v);
        }
      }
    }

    if(dis[TT] == INF) break;

    int minf = INF;
    int cur = TT;
    while(cur != SS)
    {
      int l = prl[cur];
      cur = prv[cur];
      minf = min(minf, edge[cur][l].f);
    }

    int nowc = 0;
    cur = TT;
    while(cur != SS)
    {
      int l = prl[cur];
      int nxt = prv[cur];
      int rl = edge[nxt][l].re;
      nowc += edge[nxt][l].c;
      edge[nxt][l].f -= minf;
      edge[cur][rl].f += minf;
      cur = nxt;
    }
    cst += minf * nowc;
    f += minf;
  }

  int z = 0;
  for(int i=0; i<N; i++) z += rs[i];
  if(f != z) while(1);

  return cst;
}

void make_sol()
{
  for(int i=0; i<N; i++)
  {
    for(auto e: edge[i])
    {
      int j = e.v;
      if(j < N || j >= N+M) continue;
      if(e.f > INF/2)
      {
        sedge[i].PB({j, e.c});
        if(e.f < INF)
          sedge[j].PB({i, -e.c});
      }
      else
      {
        sedge[j].PB({i, -e.c});
        if(e.f > 0)
          sedge[i].PB({j, e.c});
      }
    }
  }
  for(int i=0; i<N+M; i++)
    sedge[SS].PB({i, 0});

  for(int i=0; i<V; i++)
    dis[i] = INF;
  dis[SS] = 0;
  queue<int> Q;
  Q.push(SS);
  
  while(!Q.empty())
  {
    int v = Q.front();
    Q.pop();
    for(auto e: sedge[v])
    {
      int newdis = dis[v] + e.S;
      if(newdis < dis[e.F])
      {
        dis[e.F] = newdis;
        Q.push(e.F);
      }
    }
  }
}

int main()
{
  IOS;
  int T;
  cin>>T;
  for(int _t=1; _t<=T; _t++)
  {
    cout<<"Case "<<_t<<": ";
    cin>>N>>M>>L>>U;
    init();
    for(int i=0; i<N; i++)
    {
      for(int j=0; j<M; j++)
      {
        string s;
        cin>>s;
        if(s == "X")
          valid[i][j] = false;
        else
        {
          valid[i][j] = true;
          x[i][j] = atoi(s.c_str());
          rs[i]++;
          cs[j]++;
        }
      }
    }

    make_edge();
    if(!feasible())
    {
      cout<<"Impossible"<<endl;
      continue;
    }

    int ans = cost_flow();
    for(int i=0; i<N; i++)
      for(int j=0; j<M; j++)
        if(valid[i][j])
          ans += x[i][j];

    make_sol();

    cout<<ans<<endl;
    for(int i=0; i<N; i++)
      cout<<(-dis[i])<<(i==N-1 ? "\n" : " ");
    for(int i=0; i<M; i++)
      cout<<(-dis[N+i])<<(i==M-1 ? "\n" : " ");
  }

  return 0;
}
