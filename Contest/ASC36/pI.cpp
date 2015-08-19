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

typedef pair<int, int> pii;

const int MAXN = 1010;
const long double PI = acosl(-1);

int N;
int px[MAXN], py[MAXN];
int deg[MAXN];
long double theta[MAXN];
vector<pii> edge;

void solve(vector<int> vec, int cen, long double inth, int d);
  
bool cmp(int a, int b)
{
  return theta[a] < theta[b];
}

void make_edge(int c, vector<int> &vec)
{
  int sz = vec.size();
  if(sz == 0) return;

  vector<int> v1, v2;
  bool used = false;
  int cen = -1;
  int d1 = 0, d2 = 0;
  int sum = 0;

  for(int i=0; i<sz; i++)
  {
    int v = vec[i];
    int nsum = sum + deg[v] - 2;
    if(!used && (nsum >= 0 || i == sz-1))
    {
      d1 = -sum;
      cen = v;
      d2 = deg[v]-1 - d1;
      used = true;
    }
    else if(!used)
      v1.PB(v);
    else if(used)
      v2.PB(v);
    sum = nsum;
  }

  edge.PB(MP(c, cen));
  long double th = atan2(py[cen]-py[c], px[cen]-px[c]);
  solve(v1, cen, th, d1);
  solve(v2, cen, th, d2);
}

void solve(vector<int> vec, int cen, long double inth, int d)
{
  if(vec.size() <= 0) return;
  int cx = px[cen];
  int cy = py[cen];
  for(auto v: vec)
  {
    theta[v] = atan2l(py[v]-cy, px[v]-cx) - inth;
    while(theta[v] < -PI) theta[v] += 2*PI;
    while(theta[v] >= PI) theta[v] -= 2*PI;
  }
  sort(vec.begin(), vec.end(), cmp);

  int prog = 0, sum = 0;
  vector<int> curvec;

  for(int i=0; i<(int)vec.size(); i++)
  {
    int v = vec[i];
    sum += deg[v] - 2;
    curvec.PB(v);
    if((sum < prog && sum >= -d+1) || (i >= (int)vec.size()-1))
    {
      prog = sum;
      make_edge(cen, curvec);
      curvec.clear();
    }
  }
}

int main()
{
  freopen("roads.in", "r", stdin);
  freopen("roads.out", "w", stdout);
  IOS;
  cin>>N;
  for(int i=0; i<N; i++)
    cin>>px[i]>>py[i]>>deg[i];

  int mx = -1;
  for(int i=0; i<N; i++)
    if(mx == -1 || px[i] < px[mx])
      mx = i;

  vector<int> lst;
  for(int i=0; i<N; i++)
    if(i != mx)
      lst.PB(i);

  solve(lst, mx, 0., deg[mx]);

  for(auto p: edge)
    cout<<p.F+1<<" "<<p.S+1<<"\n";

  return 0;
}
