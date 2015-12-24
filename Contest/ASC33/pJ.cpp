#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!
//

typedef long long i64;
const i64 M = 1000000000;
const int MAXV = 123;
int V;
vector<int> el[MAXV];
i64 dp[MAXV][MAXV][2];

void aozora(){
	for(int i=0; i<=V+2; i++){
		el[i].clear();
	}

}

void meteor(int v, int fa){


	dp[v][1][1] = 1;
	dp[v][0][0] = 1;
	for(auto u: el[v]){

		if(u == fa) continue;

		meteor(u, v);

		for(int i=V; i>=0; i--){
			i64 t = 0;
			for(int j=0; j<=i; j++){
				t += (dp[u][j][0] + dp[u][j][1]) *
							dp[v][i-j][0];
				t %= M;
			}

			dp[v][i][0] = t;
		}

		for(int i=V; i>=0; i--){
			i64 t = 0;
			for(int j=0; j<=i; j++){
				t += (dp[u][j][0] + dp[u][j][1]) *
							dp[v][i-j][1];
				t %= M;
				if(j){
					t += (dp[u][j][1]) * dp[v][i - j + 1][1];
					t %= M;
				}
			}

			dp[v][i][1] = t;
		}
	}
}


int main(){
	FILEIO("subtrees");

	IOS;

	cin >> V;

	aozora();

	for(int i=0; i<V-1; i++){
		int u, v;
		cin >> u >> v;

		el[u].push_back(v);
		el[v].push_back(u);

	}

	int roo = 1;

	meteor(roo, -1);

	for(int i=1; i<=V; i++){
		cout << (dp[roo][i][0] + dp[roo][i][1]) % M << endl;
	}

	return 0;
}

