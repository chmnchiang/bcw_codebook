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

const int INF = 1029384756;
const int MXN = 1005;

int N, K, E, seg[MXN];
int power[] = {0, 4, 8 ,11};
int dp[MXN][54][11][4];

void input() {
	cin >> N >> K >> E;
	for (int i=1; i<=N; i++) {
		cin >> seg[i];
	}
}

int f(int i, int e, int k, int t) {
	if (e > E) return INF;
	if (k > K) return INF;
	return dp[i][e][k][t];
}

void solve() {
	for (int i=0; i<=N; i++) {
		for (int e=0; e<=E; e++) {
			for (int k=0; k<=K; k++) {
				for (int t=0; t<4; t++) {
					dp[i][e][k][t] = INF;
				}
			}
		}
	}
	dp[0][E][K][0] = 0;
	for (int i=1; i<=N; i++) {
		for (int e = 0; e <= E; e++) {
			for (int k=0; k<=K; k++) {
				for (int t=0; t<4; t++) {
					int &ret = dp[i][e][k][t];
					for (int prv=0; prv<4; prv++) {
						if (prv == t) {
							ret = min(ret, f(i-1, e+t, k, prv) + max(0, seg[i]-power[t]));
						} else {
							ret = min(ret, f(i-1, e+t, k+1, prv) + max(0, seg[i]-power[t]));
						}
					}
					if (t == 0 && k == 0) {
						for (int prv=0; prv<4; prv++) {
							ret = min(ret, f(i-1, e, k, prv) + max(0, seg[i]-power[t]));
						}
					}
				}
			}
		}
	}
	int ans = INF;
	for (int e=0; e<=E; e++)
		for (int i=0; i<=K; i++)
			for (int t=0; t<4; t++)
				ans = min(ans, dp[N][e][i][t]);
	cout << ans << endl;
}

int main() {
	int nT;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		input();
		cout << "Case #" << t << ": ";
		solve();
	}

	return 0;
}

