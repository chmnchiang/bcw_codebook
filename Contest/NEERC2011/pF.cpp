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

typedef long double ld;
typedef pair<double, double> pdd;

const int MAXN = 202020;
const ld INF = 1E12;
const ld EPS = 1E-15;

int N, M;
ld cen[MAXN], a[MAXN], b[MAXN], c[MAXN];
map<ld, int> seg[MAXN];
vector<ld> segseg[MAXN];
vector<ld> spos[MAXN];
vector<int> sv[MAXN];

ld eval(int i, ld x)
{
  return a[i] * x * x + b[i] * x + c[i];
}

pdd intersection(int v1, int v2)
{
  ld da = a[v2] - a[v1];
  ld db = b[v2] - b[v1];
  ld dc = c[v2] - c[v1];
  if(abs(da) < EPS)
  {
    if(abs(db) < EPS)
      return {INF, INF};
    else
      return {-dc/db, INF};
  }
  else
  {
    ld det = db * db - 4 * da * dc;
    if(det < EPS)
      return {INF, INF};
    det = sqrtl(det);
    return {(-db+det)/(2*da), (-db-det)/(2*da)};
  }
}

ld interval_max(int v, ld l, ld r)
{
  if(l > r) return 0;
  ld mx = max(eval(v, l), eval(v, r));
  if(l < cen[v] && cen[v] < r)
    mx = max(mx, eval(v, cen[v]));
  return mx;
}

void update_segseg(int s, int ss, int lb, int rb, int pos, ld val)
{
  if(pos < lb || pos >= rb) return;
  if(rb - lb == 1)
  {
    segseg[s][ss] = val;
  }
  else
  {
    int mb = (lb + rb) / 2;
    update_segseg(s, 2*ss, lb, mb, pos, val);
    update_segseg(s, 2*ss+1, mb, rb, pos, val);
    segseg[s][ss] = max(segseg[s][2*ss], segseg[s][2*ss+1]);
  }
}

ld query_segseg(int s, int ss, int lb, int rb, int l, int r)
{
  if(l >= r) return 0;
  if(rb <= l || r <= lb) return 0;
  if(l <= lb && rb <= r) return segseg[s][ss];

  int mb = (lb + rb) / 2;
  ld v1 = query_segseg(s, 2*ss, lb, mb, l, r);
  ld v2 = query_segseg(s, 2*ss+1, mb, rb, l, r);
  return max(v1, v2);
}

ld query_interval(int s, ld l, ld r)
{
  int lb = lower_bound(spos[s].begin(), spos[s].end(), l) - spos[s].begin();
  int rb = lower_bound(spos[s].begin(), spos[s].end(), r) - spos[s].begin();

  ld res = query_segseg(s, 1, 0, spos[s].size(), lb, rb-1);
  res = max(res, interval_max(sv[s][lb-1], l, min(r, spos[s][lb])));
  res = max(res, interval_max(sv[s][rb-1], max(l, spos[s][rb-1]), r));
  res = max(res, 0.L);

  return res;
}

ld query(int s, int lb, int rb, int lt, int rt, ld l, ld r)
{
  if(rb <= lt || rt <= lb) return 0;
  if(lt <= lb && rb <= rt)
    return query_interval(s, l, r);

  int mb = (lb + rb) / 2;
  ld v1 = query(2*s, lb, mb, lt, rt, l, r);
  ld v2 = query(2*s+1, mb, rb, lt, rt, l, r);
  return max(v1, v2);
}

void make_seg(int s, int lb, int rb)
{
  if(rb - lb == 1)
  {
    seg[s][-INF] = lb;
  }
  else
  {
    int mb = (lb + rb) / 2;
    make_seg(2*s, lb, mb);
    make_seg(2*s+1, mb, rb);

    auto &m1 = seg[2*s], &m2 = seg[2*s+1];
    auto it1 = m1.begin(), it2 = m2.begin();
    ld pos = -INF;
    int lst = -1;

    while(1)
    {
      vector<ld> vp;
      vp.PB(pos);

      auto jt1 = it1, jt2 = it2;
      jt1++;
      jt2++;
      ld p1 = (jt1 == m1.end() ? INF : jt1->F);
      ld p2 = (jt2 == m2.end() ? INF : jt2->F);
      ld npos = min(p1, p2);
      vp.PB(npos);

      int v1 = it1->S, v2 = it2->S;
      ld g1, g2;
      tie(g1, g2) = intersection(v1, v2);
      if(pos < g1 && g1 < npos) vp.PB(g1);
      if(pos < g2 && g2 < npos) vp.PB(g2);
      
      sort(vp.begin(), vp.end());
      for(int i=0; i<(int)vp.size()-1; i++)
      {
        if(vp[i+1] - vp[i] < EPS) continue;
        ld mid = (vp[i] + vp[i+1]) / 2;
        int lar = (eval(v1, mid) > eval(v2, mid) ? v1 : v2);
        if(lar != lst)
        {
          seg[s][vp[i]] = lar;
          lst = lar;
        }
      }

      if(p1 < p2)
        it1++;
      else
        it2++;

      pos = npos;
      if(npos >= INF)
        break;
    }
  }

  int S = seg[s].size();
  segseg[s].resize(S*4);
  int cnt = 0;
  auto it = seg[s].begin();
  while(it != seg[s].end())
  {
    ld l = it->F;
    int v = it->S;
    spos[s].PB(l);
    sv[s].PB(v);
    it++;
    ld r = it->F;
    ld mx = interval_max(v, l, r);
    update_segseg(s, 1, 0, S, cnt, mx);
    cnt++;
  }
}

int main()
{
  FILEIO("flights");

  IOS;
  cin>>N;
  for(int i=0; i<N; i++)
  {
    ld p, x, y;
    cin>>p>>x>>y;
    ld pv = p - x;
    cen[i] = x;
    a[i] = -y / (pv * pv);
    b[i] = (2 * y * x) / (pv * pv);
    c[i] = y * (1 - (x * x) / (pv * pv));
  }

  make_seg(1, 0, N);

  cin>>M;
  for(int i=0; i<M; i++)
  {
    int lt, rt;
    ld l, r;
    cin>>lt>>rt>>l>>r;
    lt--;
    ld res = query(1, 0, N, lt, rt, l, r);

    cout<<fixed<<setprecision(10)<<res<<"\n";
  }

  return 0;
}
