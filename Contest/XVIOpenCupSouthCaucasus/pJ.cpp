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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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

typedef long long ll;
typedef pair<ll, int> pii;

const int MAXN = 10101;
const int MAXT = 13;
const ll INF = 1LL<<50;

int N, M, T, V;
int SS, TT;
ll eup[MAXN][MAXT], edown[MAXN][MAXT];
multiset<pii> edge[MAXT][MAXT];
ll dis[MAXT];
pii prv[MAXT];
bool inq[MAXT];
ll ans = 0;

void erase2(multiset<pii> &m, pii x)
{
  m.erase(m.lower_bound(x));
}

void flow_up(int i, int t)
{
  ans += eup[i][t];
  for(int j=0; j<T; j++)
    erase2(edge[SS][j], {eup[i][j], i});
  edge[t][SS].insert({-eup[i][t], i});
  for(int u=0; u<T; u++)
  {
    if(u == t) continue;
    edge[t][u].insert({-eup[i][t] + eup[i][u], i});
  }
}

void unflow_up(int i, int t)
{
  ans -= eup[i][t];
  for(int j=0; j<T; j++)
    edge[SS][j].insert({eup[i][j], i});
  erase2(edge[t][SS], {-eup[i][t], i});
  for(int u=0; u<T; u++)
  {
    if(u == t) continue;
    erase2(edge[t][u], {-eup[i][t] + eup[i][u], i});
  }
}

void flow_down(int i, int t)
{
  ans += edown[i][t];
  for(int j=0; j<T; j++)
    erase2(edge[j][TT], {edown[i][j], N+i});
  edge[TT][t].insert({-edown[i][t], N+i});
  for(int u=0; u<T; u++)
  {
    if(u == t) continue;
    edge[u][t].insert({-edown[i][t] + edown[i][u], N+i});
  }
}

void unflow_down(int i, int t)
{
  ans -= edown[i][t];
  for(int j=0; j<T; j++)
    edge[j][TT].insert({edown[i][j], N+i});
  erase2(edge[TT][t], {-edown[i][t], N+i});
  for(int u=0; u<T; u++)
  {
    if(u == t) continue;
    erase2(edge[u][t], {-edown[i][t] + edown[i][u], N+i});
  }
}

void calc()
{
  for(int i=0; i<N; i++)
    for(int j=0; j<T; j++)
      eup[i][j] *= -1;
  for(int i=0; i<M; i++)
    for(int j=0; j<T; j++)
      edown[i][j] *= -1;

  SS = T, TT = T + 1, V = T + 2;
  for(int i=0; i<N; i++)
    for(int j=0; j<T; j++)
      edge[SS][j].insert({eup[i][j], i});
  for(int i=0; i<M; i++)
    for(int j=0; j<T; j++)
      edge[j][TT].insert({edown[i][j], N+i});

  while(true)
  {
    for(int i=0; i<V; i++)
      dis[i] = INF;
    dis[SS] = 0;
    queue<int> q;
    for(int i=0; i<V; i++)
      inq[i] = false;
    q.push(SS);
    inq[SS] = true;

    while(!q.empty())
    {
      int v = q.front();
      inq[v] = false;
      q.pop();
      for(int u=0; u<V; u++)
      {
        if(u == v) continue;
        if(edge[v][u].empty()) continue;
        ll c = dis[v] + edge[v][u].begin()->F;
        if(c < dis[u])
        {
          if(!inq[u])
          {
            q.push(u);
            inq[u] = true;
          }
          dis[u] = c;
          prv[u] = {v, edge[v][u].begin()->S};
        }        
      }
    }

    if(dis[TT] == INF) break;
    int cur = TT;
    while(cur != SS)
    {
      int nxt = prv[cur].F, v = prv[cur].S;
      if(nxt == SS)
        flow_up(v, cur);
      else if(cur == SS)
        unflow_up(v, nxt);
      else if(nxt == TT)
        unflow_down(v-N, cur);
      else if(cur == TT)
        flow_down(v-N, nxt);
      else if(v >= N)
      {
        unflow_down(v-N, cur);
        flow_down(v-N, nxt);
      }
      else
      {
        unflow_up(v, nxt);
        flow_up(v, cur);
      }

      cur = nxt;
    }
  }
}

int main() {
  IOS;
  cin>>N>>M>>T;
  for(int i=0; i<N; i++)
    for(int j=0; j<T; j++)
      cin>>eup[i][j];
  for(int i=0; i<M; i++)
    for(int j=0; j<T; j++)
      cin>>edown[i][j];

  calc();
  cout<<(-ans)<<endl;

  return 0;
}
