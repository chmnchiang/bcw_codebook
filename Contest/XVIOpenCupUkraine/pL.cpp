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
typedef pair<ll, ll> pll;

const int MAXN = 302;
const int MAXM = 42;
const int MAXK = 6;
const double INF = 1E20;

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
double abs(pll a){return sqrt(dot(a, a));}

int N, M, K;
pll pt[MAXN], qt[MAXM];
int color[MAXN];
double dp[MAXM][MAXM][MAXM][1<<MAXK];
int trimask[MAXM][MAXM][MAXM];

bool in_triangle(pll a, pll b, pll c, pll p)
{
  if(cross(b-a, p-a) <= 0) return false;
  if(cross(c-b, p-b) <= 0) return false;
  if(cross(a-c, p-c) <= 0) return false;
  return true;
}

double calc()
{
  sort(qt, qt+M);

  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      for(int k=0; k<M; k++)
        for(int l=0; l<M; l++)
          if(in_triangle(qt[j], qt[k], qt[l], pt[i]))
            trimask[j][k][l] |= 1<<color[i];

  for(int i=0; i<M; i++)
    for(int j=0; j<M; j++)
      for(int k=0; k<M; k++)
        for(int l=0; l<(1<<K); l++)
          dp[i][j][k][l] = INF;

  for(int i=0; i<M; i++)
    dp[i][i][i][0] = 0;

  for(int i=0; i<M; i++)
  {
    for(int j=i; j<M; j++)
    {
      for(int k=i; k<M; k++)
      {
        //for(int l=0; l<(1<<K); l++) cout<<i<<" "<<j<<" "<<k<<" "<<l<<" : "<<dp[i][j][k][l]<<endl;
        int mn = min(j, k);
        for(int m=mn; m<M; m++)
        {
          double dlen = abs(qt[m] - qt[j]) + abs(qt[m] - qt[k]) - abs(qt[j] - qt[k]);
          for(int l=0; l<(1<<K); l++)
          {
            if(dp[i][j][k][l] > INF/2) continue;
            double nlen = dp[i][j][k][l] + dlen;
            int nl = l | trimask[k][j][m];
            //cout<<i<<" "<<j<<" "<<k<<" => "<<m<<" "<<nlen<<" "<<nl<<endl;
            if(j <= k)
              dp[j][m][k][nl] = min(dp[j][m][k][nl], nlen);
            else
              dp[k][j][m][nl] = min(dp[k][j][m][nl], nlen);
          }
        }
      }
    }
  }

  double ans = INF;
  for(int i=0; i<M; i++)
    for(int j=i; j<M; j++)
      for(int k=i; k<M; k++)
        ans = min(ans, dp[i][j][k][(1<<K)-1]);

  return ans;
}

int main() {
  IOS;
  
  cin>>N>>M>>K;
  for(int i=0; i<N; i++)
    cin>>pt[i].F>>pt[i].S;
  for(int i=0; i<N; i++)
  {
    cin>>color[i];
    color[i]--;
  }
  for(int i=0; i<M; i++)
    cin>>qt[i].F>>qt[i].S;

  double ans = calc();
  if(ans >= INF/2)
    cout<<-1<<endl;
  else
    cout<<fixed<<setprecision(10)<<ans<<endl;

  return 0;
}
