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

typedef pair<int, int> pii;

const int N = 16;

int state[N+1][N+1];
int tag[N+1][N+1];
set<pii> nset;

pii nei(int x, int y)
{
  pii res = {0, 0};
  for(int j=x-1; j<=x+1; j++)
  {
    for(int k=y-1; k<=y+1; k++)
    {
      if(j==x && k==y) continue;
      if(j<1 || j>N || k<1 || k>N) continue;
      if(state[j][k] != -1 || tag[j][k] == 0) continue;
      if(tag[j][k] == 1) res.F++;
      else res.S++;
    }
  }

  return res;
}

bool dfs(int x, int y, bool s)
{
  bool res = false;
  tag[x][y] = s;
  vector<pii> van;
  for(int j=x-1; j<=x+1; j++)
  {
    for(int k=y-1; k<=y+1; k++)
    {
      if(j==x && k==y) continue;
      if(j<1 || j>N || k<1 || k>N) continue;
      if(state[j][k] == -1) continue;
      if(nset.count({j, k})) continue;
      van.PB({j, k});
    }
  }
  for(auto p: van)
    nset.insert(p);

  pii m = {-1, -1};
  int bst = 1234;
  bool fail = false;
  for(auto v: nset)
  {
    pii r = nei(v.F, v.S);
    if(r.S == 0)
    {
      if(r.F != state[v.F][v.S])
        fail = true;
    }
    else if(r.S < bst)
    {
      bst = r.S;
      m = v;
    }
  }

  if(!fail)
  {
    if(m.F == -1)
    {
      res = true;
    }
    else
    {
      int px = -1, py = -1;
      for(int j=m.F-1; j<=m.F+1; j++)
      {
        for(int k=m.S-1; k<=m.S+1; k++)
        {
          if(j==m.F && k==m.S) continue;
          if(j<1 || j>N || k<1 || k>N) continue;
          if(state[j][k] != -1 || tag[j][k] != -1) continue;
          px = j;
          py = k;
        }
      }
      if(dfs(px, py, true))
        res = true;
      else if(dfs(px, py, false))
        res = true;
    }
  }

  for(auto p: van)
    nset.erase(p);
  tag[x][y] = -1;

  return res;
}

bool test(int tx, int ty)
{
  return !dfs(tx, ty, true);
}

int main() {
  IOS;

  int px, py;
  cin>>px>>py;

  for(int i=1; i<=N; i++)
    for(int j=1; j<=N; j++)
      state[i][j] = -1, tag[i][j] = -1;

  while(1)
  {
    assert(px != -1 && py != -1);
    cout<<1<<" "<<px<<" "<<py<<endl;

    int l = 0;
    if(!(cin>>l)) assert(false);
    for(int i=0; i<l; i++)
    {
      int a, b, c;
      cin>>a>>b>>c;
      state[a][b] = c;
    }

    px = py = -1;
    for(int i=1; i<=N; i++)
    {
      if(px != -1) break;
      for(int j=1; j<=N; j++)
      {
        if(state[i][j] != -1) continue;
        if(test(i, j))
        {
          px = i;
          py = j;
          break;
        }
      }
    }

    if(px == -1 && py == -1)
    {
      for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
          if(state[i][j] == -1)
            cout<<3<<" "<<i<<" "<<j<<endl;
      cout<<4<<endl;
      break;
    }
  }

  return 0;
}
