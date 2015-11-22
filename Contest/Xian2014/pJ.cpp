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
#define MC(n,m) memcpy((n),(m),sizeof(m))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;

const int MAXN = 52;

int N;
int A[MAXN];
vector<int> edge[MAXN];
ll dp[MAXN][MAXN][MAXN], sum[MAXN][MAXN][MAXN];
ll tmp[MAXN][MAXN], smp[MAXN][MAXN];
int sz[MAXN];
int dep[MAXN];

void init()
{
  for(int i=0; i<N; i++)
  {
    edge[i].clear();
  }
  for(int i=0; i<=N; i++)
    for(int j=0; j<=N; j++)
      for(int k=0; k<=N; k++)
        dp[i][j][k] = sum[i][j][k] = 0;
}

void calc(int v)
{
  sz[v] = 0;

  for(int d=dep[v]+1; d<=N; d++)
    dp[v][d][0] = 1;

  int ub = min(dep[v] + A[v] + 1, N);

  for(auto c: edge[v])
  {
    dep[c] = dep[v] + 1;
    calc(c);

    FZ(tmp);
    FZ(smp);

    for(int d=dep[c]; d<=N; d++)
    {
      for(int a=0; a<=sz[v]; a++)
      {
        if(!dp[v][d][a] && !sum[v][d][a]) continue;
        for(int b=0; b<=sz[c]; b++)
        {
          tmp[d][a+b] += dp[v][d][a] * dp[c][d][b];
          smp[d][a+b] += sum[v][d][a] * dp[c][d][b] + dp[v][d][a] * sum[c][d][b];
        }
      }
    }

    MC(dp[v], tmp);
    MC(sum[v], smp);
    sz[v] += sz[c];
  }

  for(int d=dep[v]; d<=N; d++)
  {
    int md = max(d, ub);
    for(int l=sz[v]; l>=0; l--)
    {
      dp[v][d][l+1] += dp[v][md][l];
      sum[v][d][l+1] += sum[v][md][l];
    }
  }

  sz[v]++; 

  for(int l=0; l<=sz[v]; l++)
  {
    ll alpha = dp[v][ub][l];
    for(int d=dep[v]; d<ub; d++)
      sum[v][d][l] += alpha - dp[v][d][l];
  }
}

int main()
{
  int TT;
  scanf("%d", &TT);

  for(int _t=1; _t<=TT; _t++)
  {
    scanf("%d", &N);
    init();
    for(int i=0; i<N; i++)
      scanf("%d", &A[i]);
    for(int i=1; i<N; i++)
    {
      int x;
      scanf("%d", &x);
      edge[x-1].PB(i);
    }

    dep[0] = 0;
    calc(0);

    // for(int v=0; v<N; v++)
    // {
      // cout<<" ===== VERTEX "<<v<<" ====="<<endl;
      // for(int i=0; i<=sz[v]; i++)
      // {
        // cout<<i<<" : "<<endl;
        // for(int d=dep[v]; d<=N; d++)
          // cout<<"DEP "<<d<<" : "<<dp[v][d][i]<<" SUM "<<sum[v][d][i]<<endl;
      // }
    // }

    // for(int i=0; i<=N; i++)
      // cout<<sum[0][0][i]<<" ";
    // cout<<endl;

    double ans = 0;
    for(int i=1; i<=N; i++)
    {
      double prob = sum[0][0][i-1];
      for(int j=1; j<=i-1; j++) prob *= j;
      for(int j=1; j<=N-i+1; j++) prob *= j;
      for(int j=1; j<=N; j++) prob /= j;
      prob /= N-i+1;
      double expect = 0;
      for(int j=N-i+1; j<=N; j++) expect += 1.0 / j;
      expect *= N;
      ans += prob * expect;
    }

    printf("Case #%d: %.12f\n", _t, ans);
  }

  return 0;
}
