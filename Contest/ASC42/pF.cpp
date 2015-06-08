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

const int MX = 10000005;

int N, M;
int isp[MX],cnt[MX];
long long value[MX];

int main(){
  IOS;
  FILEIO("funny");
  fill(isp,isp+MX,1);
  fill(value,value+MX,0);
  isp[0] = isp[1] = 0;
  for (int i=2; i<MX; i++){
    if (isp[i]){
      for (int j=i; j<MX; j+=i){
        cnt[j] = cnt[j/i] + 1;
        value[j] += cnt[j];
        isp[j] = 0;
      }
      for (int j=i; j<MX; j+=i)
        cnt[j] = 0;
    }
  }
  while(cin >> N >> M and N and M) {
    if (value[N] > value[M]) cout << N << ' ' << M << " - Vera";
    else cout << N << ' ' << M << " - Harry";
    cout << endl;
  }
	return 0;
}

