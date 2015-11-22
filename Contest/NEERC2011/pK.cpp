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

typedef pair<int,int> pii;
const int MXN = 100005;

int N, lastLeaf, cnt, bye, two, dfn[MXN];
vector<int> E[MXN];
vector<int> match[MXN];
vector<pii> ans;

void DFS(int u, int f, int step) {
	dfn[u] = step;
	if (SZ(E[u]) == 1) {
		cnt++;
		if (cnt == 1) {
			// pass
		} else if (cnt == 2) {
			match[u].PB(lastLeaf);
			match[lastLeaf].PB(u);
		} else if (cnt & 1) {
			two = lastLeaf;
			match[u].PB(lastLeaf);
			match[lastLeaf].PB(u);
		} else {
			int a = match[two][0];
			int b = match[two][1];
			int c = two;
			match[a].clear();
			match[b].clear();
			match[c].clear();
			match[a].PB(b);
			match[b].PB(a);
			match[c].PB(u);
			match[u].PB(c);
		}
		lastLeaf = u;
	}
	for (auto v : E[u]) {
		if (v == f) continue;
		DFS(v, u, step+1);
	}
}

int main() {
	FILEIO("kingdom");
	cin >> N;
	int rt = 1;
	for (int i=0, u, v; i<N-1; i++) {
		cin >> u >> v;
		E[u].PB(v);
		E[v].PB(u);
		if (SZ(E[u]) > 1) rt = u;
		if (SZ(E[v]) > 1) rt = v;
	}
	DFS(rt, rt, 1);
	int c = cnt / 2 + cnt % 2;
	int x = 0;
	cout << c << endl;
	for (int i=1; i<=N; i++) {
		if (!match[i].empty()) {
			for (auto it : match[i]) {
				if (it < i) {
					cout << i << " " << it << "\n";
					x++;
				}
			}
		}
	}
	assert(x == c);

	return 0;
}
