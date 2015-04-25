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

typedef long long LL;
const int MX = 5005;
const LL INF = 1ll<<60;

int N, ip[MX];
int a,b,c,m;
int prv[MX][MX];
LL dp[MX][MX];

inline int d(int i, int j){
	return (a*i + b*j + c*(i^j)) % m;
}

int main(){
	FILEIO("elegant");
	while (~scanf("%d", &N) && N){
		scanf("%d%d%d%d", &a, &b, &c, &m);
		for (int i=0; i<N; i++)
			fill(dp[i],dp[i]+N,INF);
		for (int i=0; i<N; i++)
			dp[0][i] = 0;
		for (int i=0; i<N-1; i++){
			for (int j=0; j<N; j++){
				int k = i + 1;
				int level = (k & (-k));
				int val = j ^ level;
				for (int cnt=0; cnt <level; cnt++){
					int num = val ^ cnt;
					if (dp[k][num] > dp[i][j] + d(j,num)){
						dp[k][num] = dp[i][j] + d(j,num);
						prv[k][num] = j;
					}
				}
			}
		}
		int best = 0;
		vector<int> ans;
		for (int i=0; i<N; i++)
			if (dp[N-1][best] > dp[N-1][i])
				best = i;
		printf("%I64d\n", dp[N-1][best]);
		for (int i=N-1; i>=0; i--){
			ans.PB(best);
			best = prv[i][best];
		}
		for (int i=N-1; i>=0; i--)
			printf("%d%c", ans[i], i == 0 ? '\n' : ' ');
	}
	return 0;
}

