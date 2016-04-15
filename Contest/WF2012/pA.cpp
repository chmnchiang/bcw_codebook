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

typedef long double ld;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ld, pii> pdp;

const int MAXN = 52;
const int MAXM = 1280;
const ld EPS = 1E-8;

int N, M;
int px[MAXN], py[MAXN], pz[MAXN], vx[MAXN], vy[MAXN], vz[MAXN];
pii edgev[MAXM];
map<pii, int> vedge;
int aa[MAXM], bb[MAXM], cc[MAXM];
ld curval[MAXM];
vector<pdp> events;
ld T;
int ord[MAXM];
ll hval[MAXM];
ll cur_hash;
int djRoot[MAXN];
bool inuse[MAXM];
vector<int> cedge[MAXN];

void djInit()
{
  for(int i=0; i<N; i++)
    djRoot[i] = i;
}

int djFind(int v)
{
  if(djRoot[v] == v) return v;
  return djRoot[v] = djFind(djRoot[v]);
}

bool djUnion(int u, int v)
{
  int pu = djFind(u), pv = djFind(v);
  if(pu == pv) return false;
  djRoot[pu] = pv;
  return true;
}

ld eval(int i)
{
  return aa[i] * T * T + bb[i] * T + cc[i];
}

bool cmp(int a, int b)
{
  return curval[a] < curval[b];
}

void build_tree()
{
  djInit();
  for(int i=0; i<M; i++)
    inuse[i] = false;

  for(int i=0; i<N; i++)
    cedge[i].clear();

  for(int i=0; i<M; i++)
  {
    int e = ord[i];
    int a, b;
    tie(a, b) = edgev[e];
    inuse[e] = djUnion(a, b);
    if(inuse[e])
    {
      cur_hash += hval[e];
      cedge[a].PB(b);
      cedge[b].PB(a);
    }
  }
}

bool dfs(int u, int p, int target, int f1, int f2)
{
  if(u == target) return true;
  for(auto v: cedge[u])
  {
    if(v == p) continue;
    if((u == f1 && v == f2) || (u == f2 && v == f1)) continue;
    if(dfs(v, u, target, f1, f2)) return true;
  }

  return false;
}

void swap_edge(int a, int b)
{
  if(!inuse[a] && inuse[b])
  {
    int au, av, bu, bv;
    tie(au, av) = edgev[a];
    tie(bu, bv) = edgev[b];

    if(!dfs(au, -1, av, bu, bv)) // delete b, add a
    {
      inuse[a] = true;
      inuse[b] = false;
      cur_hash += hval[a] - hval[b];
      for(auto it=cedge[bu].begin(); it!=cedge[bu].end(); it++)
      {
        if(*it == bv)
        {
          cedge[bu].erase(it);
          break;
        }
      }
      for(auto it=cedge[bv].begin(); it!=cedge[bv].end(); it++)
      {
        if(*it == bu)
        {
          cedge[bv].erase(it);
          break;
        }
      }
      cedge[au].PB(av);
      cedge[av].PB(au);
    }
  }
}

int calc()
{
  M = 0;
  vedge.clear();
  for(int i=0; i<N; i++)
  {
    for(int j=i+1; j<N; j++)
    {
      int dx = px[j] - px[i], dy = py[j] - py[i], dz = pz[j] - pz[i];
      int dvx = vx[j] - vx[i], dvy = vy[j] - vy[i], dvz = vz[j] - vz[i];
      aa[M] = dvx * dvx + dvy * dvy + dvz * dvz;
      bb[M] = 2 * (dvx * dx + dvy * dy + dvz * dz);
      cc[M] = dx * dx + dy * dy + dz * dz;
      edgev[M] = {i, j};
      vedge[{i, j}] = vedge[{j, i}] = M;
      M++;
    }
  }

  for(int i=0; i<M; i++)
    hval[i] = (ll)rand() + RAND_MAX * (ll)rand();
  cur_hash = 0;

  events.clear();
  for(int i=0; i<M; i++)
  {
    for(int j=i+1; j<M; j++)
    {
      ll da = aa[j] - aa[i], db = bb[j] - bb[i], dc = cc[j] - cc[i];
      if(da == 0 && db == 0) continue;

      if(da == 0)
      {
        ld t = -(ld)dc / db;
        if(t > EPS)
        {
          if(db > 0)
            events.PB({t, {i, j}});
          else
            events.PB({t, {j, i}});
        }
      }
      else
      {
        ll delta = db * db - 4 * da * dc;
        if(delta <= 0) continue;
        ld sd = sqrtl(delta);
        ld t1 = (-db - sd) / (2. * da);
        ld t2 = (-db + sd) / (2. * da);
        if(t1 > EPS)
          events.PB({t1, {j, i}});
        if(t2 > EPS)
          events.PB({t2, {i, j}});
      }
    }
  }

  sort(ALL(events));

  int ans = 1;
  T = EPS;
  for(int i=0; i<M; i++)
    curval[i] = eval(i);
  for(int i=0; i<M; i++)
    ord[i] = i;
  sort(ord, ord+M, cmp);

  build_tree();
  ll hash_val = cur_hash;
  int pos = 0;
  int E = events.size();
  while(pos < E)
  {
    T = events[pos].F;
    int rb = pos;
    while(rb < E && events[rb].F <= T + EPS)
      rb++;

    vector<pii> evs;
    for(int i=pos; i<rb; i++)
      evs.PB(events[i].S);

    for(auto p: evs)
    {
      curval[p.F] = eval(p.F);
      curval[p.S] = eval(p.S);
    }

    for(auto p: evs)
      swap_edge(p.F, p.S);

    if(cur_hash != hash_val)
    {
      ans++;
      cur_hash = hash_val;
    }

    pos = rb;
  }

  return ans;
}

int main() {
  IOS;

  int t = 0;
  while(cin>>N)
  {
    t++;
    for(int i=0; i<N; i++)
      cin>>px[i]>>py[i]>>pz[i]>>vx[i]>>vy[i]>>vz[i];

    int ans = calc();
    cout<<"Case "<<t<<": "<<ans<<endl;
  }

  return 0;
}
