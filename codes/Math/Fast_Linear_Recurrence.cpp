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

const int MAXN = 514;
const int LG = 61;
const ll MOD = 1000000007;

ll N;
int M;
ll f[LG][MAXN];
ll tmp[MAXN*2];
ll g[MAXN];

void calc_f(ll f0[MAXN], ll f1[MAXN], ll f2[MAXN])
{
  FZ(tmp);
  for(int i=0; i<M; i++)
    for(int j=0; j<M; j++)
      tmp[i+j] = (tmp[i+j] + f0[i] * f1[j]) % MOD;
  for(int i=2*M-2; i>=M; i--)
  {
    ll mrat = (MOD - tmp[i]) % MOD;
    tmp[i] = 0;
    for(int j=0; j<M; j++)
      tmp[i+j-M+1] = (tmp[i+j-M+1] + mrat * f[0][j]) % MOD;
    tmp[i-M] = (tmp[i-M] + mrat * (MOD-1)) % MOD;
  }
  for(int i=0; i<M; i++)
    f2[i] = tmp[i];
}

void make()
{
  for(int i=1; i<LG; i++)
    calc_f(f[i-1], f[i-1], f[i]);

  for(int i=0; i<10; i++)
  {
    for(int j=0; j<M; j++)
      cout<<f[i][j]<<" ";
    cout<<endl;
  }
}

ll calc(ll x)
{
  bool any = false;
  for(int i=0; i<LG; i++)
  {
    if(x&(1LL<<i))
    {
      if(!any)
      {
        any = true;
        for(int j=0; j<M; j++)
          g[j] = f[i][j];
      }
      else
      {
        calc_f(g, f[i], g);
      }
    }
  }

  return g[0];
}

int main()
{
  IOS;
  cin>>N>>M;

  for(int i=0; i<M; i++)
    cin>>f[0][i];

  // f[n] = \sum_{0 <= i < M} f[n-i-1]

  make();
  ll ans = calc(N);

  cout<<ans<<endl;

  return 0;
}
