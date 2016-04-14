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

const int INF = 1029384756;

int N,M,dis[20][20];
int A;
int ans,used[20];
int dp[20][20][(1<<20)+1];
int rd[20][20];
int d[13][20];
vector<int> pt[13];

int counter = 0;
void build_edge(vector<int> v1, int k1, vector<int> v2, int k2) {
	REP(i,N) {
		REP(j,N) rd[i][j] = INF;
	}
	REP(i,N) {
		rd[0][i] = rd[i][0] = dis[0][i];
		rd[N-1][i] = rd[i][N-1] = dis[N-1][i];
	}

	for (auto a:v1)
		for (auto b:v2)
			rd[a][b] = dis[a][b];
	for (auto a:v1)
		for (auto b:v1)
			rd[a][b] = dp[a][b][k1];
	for (auto a:v2)
		for (auto b:v2)
			rd[a][b] = dp[a][b][k2];

	pt[0] = pt[10] = {0};
	pt[1] = pt[2] = pt[6] = pt[7] = v1;
	pt[3] = pt[4] = pt[8] = pt[9] = v2;
	pt[5] = {N-1};
}
int calc() {
	REP(i,11) REP(j,N) d[i][j] = INF;
	d[0][0] = 0;
	REP(i,10) {
		for (auto a:pt[i]) {
			for (auto b:pt[i+1]) {
				d[i+1][b] = min(d[i+1][b], d[i][a] + rd[a][b]);
			}
		}
	}
	return d[10][0];
}
void DFS(int pos, int tot) {
	if (tot == A) {
		counter++;
		vector<int> v1;
		vector<int> v2;
		int k1,k2;
		k1 = k2 = 0;
		REP1(i,1,N-2) {
			if (used[i]) {
				v1.PB(i);
				k1 |= 1<<i;
			} else {
				v2.PB(i);
				k2 |= 1<<i;
			}
		}

		build_edge(v1,k1,v2,k2);
		ans = min(ans,calc());


		return;
	}
	if (N-1-pos+tot<A) return;

	used[pos] = 0;
	DFS(pos+1,tot);
	used[pos] = 1;
	DFS(pos+1,tot+1);
	used[pos] = 0;
}
int main() {
	IOS;
	int cas = 0;
	while (cin >> N >> M) {
		REP(i,N) {
			REP(j,N) dis[i][j] = INF;
			dis[i][i] = 0;
		}
		REP(i,M) {
			int u,v,t;
			cin >> u >> v >> t;
			dis[u][v] = dis[v][u] = min(dis[u][v],t);
		}
		REP(k,N) REP(i,N) REP(j,N)
			dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);

/*
		REP(i,N) REP(j,N) REP(k,1<<N)
			dp[i][j][k] = INF;
		REP(i,N) dp[i][i][1<<i] = 0;
*/

		A = (N - 2) / 2;
		REP(k,1<<N) {
			if (!k or (k & 1) or (k & (1<<(N-1)))) continue;
			if (__builtin_popcount(k) > max(A,N-2-A)) {
				continue;
			}
			vector<int> vec;
			REP(i,N) {
				if (k & (1 << i))
					vec.PB(i);
			}

			if (SZ(vec) == 1) {
				dp[vec[0]][vec[0]][k] = 0;
				continue;
			}
			for (auto i:vec) {
				for (auto j:vec) {
					int &res = dp[i][j][k];
					res = INF;
					if (i == j) continue;
					for (auto from:vec) {
						if (from == j) continue;
						res = min(res, dp[i][from][k-(1<<j)]+dis[from][j]);
					}
				}
			}
		}


		REP(i,N) used[i] = 0;
		ans = INF;
		DFS(1,0);
		if (N == 3) {
			ans = dis[0][1] + dis[1][2] + dis[2][1] + dis[1][0];
		}
		assert(ans != INF);
		cas++;
		cout << "Case " << cas << ": " << ans << "\n";
	}

	return 0;
}

