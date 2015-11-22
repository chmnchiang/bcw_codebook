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

typedef pair<int, int> pii;

const int MAXN = 55;

int N;
int tarx, tary;
char c[MAXN];
int lb[MAXN], rb[MAXN];
char fc[MAXN];
int diff[MAXN];
int dir[MAXN];
int fv[MAXN];
bool fre[MAXN];
int rem;
vector<pii> vec;
int findval, finddif;

bool dfs1(int i, int x, int y, int tdx, int tdy, int d);

int cval(char ch)
{
  if(ch == 'L') return 1;
  else if(ch == 'R') return 3;
  return 0;
}

void dfs0(int i, int val, int td)
{
  if(i >= N)
  {
    vec.PB(MP(val, val+td));
    return;
  }
  if(!fre[i])
    dfs0(i+2, val, td);
  else
  {
    dfs0(i+2, val+lb[i], td+diff[i]);
    dfs0(i+2, val-rb[i], td+diff[i]);
  }
}

bool dfs2(int i, int val, int td)
{
  if(i >= N)
  {
    rem = findval - val;
    return 0 <= rem && rem <= td;
  }
  if(!fre[i])
    return dfs2(i+2, val, td);
  else
  {
    dir[i] = 0;
    if(dfs2(i+2, val+lb[i], td+diff[i]))
      return true;
    dir[i] = 1;
    if(dfs2(i+2, val-rb[i], td+diff[i]))
      return true;
  }
  return false;
}

bool any(int lbb, int rbb)
{
  auto it = lower_bound(vec.begin(), vec.end(), MP(lbb, 2100000000));

  if(it != vec.end())
  {
    if(it->F <= rbb)
    {
      findval = it->F;
      return true;
    }
  }
  if(it != vec.begin())
  {
    it--;
    if(it->S >= lbb)
    {
      findval = lbb;
      return true;
    }
  }

  return false;
}

bool trans(int i, int x, int y, int tdx, int tdy, int d, char cy, char cx)
{
  if(cy == 'L')
    d = (d+1)%4;
  else
    d = (d+3)%4;
  if(cy != '?')
  {
    tdy += diff[i-1];
    dir[i-1] = d/2;
    if(dir[i-1])
      y -= rb[i-1];
    else
      y += lb[i-1];
  }

  if(cx == 'L')
    d = (d+1)%4;
  else
    d = (d+3)%4;
  tdx += diff[i];
  dir[i] = d/2;
  if(dir[i])
    x -= rb[i];
  else
    x += lb[i];

  return dfs1(i+2, x, y, tdx, tdy, d);
}

bool dfs1(int i, int x, int y, int tdx, int tdy, int d)
{
  if(i >= N+2)
  {
    if(!(x <= tarx && tarx <= x+tdx)) return false;
    int lbb = tary-y-tdy, rbb = tary-y;
    rem = tarx - x;
    return any(lbb, rbb);
  }

  int qcnt = (c[i-1]=='?') + (c[i]=='?');

  if(qcnt == 0)
  {
    if(trans(i, x, y, tdx, tdy, d, c[i-1], c[i]))
      return true;
  }
  else if(qcnt == 1)
  {
    if(c[i-1] == '?')
    {
      if(trans(i, x, y, tdx, tdy, d, 'L', c[i]))
        return true;
      if(trans(i, x, y, tdx, tdy, d, 'R', c[i]))
        return true;
    }
    else
    {
      if(trans(i, x, y, tdx, tdy, d, c[i-1], 'L'))
        return true;
      if(trans(i, x, y, tdx, tdy, d, c[i-1], 'R'))
        return true;
    }
  }
  else
  {
    if(trans(i, x, y, tdx, tdy, d, '?', 'L'))
      return true;
    if(trans(i, x, y, tdx, tdy, d, '?', 'R'))
      return true;
  }
  
  return false;
}

void make_vec()
{
  vector<pii> nvec = vec;
  vec.clear();
  sort(nvec.begin(), nvec.end());
  int last = -2100000000;

  for(auto v: nvec)
  {
    int l = v.F, r = v.S;
    if(l > last)
    {
      vec.PB(MP(l, r));
      last = r;
    }
    else
    {
      last = max(last, r);
      vec.back().S = last;
    }
  }
}

int main()
{
  IOS;
  cin>>N>>tarx>>tary;
  for(int i=0; i<N; i++)
    cin>>c[i]>>lb[i]>>rb[i];
  lb[N] = rb[N] = lb[N+1] = rb[N+1] = 0;
  c[N] = c[N+1] = '?';
  for(int i=0; i<N+2; i++)
  {
    fre[i] = true;
    diff[i] = rb[i] - lb[i];
  }
  for(int i=0; i<N; i+=2)
    if(c[i] != '?' || c[i+1] != '?')
      fre[i] = false;

  bool ok = true;

  dfs0(0, 0, 0);
  make_vec();

  ok = dfs1(1, 0, 0, 0, 0, 0);

  for(int i=1; i<N; i+=2)
  {
    int use = min(rem, diff[i]);
    if(dir[i])
      fv[i] = rb[i] - use;
    else
      fv[i] = lb[i] + use;
    rem -= use;
  }

  if(!dfs2(0, 0, 0))
    ok = false;

  rem = tary;
  for(int i=0; i<N; i+=2)
  {
    if(dir[i])
      rem += rb[i];
    else
      rem -= lb[i];
  }

  for(int i=0; i<N; i+=2)
  {
    int use = min(rem, diff[i]);
    if(dir[i])
      fv[i] = rb[i] - use;
    else
      fv[i] = lb[i] + use;
    rem -= use;
  }

  int curd = 0;
  for(int i=0; i<N; i++)
  {
    int nd = dir[i]*2 + ((i+1)%2);
    if((nd+1)%4 == curd)
      fc[i] = 'R';
    else
      fc[i] = 'L';
    curd = nd;
  }

  if(!ok)
  {
    cout<<-1<<endl;
    return 0;
  }
  else
  {
    cout<<N<<endl;
    for(int i=0; i<N; i++)
      cout<<fc[i]<<" "<<fv[i]<<endl;
  }

  for(int i=0; i<N; i++)
    if(c[i] != '?')
      assert(c[i] == fc[i]);

  int nx = 0, ny = 0;
  for(int i=0; i<N; i++)
  {
    assert(lb[i] <= fv[i] && fv[i] <= rb[i]);
    int d = (dir[i] ? -1 : 1) * fv[i];
    if(i%2)
      nx += d;
    else
      ny += d;
  }
  assert(nx == tarx);
  assert(ny == tary);

  return 0;
}
