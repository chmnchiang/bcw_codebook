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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MX = 305;
const int INF = 529384756;

int N,edge[MX][MX],dis[MX],prv[MX],done[MX],dep[MX];
int mem[MX][MX];

int lca(int x, int y) {
	if (x == y) return x;
	if (mem[x][y] != -1) return mem[x][y];
	if (dep[x] > dep[y]) swap(x, y);
	return mem[x][y] = mem[y][x] = lca(x, prv[y]);
}
void dijkstra(int s) {
	REP(i,N) {
		done[i] = 0;
		dis[i] = INF;
		prv[i] = i;
		dep[i] = INF;
		REP(j,N) mem[i][j] = -1;
	}
	dis[s] = 0;
	dep[s] = 0;
	REP(_,N) {
		int best = -1;
		REP(i,N) {
			if (done[i]) continue;
			if (best == -1 || dis[i] < dis[best])
				best = i;
		}
		if (best == -1) break;
		done[best] = 1;
		REP(i,N) {
			if (done[i]) continue;
			if (dis[i] > dis[best]+edge[best][i]) {
				dis[i] = dis[best]+edge[best][i];
				prv[i] = best;
				dep[i] = dep[best]+1;
			}
		}
	}
}
int solve(int st) {
	int ans = INF;
	FMO(mem);
	/*
	REP(i,N) {
		cout << dis[i] << " " << prv[i] << " " << dep[i] << endl;
	}
	*/
	REP(i,N) {
		REP(j,N) {
			if (i == j) continue;
			if (edge[i][j] == INF) continue;
			if (prv[i] == j || prv[j] == i) continue;
			if (dis[i] == INF or dis[j] == INF) continue;
//			cout << "LCA " << pair<int,int>(i,j) << " = " << lca(i,j) << endl;
			if (lca(i, j) == st) {
				ans = min(ans, dis[i]+dis[j]+edge[i][j]);
			}
		}
	}
	if (ans == INF) ans = -1;
	return ans;
}
int main() {
	IOS;
	cin >> N;
	REP(i,N) {
		REP(j,N) {
			cin >> edge[i][j];
			if (edge[i][j] == -1) edge[i][j] = INF;
		}
	}
	REP(st,N) {
		dijkstra(st);
		cout << solve(st) << endl;
	}

	return 0;
}

