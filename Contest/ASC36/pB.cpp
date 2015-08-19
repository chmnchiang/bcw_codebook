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

typedef long long ll;

const int MAXN = 32;

int N, K, M;
ll R;

struct Seg
{
  ll ans;
  ll allc[MAXN][MAXN], nzc[MAXN];
  int len;
  ll val;

  Seg()
  {
    ans = len = 0;
    for(int i=0; i<MAXN; i++)
    {
      nzc[i] = 0;
      for(int j=0; j<MAXN; j++)
        allc[i][j] = 0;
    }
    val = 0;
  }

  Seg(Seg &s)
  {
    ans = s.ans;
    len = s.len;
    val = s.val;
    for(int i=0; i<MAXN; i++)
    {
      nzc[i] = s.nzc[i];
      for(int j=0; j<MAXN; j++)
        allc[i][j] = s.allc[i][j];
    }
  }

  Seg merge(Seg &s)
  {
    Seg ret;
    ret.ans = (ans + s.ans) % R;
    ret.len = len + s.len;
    while(ret.len >= N) ret.len -= M;
    int mult = 1;
    for(int i=0; i<s.len; i++)
      mult = (mult * 10) % N;
    ret.val = (val * mult + s.val) % N;

    for(int i=0; i<N; i++)
    {
      ret.nzc[i] += s.nzc[i];
      int k = (i * mult + s.val) % N;
      ret.nzc[k] += nzc[i];
    }

    int mt = 1;
    for(int i=0; i<N; i++)
    {
      int l = len + i;
      while(l >= N) l -= M;
      for(int j=0; j<N; j++)
      {
        ret.allc[i][j] += allc[i][j];
        int k = (val * mt + j) % N;
        ret.allc[l][k] += s.allc[i][j]; 
      }
      mt = (mt * 10) % N;
    }

    for(int i=0; i<N; i++)
    {
      ret.nzc[i] %= R;
      for(int j=0; j<N; j++)
        ret.allc[i][j] %= R;
    }

    mt = 1;
    for(int i=0; i<N; i++)
    {
      for(int j=0; j<N; j++)
      {
        int l = (j * mt) % N;
        for(int k=0; k<N; k++)
        {
          if(l == 0)
          {
            ret.ans += nzc[j] * s.allc[i][k];
            ret.ans %= R;
          }
          l++;
          if(l >= N) l -= N;
        }
      }
      mt = (mt * 10) % N;
    }
    
    return ret;
  }
};

string tra[MAXN];
int used[MAXN];
Seg snum[MAXN], salp[MAXN];

void init()
{
  for(int i=0; i<N; i++)
    used[i] = -1;
  int now = 1 % N;
  for(int i=0; ; i++)
  {
    if(used[now] != -1)
    {
      M = i - used[now];
      break;
    }
    used[now] = i;
    now = (now * 10) % N;
  }

  for(int i=0; i<10; i++)
  {
    snum[i].len = 1;
    snum[i].val = i % N;
    snum[i].allc[1%N][i%N]++;
    if(i>0)
      snum[i].nzc[i%N]++;
    snum[i].ans = (i%N==0);
  }
}

Seg& getseg(char c)
{
  if(c >= '0' && c <= '9') return snum[c-'0'];
  else return salp[c-'A'];
}

int main()
{
  freopen("divisible.in", "r", stdin);
  freopen("divisible.out", "w", stdout);

  IOS;
  cin>>N>>R>>K;

  init();

  for(int i=0; i<K; i++)
  {
    string s;
    cin>>s;
    tra[s[0]-'A'] = s.substr(3);
  }

  for(int i=25; i>=0; i--)
  {
    int len = tra[i].size();
    if(len == 0) continue;
    salp[i] = getseg(tra[i][0]);
    for(int j=1; j<len; j++)
      salp[i] = salp[i].merge(getseg(tra[i][j]));
  }

  ll ans = salp[0].ans % R;
  if(ans < 0) ans += R;
  cout<<ans<<endl;

  return 0;
}
