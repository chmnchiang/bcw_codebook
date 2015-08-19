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
// Let's Fight!

typedef pair<int, int> pii;

const int MAXN = 101010;

int N, M;
vector<int> edge[MAXN];
int deg[MAXN], dep[MAXN];
int rem[MAXN];

void dfs(int v)
{
  if(dep[v] != -1) return;
  dep[v] = 0;
  for(auto c: edge[v])
  {
    dfs(c);
    dep[v] = max(dep[v], dep[c] + 1);
  }
}

void relax(int v, priority_queue<pii> &pq)
{
  for(auto c: edge[v])
  {
    deg[c]--;
    if(deg[c] == 0)
      pq.push(MP(2*dep[c]+rem[c], c));
  }
}

int main()
{
  freopen("documents.in", "r", stdin);
  freopen("documents.out", "w", stdout);
  
  IOS;
  cin>>N>>M;
  for(int i=0; i<M; i++)
  {
    int a, b;
    cin>>a>>b;
    a--;
    b--;
    deg[b]++;
    edge[a].PB(b);
  }
  for(int i=0; i<N; i++)
    dep[i] = -1;
  for(int i=0; i<N; i++)
    dfs(i);

  for(int i=0; i<N; i++)
    rem[i] = 2;

  int tm = 0;
  priority_queue<pii> pq;
  for(int i=0; i<N; i++)
    if(deg[i] == 0)
      pq.push(MP(2*dep[i]+rem[i], i));

  while(!pq.empty())
  {
    tm++;
    int v = pq.top().S;
    pq.pop();
    if(!pq.empty())
    {
      int u = pq.top().S;
      pq.pop();

      rem[v]--;
      rem[u]--;
      if(rem[v] == 0) relax(v, pq);
      else pq.push(MP(2*dep[v]+rem[v], v));
      if(rem[u] == 0) relax(u, pq);
      else pq.push(MP(2*dep[u]+rem[u], u));
    }
    else
    {
      rem[v]--;
      if(rem[v] == 0) relax(v, pq);
      else pq.push(MP(2*dep[v]+rem[v], v));
    }
  }

  double ans = tm / 2.0;
  cout<<ans<<endl;

  return 0;
}
