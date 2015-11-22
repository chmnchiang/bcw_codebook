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

typedef long long ll;

const int MAXN = 42;
const ll INF = 1LL<<60;
const ll dx[] = {1, 0, -1, 0};
const ll dy[] = {0, 1, 0, -1};

int N;
ll D;
ll tx, ty;
ll px[MAXN], py[MAXN];
vector<ll> seg[4];
int sz[4];
ll dp[MAXN][MAXN][MAXN][MAXN];
ll ans = INF;

void add_dp(ll base, int type, int pos)
{
  for(int i=0; i<=pos; i++)
  {
    for(int j=0; i+j<=pos; j++)
    {
      for(int k=0; i+j+k<=pos; k++)
      {
        int l = pos - (i+j+k);
        dp[i][j][k][l] = INF;
        if(i) dp[i][j][k][l] = min(dp[i][j][k][l], dp[i-1][j][k][l] + base + (2*D)*((4-type)%4));
        if(j) dp[i][j][k][l] = min(dp[i][j][k][l], dp[i][j-1][k][l] + base + (2*D)*((5-type)%4));
        if(k) dp[i][j][k][l] = min(dp[i][j][k][l], dp[i][j][k-1][l] + base + (2*D)*((6-type)%4));
        if(l) dp[i][j][k][l] = min(dp[i][j][k][l], dp[i][j][k][l-1] + base + (2*D)*((7-type)%4));
      }
    }
  }
}

void dfs(int num[4], int lv, int cnt)
{
  if(lv == 4)
  {
    // for(int i=0; i<4; i++) cout<<num[i]<<" ";cout<<endl;

    ll sum[4];
    for(int i=0; i<4; i++)
      sum[i] = 0;
    ll bc = 0;
    ll offx = 0, offy = 0;
    ll cx = 0, cy = 0;

    for(int i=0; i<4; i++)
    {
      for(int j=0; j<sz[i]; j++)
      {
        if(j<num[i])
        {
          sum[i] += D*2 - seg[i][j];
          bc += 1;
          offx += dx[i] * D;
          offy += dy[i] * D;
          cx += (seg[i][j] - D) * dx[(i+1)%4];
          cy += (seg[i][j] - D) * dy[(i+1)%4];
        }
        // else
        // {
          // add_dp(D*2 - seg[i][j] + 1, (i+1)%4, ++cnt);
        // }
      }
    }

    // cout<<"GET DP "<<cnt<<endl;
    for(int i=0; i<=cnt; i++)
    {
      for(int j=0; i+j<=cnt; j++)
      {
        for(int k=0; i+j+k<=cnt; k++)
        {
          int l = cnt - (i+j+k);
          ll tarx = tx - offx - (i-k) * D;
          ll tary = ty - offy - (j-l) * D;
          ll cenx = cx + (j-l) * D;
          ll ceny = cy - (i-k) * D;
          
          if(tarx > cenx + sum[3] + l*D*2) continue;
          if(tarx < cenx - sum[1] - j*D*2) continue;
          if(tary > ceny + sum[0] + i*D*2) continue;
          if(tary < ceny - sum[2] - k*D*2) continue;

          ll cst = bc + dp[i][j][k][l] + abs(tarx - cenx) + abs(tary - ceny);
          ans = min(ans, cst);

          // for(int x=0; x<4; x++) cout<<num[x]<<" ";
          // cout<<","<<i<<" "<<j<<" "<<k<<" "<<l<<" = "<<cst<<endl;
          // cout<<"TAR "<<tarx<<","<<tary<<" CEN "<<cenx<<","<<ceny<<" DP "<<dp[i][j][k][l]<<endl;
        }
      }
    }

    return;
  }

  while(num[lv] >= 0)
  {
    // for(int i=0; i<4; i++)cout<<num[i]<<",";cout<<endl;
    dfs(num, lv+1, cnt);
    num[lv]--;
    if(num[lv] < 0) break;
    add_dp(D*2 - seg[lv][num[lv]] + 1, (lv+1)%4, ++cnt);
    // cout<<"ADD DP "<<cnt<<endl;
    for(int i=lv+1; i<4; i++) num[i] = sz[i];
  }
}

int main()
{
  IOS;
  cin>>N>>D>>tx>>ty;
  for(int i=0; i<N; i++)
    cin>>px[i]>>py[i];

  for(int i=0; i<N; i++)
  {
    if(px[i]==D && py[i]>-D) seg[0].PB(py[i]+D);
    if(py[i]==D && px[i]<D) seg[1].PB(-px[i]+D);
    if(px[i]==-D && py[i]<D) seg[2].PB(-py[i]+D);
    if(py[i]==-D && px[i]>-D) seg[3].PB(px[i]+D);
  }

  for(int i=0; i<4; i++)
    sort(seg[i].begin(), seg[i].end());

  // for(int i=0; i<4; i++){cout<<i<<" : ";for(auto v: seg[i]) cout<<v<<" ";cout<<endl;}

  int num[4];
  for(int i=0; i<4; i++)
    num[i] = sz[i] = seg[i].size();
  dfs(num, 0, 0);

  cout<<ans<<endl;

  return 0;
}
