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

double P;
int PR;
int M, N;

double prob_sub(double x, int lv)
{
  if(lv >= 1000) return 0;
  if(x > 0.5) return P + (1-P) * prob_sub(2*x-1, lv+1);
  else return P * prob_sub(2*x, lv+1);
}

int main()
{
  IOS;
  cin>>PR>>M>>N;
  P = PR / 100.0;

  double ans = 0;
  int bnum;
  vector<int> vp;

  if(PR == 0 || PR == 50 || PR == 100)
  {
    if(PR == 0) ans = 0;
    else if(PR == 100) ans = 1;
    else ans = (double)M / N;

    int maxbet = min(M, N-M);
    if(PR == 0 || PR == 100)
      maxbet = M;

    if(maxbet <= 200)
    {
      for(int i=1; i<=maxbet; i++)
        vp.PB(i);
    }
    else
    {
      for(int i=1; i<=100; i++)
        vp.PB(i);
      for(int i=maxbet-100+1; i<=maxbet; i++)
        vp.PB(i);
    }
    bnum = maxbet;
  }
  else if(PR < 50)
  {
    ans = prob_sub((double)M / N, 0);
    int lb = 0, rb = N;
    while(1)
    {
      if(M == lb || M == rb) break;
      vp.PB(min(rb-M, M-lb));
      int mb = (lb + rb) / 2;
      if(rb - mb != mb - lb) break;
      if(M > mb) lb = mb;
      else rb = mb;
    }

    sort(vp.begin(), vp.end());
    vp.resize(unique(vp.begin(), vp.end()) - vp.begin());
    bnum = vp.size();
  }
  else
  {
    double r = (1-P) / P;
    double alpha = (1-r) / (1-pow(r, N));
    ans = alpha * (1-pow(r, M)) / (1-r);
    vp.PB(1);
    bnum = vp.size();
  }
  
  cout<<fixed<<setprecision(10)<<ans<<endl;
  cout<<bnum<<endl;
  int SZ = vp.size();
  for(int i=0; i<SZ; i++)
    cout<<vp[i]<<(i==SZ-1 ? "\n" : " ");

  return 0;
}
