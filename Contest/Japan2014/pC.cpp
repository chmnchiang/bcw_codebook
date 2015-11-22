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

typedef pair<int, int> pii;
int N, M;
vector<pii> ip;
int main() {
	IOS;
	cin >> N >> M;

	for (int i=0; i<M; i++) {
		int a, b; cin >> a >> b;
		ip.PB({a, b});
	}
	sort(ALL(ip));

	int lst = 0, led = 0;
	int ans = 0;
	for (int i=0; i<M; i++) {
		int s, e;
		tie(s, e) = ip[i];
		if (s > led) {
			ans += (led - lst) * 2;
			ans += s - lst;
			lst = s; led = e;
		} else {
			led = max(led, e);
		}
	}
	ans += (led - lst) * 2;
	ans += N + 1 - lst;
	cout << ans << endl;
    return 0;
}
