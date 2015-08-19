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

const int MAXN = 105;
const int MAXL = 10;

int N, P;
int l[MAXN];
int a[MAXN][MAXL];
int s[MAXN], d[MAXN], t[MAXN], tend[MAXN];
int pos[MAXN];
int status[MAXN];
vector<int> vec[MAXN];

int main()
{
  freopen("hot.in", "r", stdin);
  freopen("hot.out", "w", stdout);

  cin>>N;
  for(int i=0; i<N; i++)
  {
    cin>>l[i];
    for(int j=0; j<l[i]; j++)
    {
      cin>>a[i][j];
      a[i][j]--;
    }
  }
  cin>>P;
  for(int i=0; i<P; i++)
  {
    cin>>s[i]>>d[i]>>t[i];
    s[i]--;
    d[i]--;
  }

  for(int i=0; i<P; i++)
  {
    int p = s[i];
    for(int tm=t[i]; tm<88888; tm++)
    {
      if(p == d[i])
      {
        tend[i] = tm;
        status[i] = 1;
        break;
      }
      p = a[p][tm%l[p]];
    }
    if(status[i] == 0) status[i] = 3;
    else status[i] = 0;
  }

  for(int tm=0; tm<88888; tm++)
  {
    for(int i=0; i<N; i++)
      vec[i].clear();
    for(int i=0; i<P; i++)
    {
      if(status[i] == 0 && t[i] == tm)
      {
        status[i] = 1;
        pos[i] = s[i];
      }
      if(status[i] == 1)
        vec[pos[i]].PB(i);
    }
    for(int i=0; i<N; i++)
    {
      while((int)vec[i].size() >= 2)
      {
        if(tend[vec[i][0]] > tend[vec[i].back()])
          swap(vec[i][0], vec[i].back());
        status[vec[i].back()] = 3;
        vec[i].pop_back();
      }
    }

    for(int i=0; i<P; i++)
    {
      if(status[i] == 1 && pos[i] == d[i])
        status[i] = 2;
    }
    for(int i=0; i<P; i++)
    {
      if(status[i] == 1)
      {
        pos[i] = a[pos[i]][tm%l[pos[i]]];
        vec[pos[i]].PB(i);
      }
    }
  }

  int ans = 0;
  for(int i=0; i<P; i++)
    if(status[i] == 2)
      ans++;
  cout<<ans<<endl;
  for(int i=0; i<P; i++)
    if(status[i] == 2)
      cout<<i+1<<" ";
  cout<<endl;

  return 0;
}
