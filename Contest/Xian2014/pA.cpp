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

int main() {
	int nT, N;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		int ok = 1;
		cin >> N;
		for (int i=1, v; i<=N; i++) {
			cin >> v;
			if (v % 3) ok = 0;
		}
		cout << "Case #" << t << ": ";
		if (ok) cout << "Yes\n";
		else cout << "No\n";
	}

	return 0;
}
