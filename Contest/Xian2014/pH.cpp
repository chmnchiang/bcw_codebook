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

typedef pair<int,int> pii;
const int MXN = 105;

struct State {
	int x, y, t;
};

int N, M, bob, alice;
int dp[MXN][MXN][2], deg[MXN][MXN][2];
vector<int> E[MXN], rE[MXN];

queue<State> que;

void init() {
	while (!que.empty()) {
		que.pop();
	}
	for (int i=0; i<MXN; i++) {
		E[i].clear();
		rE[i].clear();
	}
	FMO(dp);
}
int main() {
	IOS;
	int nT;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		init();
		cin >> N >> M;
		for (int i=1, u, v; i<=M; i++) {
			cin >> u >> v;
			E[u].PB(v);
			rE[v].PB(u);
		}
		cin >> bob >> alice;
		for (int i=1; i<=N; i++) {
			for (int j=1; j<=N; j++) {
				deg[i][j][0] = E[i].size();
				deg[i][j][1] = E[j].size();
			}
		}
		for (int i=1; i<=N; i++) {
			dp[i][i][0] = dp[i][i][1] = 1;
			que.push({i,i,0});
			que.push({i,i,1});
			if (E[i].empty()) {
				for (int j=1; j<=N; j++) {
					dp[i][j][0] = 1;
					que.push({i,j,0});
				}
			}
		}
		while (!que.empty()) {
			State s = que.front();
			que.pop();
			int x = s.x;
			int y = s.y;
			int turn = s.t;
			if (turn == 0) {
				for (auto it : rE[y]) {
					if (dp[x][it][1] != 1) {
						dp[x][it][1] = 1;
						que.push({x,it,1});
					}
				}
			} else {
				for (auto it : rE[x]) {
					deg[it][y][0]--;
					if (!deg[it][y][0]) {
						if (dp[it][y][0] != 1) {
							dp[it][y][0] = 1;
							que.push({it,y,0});
						}
					}
				}
			}
		}

		int ok = dp[bob][alice][0] == 1 ? 0 : 1;
		cout << "Case #" << t << ": " << (ok ? "Yes" : "No") << "\n";
	}

	return 0;
}
