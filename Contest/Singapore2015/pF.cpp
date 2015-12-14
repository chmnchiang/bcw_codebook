#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

typedef pair<int,int> pii;
const int MXN = 105;

int N;
pii ip[MXN];

bool comp(pii a, pii b) {
	return a.S < b.S;
}

int main() {
	IOS;
	while (cin >> N) {
		for (int i=0; i<N; i++)
			cin >> ip[i].F >> ip[i].S;
		sort(ip, ip+N, comp);
		int ans = 0;
		for (int i=0, r=-1; i<N; i++) {
			if (!(ip[i].F <= r && r <= ip[i].S)) {
				ans++;
				r = max(r, ip[i].S);
			}
		}
		cout << ans << endl;
	}

	return 0;
}

