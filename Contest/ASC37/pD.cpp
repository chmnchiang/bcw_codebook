#include <bits/stdc++.h>
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
	freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

using namespace std;

const int MX = 202;

vector<int> vl[MX];
int ans[MX];

int main() {
	IOS;
	FILEIO("bubble");
	int N; cin >> N; 
	for (int i=1; i<N; i++) {
		for (int j=0; j<i; j++) {
			int a; cin >> a; vl[i-1].PB(a);
		}
	}

	for (int i=0; i<N; i++) {
		ans[i] = i+1;
	}

	bool fg = true;
	for (int i=1; i<N; i++) {
		int st = N-i-1;
		for (int j=st; j<N-1; j++) {
			//cout << j << endl;
			int f = vl[j].back();
			vl[j].pop_back();
			int u = j, v = j+1;
			if (f == 1) {
				if (ans[u] > ans[v]) {
					fg = false; break;
				}
				swap(ans[u], ans[v]);
			} else {
				if (ans[u] > ans[v]) {
					fg = false; break;
				}
			}
		}
		if (not fg) break;
	}

	if (not fg) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		for (int i=0; i<N; i++) {
			cout << ans[i] << (i == N-1 ? "\n" : " ");
		}
	}
	return 0;
}
