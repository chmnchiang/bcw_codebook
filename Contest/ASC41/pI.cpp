//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

const int MAXN = 10;

int N;
int ans;

vector<int> poly[MAXN][MAXN];

void init()
{
  vector<int> p;
  p.PB(1);
  for(int i=0; i<=9; i++)
  {
    poly[i][i] = p;
    for(int j=i+1; j<=9; j++)
    {
      poly[j][i].PB(0);
      for(auto k: poly[j-1][i])
        poly[j][i].PB(k);
    }
    p.PB(0);
    for(int j=(int)p.size()-2; j>=0; j--)
    {
      p[j+1] -= p[j];
    }
  }

  if(0)for(int i=0; i<=9; i++)
  {
    for(int j=0; j<=i; j++)
    {
      cout<<i<<","<<j<<" :\t";
      for(auto k: poly[i][j])
        cout<<k<<" ";
      cout<<endl;
    }
  }
}

int cnt = 0;

void check(int n, vector<int> &p)
{
  //cout<<"Check "<<n<<":\t";
  //for(auto k: p) cout<<k<<" ";cout<<endl;
  if(n == 0)
  {
    if(p[0] == 1) ans++;
    return;
  }

  int a = 0, b = 0;
  for(int j=0; j<=n; j++)
  {
    int jn = poly[n][j][n];
    if(jn > 0) a += jn;
    else b -= jn;
  }
  if(p[n] < -a || p[n] > b) return;

  for(int i=0; i<(2<<n); i++)
  {
    cnt++;
    vector<int> cur = p;
    for(int j=0; j<=n; j++)
    {
      if(i&(1<<j))
      {
        for(int k=0; k<=n; k++)
          cur[k] += poly[n][j][k];
      }
    }
    //for(auto k: cur) cout<<k<<",";cout<<endl;
    if(cur[n] != 0) continue;
    check(n-1, cur);
  }
}

int solve(int x)
{
  N = x;
  ans = 0;
  vector<int> p;
  for(int i=0; i<=N; i++)
    p.PB(0);
  cnt = 0;
  check(N, p);
  //cout<<"Cnt = "<<cnt<<endl;
  return ans;
}

int main(){
  FILEIO("immetric");
  init();

  cout<<"int ans[] = {";
  for(int i=1; i<=9; i++)
  {
    int ret = solve(i) - solve(i-1);
    cout<<ret<<",";
  }
  cout<<"};"<<endl;

	return 0;
}

