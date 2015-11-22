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

typedef unsigned long long ull;

const int MX = 70;

int ip[MX];
ull mem[MX][MX][MX][2];
bool us[MX][MX][MX][2];
int nowM;

ull dp(int n, int m, int k, bool fg) {
	//cout << n << ' ' << m << ' ' << k << ' ' << fg << endl;
	if (us[n][m][k][fg]) return mem[n][m][k][fg];

	if (n == 64) {
		return (m == 0 and k == nowM) ? 1 : 0;
	}
	us[n][m][k][fg] = true;
	ull a = 0;
	if (fg or ip[n] == 1) {
		a += dp(n+1, (m*2+1)%nowM, k+1, fg);
	} 
	a += dp(n+1, (m*2)%nowM, k, (fg or ip[n] == 1));
	return mem[n][m][k][fg] = a;
}

int main() {
	
	IOS;
	ull N;
	cin >> N;
	for (int i=63; i>=0; i--) {
		ip[i] = N&1ull;
		N >>= 1;
	}
	

	ull ans=0;
	for(int i=1; i<=64; i++) {
		memset(us, false, sizeof(us));
		nowM = i;
		ans += dp(0, 0, 0, false);
		//cout << ans << endl;
	}
	cout << ans << endl;
	return 0;
}

