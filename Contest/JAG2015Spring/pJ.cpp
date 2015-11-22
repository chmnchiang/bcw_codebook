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

const int MAXN = 65536;
const int INF = 1029384756;

int N, C;
pii pt[MAXN];
int hp[MAXN];
int tmp[MAXN];
bool alive[MAXN];
set<int> A, X;
int seg[MAXN*2];
bool tsanzi_ok;
vector<int> vtsanzi[MAXN];
int tsanzi_pos[MAXN];

void initSeg()
{
  for(int i=0; i<MAXN; i++)
    seg[i] = -1;
}

int cmin(int v1, int v2)
{
  if(v1 == -1) return v2;
  else if(v2 == -1) return v1;
  else
  {
    int s1 = pt[v1].S, s2 = pt[v2].S;
    if(s1 == s2) return min(v1, v2);
    else return (s1 < s2 ? v1 : v2);
  }
}

void updateSeg(int sp, int pos, int val, int lb, int rb)
{
  if(pos < lb || pos >= rb) return;
  if(rb - lb == 1)
  {
    seg[sp] = val;
    return;
  }
  int mb = (lb + rb) / 2;
  updateSeg(2*sp, pos, val, lb, mb);
  updateSeg(2*sp+1, pos, val, mb, rb);
  seg[sp] = cmin(seg[2*sp], seg[2*sp+1]);
}

int querySeg(int sp, int l, int r, int lb, int rb)
{
  if(r <= lb || l >= rb) return -1;
  if(l <= lb && rb <= r) return seg[sp];
  int mb = (lb + rb) / 2;
  int s1 = querySeg(2*sp, l, r, lb, mb);
  int s2 = querySeg(2*sp+1, l, r, mb, rb);
  return cmin(s1, s2);
}

void updatePoint(int pos, int val)
{
  updateSeg(1, pos, val, 0, N);
}

int queryRange(int l, int r)
{
  int lb = lower_bound(hp, hp+N, l) - hp;
  int rb = lower_bound(hp, hp+N, r) - hp;
  return querySeg(1, lb, rb, 0, N);
}

void disc()
{
  for(int i=0; i<N; i++)
    tmp[i] = pt[i].S;
  sort(tmp, tmp+N);
  int L = unique(tmp, tmp+N) - tmp;
  for(int i=0; i<N; i++)
    pt[i].S = lower_bound(tmp, tmp+L, pt[i].S) - tmp;
}

int findS()
{
  int pos = *A.begin();;
  int h = pt[pos].F;
  return queryRange(h-C, h+C+1);
}

void usePoint(int p)
{
  updatePoint(p, -1);
  A.erase(p);
  X.insert(p);
  alive[p] = false;

  int d = pt[p].S;
  tsanzi_pos[d]++;
  if(tsanzi_pos[d] == (int)vtsanzi[d].size())
    tsanzi_ok = false;
  else
  {
    int nxt = vtsanzi[d][tsanzi_pos[d]];
    int orig = vtsanzi[d][0];
    if(pt[nxt].F - pt[orig].F > C)
      tsanzi_ok = false;
  }
}

int main()
{
  IOS;
  cin>>N>>C;
  for(int i=0; i<N; i++)
    cin>>pt[i].F>>pt[i].S;
  sort(pt, pt+N);
  for(int i=0; i<N; i++)
    hp[i] = pt[i].F;
  disc();
  initSeg();
  tsanzi_ok = true;

  for(int i=0; i<N; i++)
  {
    A.insert(i);
    alive[i] = true;
    updatePoint(i, i);
    vtsanzi[pt[i].S].PB(i);
  }

  while(1)
  {
    int s = findS();

    vector<int> vec;
    vec.PB(s);
    usePoint(s);

    while(!vec.empty())
    {
      int v = vec.back();
      vec.pop_back();

      int h = pt[v].F;
      int p;
      while((p = queryRange(-INF, h-C)) != -1)
      {
        usePoint(p);
        vec.PB(p);
      }
      while(((p = queryRange(h-C, h+C+1)) != -1) && pt[p].S < pt[v].S)
      {
        usePoint(p);
        vec.PB(p);
      }
    }

    if(!tsanzi_ok) break;
  }

  int ans = X.size();
  cout<<ans<<endl;

  return 0;
}
