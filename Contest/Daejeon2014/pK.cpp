#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
  return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

#define int long long
const int MX = 10101;
int mem[MX][40];
bool us[MX][40];
int T;
int N;
int bus[MX], train[MX];

void init() {
	for (int i=0; i<=N; i++) {
		for (int j=0; j<40; j++)
			us[i][j] = 0;
	}
}

const int INF = 1029384756102938;
int dp(int n, int k) {
	if (n < 0)
		return 0;
	if (us[n][k]) {
		return mem[n][k];
	}

	us[n][k] = true;
	int ans = INF;

	ans = min(ans, dp(n-1, max(0ll, k-1)) + bus[n] + train[n]*2);
	ans = min(ans, dp(n-1, max(0ll, k-1)) + 6);
	ans = min(ans, dp(n-7, max(0ll, k-7)) + 36);
	ans = min(ans, dp(n-30, max(0ll, k-30)) + 90);

	if (k < 1)
		ans = min(ans, dp(n, 1) + 3);
	if (k < 7)
		ans = min(ans, dp(n, 7) + 18);
	if (k < 30)
		ans = min(ans, dp(n, 30) + 45);
	
	if (k) {
		ans = min(ans, dp(n-1, k-1) + train[n]*2);
	}

	return (mem[n][k] = ans);
}

int32_t main() {

	IOS;
	cin >> T;
	while (T--) {
		cin >> N;
		init();
		for (int i=0; i<N; i++) {
			cin >> bus[i] >> train[i];
		}

		cout << dp(N-1, 0) << endl;
	}
    return 0;
}

