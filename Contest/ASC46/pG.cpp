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

typedef long long i64;
const i64 MD = 242121643;
const int MX = 123;
int ip[MX];
i64 cdp[MX][MX];
bool us[MX][MX];

i64 C(int n, int m) {
	if(n == m) return 1;
	if(n < m) return 0;
	if(m == 0) return 1;
	if(m < 0) return 0;
	if(us[n][m]) return cdp[n][m];
	us[n][m] = 1;
	return (cdp[n][m] = (C(n-1, m) + C(n-1, m-1)) % MD);
}

int main(){
	FILEIO("game");
	int K, N;
	while(cin >> N >> K && (N && K)) {
		int ones = 0, others;
		for(int i=0; i<N; i++) {
			cin >> ip[i];
			if(ip[i] == 1) ones ++;
		}
		others = N - ones;
		i64 ans = 0;
		for(int i=1; i<=ones; i+=2) {
			//cout << ones << ' ' << C(ones, i) << endl;
			ans += ((C(ones, i) * C(others, K-i)) % MD);
			ans %= MD;
		}
		cout << ans << endl;
	}

	return 0;
}

