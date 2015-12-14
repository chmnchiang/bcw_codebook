#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

const int MM = 555555;
set<int> sets[MM];
int where[MM];

int main() {

	int N; cin >> N;
	int ans = 0;
	for (int i=1; i<=N; i++) {
		int m; cin >> m;
		set<int> ip;
		vector<int> ls;
		for (int j=0; j<m; j++) {
			int a; cin >> a;
			sets[i].insert(a);
			ip.insert(a);
			ls.PB(a);
		} 
		bool ok = true;
		for (int j=0; j<m; j++) {
			int t = ls[j];
			if (not ip.count(t))
				continue;
			if (where[t]) {
				int w = where[t];
				for (auto x: sets[w]) {
					if (not ip.count(x)) {
						ok = false;
						break;
					} else {
						ip.erase(x);
					}
				}
			}
			if (not ok) break;
		}
		if (ok) {
			ans ++;
			for (auto x: ls) {
				where[x] = i;
			}
		}
	}
	cout << ans << endl;

	return 0;
}

