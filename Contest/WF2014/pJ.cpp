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

typedef double ld;
typedef pair<ld, ld> pdd;

const int MAXN = 256;
const ld DINF = 1E20;
const ld IINF = 1E9;
const ld EPS = 1E-9;
const pdd BAD = {DINF, DINF};

int N, C;
ld Vy, A;
pdd pt[MAXN];
vector<pdd> dpup[MAXN], dpdown[MAXN][MAXN];
int ord[MAXN];
bool canuse[MAXN];
bool used[MAXN];

pdd trans(pdd v, ld dx, ld dt)
{
  if(dt < EPS)
  {
    if(abs(dx) < EPS) return v;
    return BAD;
  }

  ld lb = dx / dt - A * dt / 2, rb = dx / dt + A * dt / 2;
  v.F = max(v.F, lb);
  v.S = min(v.S, rb);
  if(v.F > v.S + EPS) return BAD;
  ld vl = v.S + A * dt - sqrt(2 * A * A * dt * dt - 4 * A * (dx - v.S * dt));
  ld vr = v.F - A * dt + sqrt(2 * A * A * dt * dt + 4 * A * (dx - v.F * dt));
  return {vl, vr};
}

void merge_interval(vector<pdd> &vec)
{
  vector<pdd> vtmp = vec;
  vec.clear();
  sort(ALL(vtmp));
  ld rb = -DINF*5;

  for(auto p: vtmp)
  {
    if(p.F > rb)
    {
      vec.PB(p);
      rb = p.S;
    }
    else
    {
      rb = max(rb, p.S);
      vec.back().S = rb;
    }
  }
}

bool interval_intersection(vector<pdd> &v1, vector<pdd> &v2)
{
  auto it1 = v1.begin(), it2 = v2.begin();
  while(it1 != v1.end() and it2 != v2.end())
  {
    if(it1->F < it2->F)
    {
      if(it1->S < it2->F) it1++;
      else return true;
    }
    else
    {
      if(it2->S < it1->F) it2++;
      else return true;
    }
  }
  return false;
}

bool cmp(int a, int b)
{
  if(abs(pt[a].S - pt[b].S) < EPS) return pt[a].F < pt[b].F;
  return pt[a].S < pt[b].S;
}

vector<int> calc()
{
  if(Vy == 0 and A == 0)
  {
    vector<int> vec;
    for(int i=1; i<=N; i++)
      if(pt[i].F == 0 and pt[i].S == 0)
        vec.PB(i);
    return vec;
  }
  else if(Vy == 0)
  {
    vector<int> vec;
    for(int i=1; i<=N; i++)
      if(pt[i].S == 0)
        vec.PB(i);
    return vec;
  }
  else if(A == 0)
  {
    vector<int> vec;
    for(int i=1; i<=N; i++)
      if(pt[i].F == 0)
        vec.PB(i);
    sort(ALL(vec), cmp);
    return vec;
  }

  for(int i=1; i<=N; i++)
    canuse[i] = (pt[i].S > -EPS);

  for(int i=0; i<=N; i++)
  {
    if(i==0 or canuse[i])
      ord[C++] = i;
  }
  sort(ord+1, ord+C, cmp);

  for(int i=0; i<C; i++)
    dpdown[ord[i]][0].PB({-DINF, DINF});

  for(int i=0; i<C; i++)
  {
    for(int j=C-1; j>=0; j--)
    {
      int v = ord[j];
      merge_interval(dpdown[v][i]);
      if(dpdown[v][i].empty()) continue;
      for(int k=0; k<j; k++)
      {
        int u = ord[k];
        ld dx = pt[v].F - pt[u].F;
        ld dt = (pt[v].S - pt[u].S) / Vy;
        for(auto vv: dpdown[v][i])
        {
          pdd vp = trans(vv, dx, dt);
          if(vp != BAD)
            dpdown[u][i+1].PB(vp);
        }
      }
    }
  }

  int ans = 0;
  vector<int> vres;

  dpup[0].PB({0, 0});
  while(interval_intersection(dpup[0], dpdown[0][ans+1]))
    ans++;

  int cur = 0;
  used[cur] = true;
  for(int i=0; i<ans; i++)
  {
    for(int j=0; j<=N; j++)
      if(j != cur)
        dpup[j].clear();
    for(int j=0; j<C; j++)
    {
      int v = ord[j];
      merge_interval(dpup[v]);
      if(dpup[v].empty()) continue;
      for(int k=j+1; k<C; k++)
      {
        int u = ord[k];
        for(auto vv: dpup[v])
        {
          ld dx = pt[u].F - pt[v].F;
          ld dt = (pt[u].S - pt[v].S) / Vy;
          pdd vp = trans(vv, dx, dt);
          if(vp != BAD)
            dpup[u].PB(vp);
        }
      }
    }

    for(int v=0; v<=N; v++)
    {
      if(!canuse[v] or used[v]) continue;
      if(interval_intersection(dpup[v], dpdown[v][ans-i-1]))
      {
        vres.PB(v);
        cur = v;
        used[v] = true;
        break;
      }
    }
  }
  
  return vres;
}

int main() {
  IOS;

  cin>>N>>Vy>>A;
  for(int i=1; i<=N; i++)
    cin>>pt[i].F>>pt[i].S;

  vector<int> ans = calc();
  int s = ans.size();
  if(s == 0)
    cout<<"Cannot visit any targets"<<endl;
  else
  {
    for(int i=0; i<s; i++)
      cout<<ans[i]<<(i==s-1 ? "\n" : " ");
  }

  return 0;
}
