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

const int MAXN = 201010;

int N1, N2, M, R;
ll ln[MAXN], rn[MAXN];
ll lwait[MAXN], rwait[MAXN];
ll lcost[MAXN], rcost[MAXN];
int lstop[MAXN], rstop[MAXN];

ll clast(ll x, ll y)
{
  if(x < 0) return 0;
  ll t = x / y;
  ll rem = x % y;
  return rem * (t+1) + t * (t+1) * y / 2;
}

void calc()
{
  ll cul = 0, cur = 0;
  for(int i=0; i<M; i++)
  {
    cul += ln[i] - N1;
    cul = max(0LL, cul);
    lwait[i] = cul;
    cur += rn[i] - N2 - 1;
    rwait[i] = cur;
    cur = max(0LL, cur);
  }

  vector<int> vec;
  for(int i=0; i<M; i++)
  {
    ll x = lwait[i];
    vec.PB(i);

    while((int)vec.size() > x)
    {
      lstop[vec.back()] = i;
      vec.pop_back();
    }
  }
  while(!vec.empty())
  {
    lstop[vec.back()] = M;
    vec.pop_back();
  }

  ll totcost = 0;
  for(int i=0; i<M; i++)
    totcost += lwait[i];
  ll lastwait = max(0LL, lwait[M-1] - N1);

  lcost[0] = totcost + clast(lastwait, N1); 
  for(int i=0; i<M; i++)
  {
    int s = lstop[i];
    totcost -= s - i;
    if(s == M && lastwait > 0)
      lastwait--;
    lcost[i+1] = totcost + clast(lastwait, N1);
  }

  queue<int> q;
  for(int i=0; i<M; i++)
  {
    ll x = max(0LL, -rwait[i]);
    q.push(i);
    
    while(x > 0 && !q.empty())
    {
      rstop[q.front()] = i;
      q.pop();
      x--;
    }
  }

  while(!q.empty())
  {
    rstop[q.front()] = M;
    q.pop();
  }

  totcost = 0;
  for(int i=0; i<M; i++)
    totcost += max(0LL, rwait[i]);
  lastwait = max(0LL, rwait[M-1]) - N2 - 1;

  rcost[0] = totcost + clast(lastwait, N2+1);
  for(int i=0; i<M; i++)
  {
    int s = rstop[i];
    totcost += s - i;
    if(s == M)
      lastwait++;
    rcost[i+1] = totcost + clast(lastwait, N2+1);
  }
}

int main()
{
  FILEIO("lanes");
  IOS;

  cin>>N1>>N2>>M>>R;
  int oM = M;
  M += R;
  for(int i=0; i<M; i++)
    cin>>ln[i]>>rn[i];

  calc();

  ll bestt = -1;
  ll bestval = 1E16;

  for(int t=0; t<oM; t++)
  {
    ll val = lcost[t] + rcost[t+R];
    if(val < bestval)
    {
      bestval = val;
      bestt = t;
    }
  }

  cout<<bestt+1<<endl;

  return 0;
}
