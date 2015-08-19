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

const int MAXN = 52;
const int MAXM = 5050;
const int INF = 1029384756;

int N, C;
int w[MAXN];
int ord[MAXN];
bool dp1[MAXN][MAXM], dp2[MAXN][MAXN][MAXM];
bool ls1[MAXN][MAXM], ls2[MAXN][MAXN][MAXM];
int nxt[MAXM];
vector<int> va, vb;

bool cmp(int a, int b)
{
  return w[a] < w[b];
}

void calc()
{
  for(int i=0; i<=N; i++)
  {
    for(int j=0; j<=C; j++)
    {
      dp1[i][j] = false;
      ls1[i][j] = false;
    }
  }
      
  for(int k=0; k<=N; k++)
  {
    for(int i=0; i<=N; i++)
    {
      for(int j=0; j<=C; j++)
      {
        dp2[k][i][j] = false;
        ls2[k][i][j] = false;
      }
    }
  }

  dp1[0][0] = true;
  for(int i=0; i<N; i++)
  {
    int wei = w[ord[i]];
    for(int j=0; j<=C; j++)
    {
      if(!dp1[i][j]) continue;
      dp1[i+1][j] = true;
      ls1[i+1][j] = false;
      if(j+wei<=C && !dp1[i+1][j+wei])
      {
        dp1[i+1][j+wei] = true;
        ls1[i+1][j+wei] = true;
      }
    }
  }

  dp2[N][0][0] = true;
  for(int i=N-1; i>=0; i--)
  {
    int wei = w[ord[i]];
    for(int j=0; j<=N; j++)
    {
      for(int k=0; k<=C; k++)
      {
        if(!dp2[i+1][j][k]) continue;
        dp2[i][j][k] = true;
        ls2[i][j][k] = false;
        if(k+wei<=C && j<N &&!dp2[i][j+1][k+wei])
        {
          dp2[i][j+1][k+wei] = true;
          ls2[i][j+1][k+wei] = true;
        }
      }
    }
  }
}

void trace1(int v, int wei)
{
  if(v == 0) return;
  if(ls1[v][wei])
  {
    int wv = w[ord[v-1]];
    va.PB(ord[v-1]);
    vb.PB(ord[v-1]);
    trace1(v-1, wei-wv);
  }
  else
  {
    trace1(v-1, wei);
  }
}

void trace2(int v, int i, int j)
{
  if(v == N) return;
  if(ls2[v][i][j])
  {
    int wv = w[ord[v]];
    vb.PB(ord[v]);
    trace2(v+1, i-1, j-wv);
  }
  else
  {
    trace2(v+1, i, j);
  }
}

bool getans()
{
  for(int v=0; v<N; v++)
  {
    int wv = w[ord[v]];
    int awei = wv;

    for(int i=0; i<=C+1; i++)
      nxt[i] = -1;
    for(int i=C; i>=0; i--)
    {
      nxt[i] = nxt[i+1];
      if(dp1[v][i])
        nxt[i] = i;
    }

    for(int i=0; i<=N-v-1; i++)
    {
      for(int j=0; j<=C; j++)
      {
        if(!dp2[v+1][i][j]) continue;
        int lb = C-j-wv+1, rb = C-j;
        lb = max(lb, 0);
        rb = min(rb, C-awei);
        int n = nxt[lb];
        if(n == -1 || n > rb) continue;

        for(int k=v; k<=v+i; k++)
          va.PB(ord[k]);
        trace1(v, n);
        trace2(v+1, i, j);

        return false;
      }
      awei += w[ord[v+i+1]];
    }
  }

  return true;
}

int main()
{
  freopen("knapsack.in", "r", stdin);
  freopen("knapsack.out", "w", stdout);

  IOS;

  cin>>N;
  for(int i=0; i<N; i++)
    cin>>w[i];
  cin>>C;

  for(int i=0; i<N; i++)
    ord[i] = i;
  sort(ord, ord+N, cmp);

  calc();
  bool res = getans();
  if(res)
  {
    cout<<"YES"<<endl;
  }
  else
  {
    cout<<"NO"<<endl<<3<<endl;
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    cout<<va.size()<<" ";
    for(auto v: va) cout<<v+1<<" ";cout<<endl;
    cout<<vb.size()<<" ";
    for(auto v: vb) cout<<v+1<<" ";cout<<endl;
  }

  return 0;
}
