#include <bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long LL;

const long long MOD = 1000000007;
const int MX = 1000005;

LL N, M, K;
LL inv[MX];

long long fast_pow(LL a, LL b) {
	if (!b) return 1;
	LL ret = fast_pow(a, b/2);
	ret = ret * ret % MOD;
	if (b&1) ret = ret * a % MOD;
	return ret;
}
long long f(long long x) {
	if (x == 0) return 0;
	return x * fast_pow(x-1, N-1) % MOD;
}

int main() {
	for (int i=1; i<MX; i++)
		inv[i] = fast_pow(i, MOD-2);
	int nT;
	cin >> nT;
	for (int t = 1; t <= nT; t++) {
		cin >> N >> M >> K;
		LL ans = 0;
		LL C = 1;
		for (int i=0; i<=K; i++) {
			LL tmp = f(i) * C % MOD;
			C = C * (K-i) % MOD * inv[i+1] % MOD;
			if ((K-i) % 2 == 0) {
				ans += tmp;
			} else {
				ans -= tmp;
			}
			ans = (ans + MOD) % MOD;
		}
		for (int i=1; i<=K; i++) {
			ans = ans * (M-i+1) % MOD;
			ans = ans * inv[i] % MOD;
		}
		cout << "Case #" << t << ": " << ans << "\n";
	}

	return 0;
}
