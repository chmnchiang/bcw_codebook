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

typedef long long ll;

const int MAXN = 55;
const ll MOD = 1000000007;

int N, K;
string s;
ll dp[MAXN][MAXN][MAXN], tmp[MAXN][MAXN][MAXN];
ll ten[MAXN];

void init()
{
  ten[0] = 1;
  for(int i=1; i<MAXN; i++)
    ten[i] = (ten[i-1] * 10) % MOD;
}

ll inv(ll x)
{
  ll p = MOD-2;
  ll ret = 1, cur = x;
  while(p)
  {
    if(p&1LL)
      ret = (ret * cur) % MOD;
    cur = (cur * cur) % MOD;
    p >>= 1;
  }
  return ret;
}

void pre()
{
  FZ(dp);
  dp[0][1][2] = 1;
  for(int i=0; i<K; i++)
  {
    FZ(tmp);
    for(int a=0; a<N; a++)
    {
      for(int b=0; b<N; b++)
      {
        for(int c=0; c<N; c++)
        {
          int arr[3];
          arr[0] = a; arr[1] = b; arr[2] = c;
          for(int j=0; j<3; j++)
          {
            if(arr[j] >= 3)
            {
              arr[j] = 3;
              for(int k=0; k<j; k++)
                if(arr[k] >= 3)
                  arr[j]++;
            }
          }

          if(arr[0] != a || arr[1] != b || arr[2] != c)
          {
            tmp[a][b][c] = tmp[arr[0]][arr[1]][arr[2]];
            continue;
          }

          for(int x=0; x<N; x++)
          {
            for(int y=x+1; y<N; y++)
            {
              arr[0] = a; arr[1] = b; arr[2] = c;
              for(int j=0; j<3; j++)
              {
                if(arr[j] == x) arr[j] = y;
                else if(arr[j] == y) arr[j] = x;
              }
              //if(dp[arr[0]][arr[1]][arr[2]])
              //cout<<a<<" "<<b<<" "<<c<<" => "<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<endl;;
              tmp[a][b][c] += dp[arr[0]][arr[1]][arr[2]];
              tmp[a][b][c] %= MOD;
            }
          }
        }
      }
    }
    swap(dp, tmp);
    for(int x=0; x<N; x++)
      for(int j=0; j<N; j++)
        for(int k=0; k<N; k++)
        {
          dp[x][j][k] %= MOD;
          //cout<<i<<" : "<<x<<" "<<j<<" "<<k<<" = "<<dp[x][j][k]<<endl;
        }
  }
}

ll calc()
{
  if(N <= 2) return 0;

  pre();
  
  ll ans = 0;
  int mpos = 0;
  for(int i=0; i<N; i++)
    if(s[i] == '*')
      mpos = i;

  for(int i=0; i<N; i++)
  {
    for(int j=0; j<N; j++)
    {
      if(i == j || i == mpos || j == mpos) continue;
      ll mult = (int)(s[i]-'0') * (s[j]-'0');
      ll zr = 0;
      for(int b=0; b<N; b++)
      {
        for(int a=0; a<b; a++)
        {
          for(int c=b+1; c<N; c++)
          {
            int arr[3];
            int cur = 3;
            if(a == i) arr[0] = 0;
            else if(a == mpos) arr[0] = 1;
            else if(a == j) arr[0] = 2;
            else arr[0] = cur++;
            if(b == i) arr[1] = 0;
            else if(b == mpos) arr[1] = 1;
            else if(b == j) arr[1] = 2;
            else arr[1] = cur++;
            if(c == i) arr[2] = 0;
            else if(c == mpos) arr[2] = 1;
            else if(c == j) arr[2] = 2;
            else arr[2] = cur++;

            ll num = dp[arr[0]][arr[1]][arr[2]];
            //cout<<a<<"/"<<b<<"/"<<c<<" : "<<arr[0]<<" "<<arr[1]<<" "<<arr[2]<<" num "<<num<<endl;
            ll dif = ten[b-a-1+N-c-1];
            zr += (num * dif) % MOD;
          }
        }
      }
      ll z = mult*zr;
      //cout<<s[i]<<"*"<<s[j]<<" : "<<z<<endl;
      ans += z;
      ans %= MOD;
    }
  }

  return ans;
}

int main() {
  init();
  IOS;
  int T;
  cin>>T;
  for(int t=1; t<=T; t++)
  {
    cin>>K>>s;
    N = s.size();
    ll ans = calc();
    cout<<"Case #"<<t<<": "<<ans<<endl;
  }

  return 0;
}
