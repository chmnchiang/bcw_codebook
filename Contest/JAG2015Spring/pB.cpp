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

const int MAXN = 606;
const int MAXW = 180480;
const unsigned short INF = -1;

int N, K, A, B, W;
int arr[MAXN];
unsigned short dp[MAXN][2][MAXW], tb[MAXN][2][MAXW];
bool ok[MAXW];
int ldis[MAXW], rdis[MAXW], dis[MAXW];
bool choose[MAXN];

vector<int> trace(int w)
{
  vector<int> ret;
  for(int i=0; i<K; i++)
    choose[i] = true;
  int i = K, k = 0;
  while(i>0 || k>0)
  {
    if(k == 0)
    {
      bool t = tb[i][k][w];
      i--;
      if(t)
      {
        w += arr[i];
        choose[i] = false;
        k = 1;
      }
    }
    else
    {
      int j = tb[i][k][w];
      if(j == INF)
        i--;
      else
      {
        w -= arr[K+j];
        choose[K+j] = true;
        k = 0;
      }
    }
  }

  for(int x=0; x<N; x++)
    if(choose[x])
      ret.PB(x+1);

  return ret;
}

int main()
{
  IOS;
  cin>>N>>K>>A>>B;
  for(int i=0; i<N; i++)
    cin>>arr[i];

  memset(dp, -1, sizeof(dp));

  int w = 0;
  for(int i=0; i<K; i++)
    w += arr[i];

  W = 0;
  for(int i=0; i<N; i++)
    W += arr[i];

  dp[0][0][w] = 0;

  for(int i=0; i<K; i++)
  {
    for(int s=0; s<=W; s++)
    {
      if(dp[i][0][s] == INF) continue;
      // cout<<"DP "<<i<<" 0 "<<s<<" = "<<dp[i][0][s]<<endl;
      if(dp[i+1][0][s] > dp[i][0][s])
      {
        dp[i+1][0][s] = dp[i][0][s];
        tb[i+1][0][s] = 0;
      }
      int last = (i==0 ? INF : dp[i-1][0][s]);
      last = min(last, N-K-1);
      for(int j=dp[i][0][s]; j<=last; j++)
      {
        int sa = s + arr[K+j];
      // cout<<" => "<<i<<" 1 "<<sa<<endl;
        if(dp[i][1][sa] > j+1)
        {
          dp[i][1][sa] = j+1;
          tb[i][1][sa] = j;
        }
      }
    }
    for(int s=0; s<=W; s++)
    {
      if(dp[i][1][s] == INF) continue;
      // cout<<"DP "<<i<<" 1 "<<s<<" = "<<dp[i][1][s]<<endl;

      if(dp[i+1][1][s] > dp[i][1][s])
      {
        dp[i+1][1][s] = dp[i][1][s];
        tb[i+1][1][s] = INF;
      }

      int sa = s - arr[i];
      if(dp[i+1][0][sa] > dp[i][1][s])
      {
        dp[i+1][0][sa] = dp[i][1][s];
        tb[i+1][0][sa] = 1;
      }
      // cout<<" => "<<i+1<<" 0 "<<s-arr[i]<<endl;
    }
  }

  for(int i=0; i<MAXW; i++)
    ok[i] = (dp[K][0][i] < INF);

   for(int i=0; i<MAXW; i++)
  {
    ldis[i] = (i==0 ? 1000000 : ldis[i-1]) + 1;
    if(ok[i]) ldis[i] = 0;
  }
  for(int i=MAXW-1; i>=0; i--)
  {
    rdis[i] = (i==MAXW-1 ? 1000000 : rdis[i+1]) + 1;
    if(ok[i]) rdis[i] = 0;
    dis[i] = min(ldis[i], rdis[i]);
  }

  int t = A;
  for(int i=A; i<=B; i++)
  {
    if(dis[i] > dis[t])
      t = i;
  }

  int target = -1;
  for(int i=0; i<=W; i++)
  {
    if(!ok[i]) continue;
    if(target == -1 || abs(t-i) < abs(t-target))
      target = i;
  } 
  vector<int> vec = trace(target);

  // for(int i=0; i<180001; i++) if(ok[i]) cout<<i<<" OK"<<endl;
  cout<<t<<endl;
  for(int i=0; i<K; i++)
    cout<<vec[i]<<(i==K-1 ? "\n" : " ");

  return 0;
}
