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
#define endl "\n"
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

const int MAXN = 32;

int N;
ll dp[MAXN][MAXN][MAXN];

ll calc()
{
  for(int i=0; i<N; i++)
    for(int j=i+1; j<N; j++)
      dp[i][j-i-1][N-j-1] = 1;

  for(int x=N-2; x>0; x--)
  {
    for(int i=0; i<N; i++)
    {
      for(int j=0; j<N; j++)
      {
        int k = x-i-j;
        if(k<0) continue;
        if(!dp[i][j][k]) continue;

        if(i > 0)
          for(int z=0; z<i; z++)
            dp[z][j+i-z-1][k] += dp[i][j][k];
        else if(j > 0)
          dp[0][j-1][k] += dp[i][j][k];

        if(k > 0)
          for(int z=0; z<k; z++)
            dp[i][j+z][k-z-1] += dp[i][j][k];
        else if(j > 0)
          dp[i][j-1][0] += dp[i][j][k];
      }
    }
  }

  return dp[0][0][0];
}

int main() {
  FILEIO("permutominoes");
  IOS;
  cin>>N;

  ll ans = calc();
  cout<<ans<<endl;

  return 0;
}
