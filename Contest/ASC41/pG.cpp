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

const int MAXN = 1010;
const int MAXM = 11;

int N, M, U;
double p[MAXN][MAXM];
double avg[MAXM];
double lb[MAXM], rb[MAXM], rat[MAXM];
int type[MAXM];
vector<double> ps[MAXM];

double get_avg(int x, double l, double r)
{
  int cnt = 0;
  double ret = 0;
  for(int i=l*N; i<r*N; i++)
  {
    cnt++;
    ret += ps[x][i];
  }
  ret /= cnt;
  return ret;
}

int calc(int x)
{
  if(p[x][U] < lb[U] * 1.2) return 0;
  double a = 0, b = 0;
  for(int i=0; i<M; i++)
  {
    if(type[i] != 2) continue;
    a += rb[i];
    b += p[x][i];
  }
  double r = b / a;
  if(r < 0.33) return 2;
  else return 1;
}

int main(){
  FILEIO("genome");

  cin>>N>>M;
  for(int i=0; i<N; i++)
  {
    for(int j=0; j<M; j++)
    {
      cin>>p[i][j];
      avg[j] += p[i][j];
      ps[j].PB(p[i][j]);
    }
  }

  for(int i=0; i<M; i++)
  {
    avg[i] /= N;
    sort(ps[i].begin(), ps[i].end());
  }

  U = 0;
  for(int i=0; i<M; i++)
    if(avg[i] > avg[U])
      U = i;

  type[U] = 0;
  
  for(int i=0; i<M; i++)
  {
    lb[i] = get_avg(i, 0, 0.3);
    rb[i] = get_avg(i, 0.3, 1);
    rat[i] = rb[i] / lb[i];
    if(i==U)continue;
    if(rat[i] > 3) type[i] = 2;
    else type[i] = 1;
  }

  for(int i=0; i<N; i++)
  {
    cout<<calc(i)<<endl;
  }

	return 0;
}

