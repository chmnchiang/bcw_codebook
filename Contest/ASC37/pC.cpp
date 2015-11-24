#include<bits/stdc++.h>
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

const int MAXN = 222;

string S;
int W;

double ans[MAXN];

int main()
{
  FILEIO("blind");
  IOS;
  cin>>S;
  W = S.size();

  for(int i=1; i<=2*W; i++)
  {
    double prob[i];
    for(int j=0; j<i; j++)
    {
      prob[j] = 0;
      for(int k=0; k<W; k++)
        if(S[(k*i+j)%W] == '1')
          prob[j] += 1;
      prob[j] /= W;
      prob[j] -= 0.5;
    }
    sort(prob, prob+i);
    int split = 0;
    while(split < i && prob[split] < 0)
      split++;
    double cur = 0;
    for(int j=0; j<split; j++)
      cur -= prob[j];
    for(int j=split; j<i; j++)
      cur += prob[j];

    for(int k=W; i<=2*k; k--)
    {
      while(split > k)
      {
        split--;
        cur += 2 * prob[split];
      }
      while(i-split > k)
      {
        cur -= 2 * prob[split];
        split++;
      }

      ans[k] = max(ans[k], cur / i + 0.5);
    }
  }

  for(int i=1; i<=W; i++)
    cout<<fixed<<setprecision(15)<<ans[i]<<"\n";

  return 0;
}
