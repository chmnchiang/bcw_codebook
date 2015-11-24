#include <bits/stdc++.h>
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

using namespace std;

const int MX = 514;
const int MOD = 1000000007;

int N, K, ip[MX];
int spj[MX];
int dp[MX][MX];

int main() {
	FILEIO("monotonic");
	cin >> N >> K;
	FZ(spj);
	for (int i=0, s=0; i<K; i++) {
		cin >> ip[i];
		s += ip[i];
		spj[s] = 1;
	}
	dp[0][0] = 1;
	for (int i=1; i<N; i++) {
		for (int j=0; j<=i; j++) {
			if (spj[i]) {
				for (int k=0; k<j; k++) {
					dp[i][j] += dp[i-1][k];
					if (dp[i][j] >= MOD) {
						dp[i][j] -= MOD;
					}
				}
			} else {
				for (int k=j; k<=i; k++) {
					dp[i][j] += dp[i-1][k];
					if (dp[i][j] >= MOD) {
						dp[i][j] -= MOD;
					}
				}
			}
		}
	}
	int ret = 0;
	for (int i=0; i<N; i++) {
		ret += dp[N-1][i];
		if (ret >= MOD) {
			ret -= MOD;
		}
	}
	cout << ret << endl;

	return 0;
}
