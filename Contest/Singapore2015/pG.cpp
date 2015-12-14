#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

typedef long long LL;
const int MXN = 3005;
const int INF = 1029384756;

int N;
LL ip[MXN], dp[MXN][MXN], sum[MXN], mx[MXN][MXN];

LL f(int l, int r) {
	if (l == 0) return sum[r];
	return sum[r] - sum[l-1];
}

int main() {
	IOS;
	while (cin >> N) {
		for (int i=1; i<=N; i++) {
			cin >> ip[i];
		}
		reverse(ip+1, ip+1+N);
		sum[0] = 0;
		for (int i=1; i<=N; i++) {
//			cout << ip[i] << " ";
			sum[i] = sum[i-1] + ip[i];
		}
//		cout << endl;
		memset(mx, 0, sizeof(mx));
		dp[1][1] = 1;
		mx[1][1] = 1;
		for (int i=2; i<=N; i++) {
			mx[0][i] = 0;
			dp[1][i] = 1;
			for (int j=2, k=0; j<=i; j++) {
				while (k+1<j && f(k+1, j-1) >= f(j, i)) k++;

				dp[j][i] = -INF;
				/*
				for (k=1; k<j; k++) {
					if (f(k, j-1) >= f(j, i)) {
						dp[j][i] = max(dp[j][i], dp[k][j-1] + 1);
					}
				}
				*/
				if (f(k, j-1) >= f(j, i)) {
					dp[j][i] = mx[k][j-1]+1;
				}
				/*
				cout << "DP(" << j << "," << i << ") = " << dp[j][i] << endl;
				cout << "K = " << k << endl;
				*/
			}
			for (int j=1; j<=i; j++) {
				mx[j][i] = max(mx[j-1][i], dp[j][i]);
			}
		}
		LL ans = 0;
		for (int i=1; i<=N; i++)
			ans = max(ans, dp[i][N]);
		cout << ans << endl;
	}

	return 0;
}

