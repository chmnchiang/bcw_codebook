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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

int N, M;
double ans;

int main() {
	FILEIO("ascii");
	cin >> N >> M;
	ans = 0;
	string str;
	for (int i=0; i<N; i++) {
		cin >> str;
		int c = 0;
		for (int j=0; j<M; j++) {
			if (c & 1) {
				ans += 0.5;
			}
			if (str[j] != '.') c++;
			if (c & 1) {
				ans += 0.5;
			}
		}
	}
	cout << ans << endl;

    return 0;
}
