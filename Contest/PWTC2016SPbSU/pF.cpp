#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

typedef long long ll;
const ll INF = 1LL<<60;

int N,K,W,col[401][401],cost[401][401];
ll dp[2][401][1024];
bitset<1024> prv[401][401];

int main() {
	IOS;
	cin >> N >> K >> W;
	REP(i,N) REP(j,N)
		cin >> cost[i][j];
	REP(i,N) REP(j,N) {
		cin >> col[i][j];
		col[i][j]--;
	}
	REP(i,2) REP(j,N) REP(k,(1<<K))
		dp[i][j][k] = INF;
	int u = 0;
	REP(k,(1<<K)) {
		int nk = k | (1 << col[0][0]);
		dp[u][0][nk] = cost[0][0];
	}
	
	REP(i,N) {
		REP(j,N) REP(k,(1<<K))
			dp[u^1][j][k] = INF;
		REP(j,N) {
			REP(k,(1<<K)) {
				int x,y,nk;
				x = i+1;
				y = j;
				nk = k | (1<<col[x][y]);
				if (dp[u^1][y][nk] > dp[u][j][k] + cost[x][y]) {
					dp[u^1][y][nk] = dp[u][j][k] + cost[x][y];
					prv[x][y][nk] = 0;
				}

				x = i;
				y = j+1;
				nk = k | (1<<col[x][y]);
				if (dp[u][y][nk] > dp[u][j][k] + cost[x][y]) {
					dp[u][y][nk] = dp[u][j][k] + cost[x][y];
					prv[x][y][nk] = 1;
				}
			}
		}
		u ^= 1;
	}

	int nc = 1029384756;
	int bk = -1;
	u ^= 1;
	REP(k,(1<<K)) {
		if (dp[u][N-1][k] <= W) {
			if (__builtin_popcount(k) < nc) {
				nc = __builtin_popcount(k);
				bk = k;
			}
		}
	}
	if (bk == -1) {
		cout << -1 << endl;
	} else {
		cout << nc << endl;
		vector<int> ans;
		int x = N-1, y=N-1;
		while (x >= 0 and y >= 0) {
			ans.PB(y+1);
			ans.PB(x+1);
			if (prv[x][y][bk] == 0) {
				x--;
			} else {
				y--;
			}
		}
		reverse(ALL(ans));
		for (auto it:ans) cout << it << " ";
		cout << endl;

		int pos = 0;
		ll totW = 0;
		int c = 0;
		while (pos < SZ(ans)) {
			int nx = ans[pos++]-1;
			int ny = ans[pos++]-1;
			totW += cost[nx][ny];
			c |= 1 << col[nx][ny];
		}
		assert(totW <= W);
		assert(__builtin_popcount(c) == nc);
	}

	return 0;
}
