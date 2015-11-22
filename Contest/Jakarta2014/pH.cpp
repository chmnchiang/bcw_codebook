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

const int MX = 2005;
int N, M, K;
int dp[MX][MX], sum[MX];
string cmd;

void input() {
	cin >> N >> M >> K;
	cin >> cmd;
}

int count1(int l, int r) {
	l = max(l, 0);
	if (l <= 0) return sum[r];
	return sum[r] - sum[l-1];
}
int count0(int l, int r) {
	l = max(l, 0);
	return (r-l+1) - count1(l, r);
}
void build(int a[]) {
	sum[0] = a[0];
	for (int i=1; i<=M; i++) {
		sum[i] = sum[i-1] + a[i];
	}
}

char win(char ch) {
	return ch;
}
char lose(char ch) {
	if (ch == 'A') return 'B';
	else return 'A';
}

void solve() {
	N *= 2;
	for (int i=0; i<=N; i++) {
		for (int j=0; j<=M; j++) {
			dp[i][j] = 0;
		}
	}
	for (int j=1; j<=K; j++)
		dp[N-1][j] = 1;
	for (int i=N-2; i>=0; i--) {
		dp[i][0] = 0;
		build(dp[i+1]);
		for (int j=1; j<=K; j++)
			dp[i][j] = 1;
		for (int j=K+1; j<=M; j++) {
			dp[i][j] = 0;
			if (cmd[i] == cmd[i+1]) {
				if (count1(j-K, j-1)) {
					dp[i][j] = 1;
				}
			} else {
				if (count0(j-K, j-1)) {
					dp[i][j] = 1;
				}
			}
		}
	}
	if (dp[0][M]) cout << win(cmd[0]) << endl;
	else cout << lose(cmd[0]) << endl;
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		input();
		cout << "Case #" << t << ": ";
		solve();
	}

	return 0;
}

