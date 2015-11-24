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

typedef pair<int,int> pii;

const int LOG = 19;
const int MXN = 200005;

int N;
int fa[MXN][LOG], nPop[MXN], cnt[MXN], num[MXN];

int up(int v, int step) {
	int i=0;
	while (step) {
		if (step & 1) {
			v = fa[v][i];
		}
		step >>= 1;
		i++;
	}
	return v;
}
int main() {
	FILEIO("queue");
	IOS;
	cin >> N;
	for (int i=1, cmd; i<=N; i++) {
		cin >> cmd;
		if (cmd == 1) {
			int v, x;
			cin >> v >> x;
			fa[i][0] = v;
			for (int j=1; j<LOG; j++) {
				fa[i][j] = fa[fa[i][j-1]][j-1];
			}
			nPop[i] = nPop[v];
			cnt[i] = cnt[v] + 1;
			num[i] = x;
		} else {
			int v;
			cin >> v;
			for (int j=0; j<LOG; j++) {
				fa[i][j] = fa[v][j];
			}
			nPop[i] = nPop[v] + 1;
			cnt[i] = cnt[v];
			num[i] = num[v];

			int id = up(i, cnt[i] - nPop[i]);
			cout << num[id] << "\n";
		}
	}

	return 0;
}
