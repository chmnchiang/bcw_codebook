#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long i64;
const int MX = 300;
const int MOD = 1000000007;
int FG;
int N, M, K;
int trans[MX][MX];

void init() {
	FG = (1<<M) - 1;
}

void make_trans() {
	for (int i=0; i<(1<<M); i++) {
		for (int j=0; j<(1<<M); j++) {
			int ip = i, jp = j;
			int a = 0, t = FG;
			for (int k=0; k<M; k++) {
				t &= jp;
				a |= (t & ip);
				ip >>= 1; jp >>= 1;
			}
			trans[i][j] = a;
		}
	}
}

i64 dp[10][70][MX];
void make_dp() {
	for (int i=0; i<=N; i++) {
		for (int j=0; j<=K; j++) {
			for (int k=0; k<=(1<<M); k++) {
				dp[i][j][k] = 0;
			}
		}
	}
	dp[0][0][1<<(M-1)] = 1;
	for (int i=0; i<N; i++) {
		for (int p=0; p<(1<<M); p++) {
			for (int j=0; j<(1<<M); j++) {
				int dk = M -  __builtin_popcount(j);
				for (int k=0; k<=K-dk; k++) {
					dp[i+1][k+dk][trans[p][j]] += dp[i][k][p];
					dp[i+1][k+dk][trans[p][j]] %= MOD;
				}
			}
		}
	}
}

int main() {
	IOS;
	int T; cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cin >> N >> M >> K;
		init();
		make_trans();
		make_dp();
		i64 ans = 0;

		for (int k=0; k<=K; k++) {
			for (int j=0; j<(1<<(M-1)); j++) {
				int t = j << 1;
				ans = (ans + dp[N][k][t]) % MOD;
			}
		}
		cout << "Case #" << cas << ": " <<  ans << endl;
	}

    return 0;
}

