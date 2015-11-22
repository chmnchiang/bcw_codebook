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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long i64;
const int MOD = 1000000007;
int main() {
	int N; cin >> N;
	i64 a[3] = {N, N-1, 3LL*N*N-N+2};

	for(int i=0; i<3; i++) {
		if (a[i] % 2 == 0) {
			a[i] /= 2;
			break;
		}
	}

	for(int i=0; i<3; i++) {
		if (a[i] % 3 == 0) {
			a[i] /= 3;
			break;
		}
	}

	for(int i=0; i<3; i++) a[i] %= MOD;

	i64 ans = (a[0] * a[1]) % MOD;
	ans = (ans * a[2]) % MOD;
	cout << ans << endl;
	return 0;
}

