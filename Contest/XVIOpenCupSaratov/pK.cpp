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
#define REP(i,n) for (int i=0;i<(n);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef pair<int,int> pii;
const int MXN = 5005;
const int INF = 1029384756;

struct Answer {
	int a1, t, x, y;
	void update(int a, int b, int c, int d) {
		if (tie(a1, t, x, y) > tie(a, b, c, d)) {
			tie(a1, t, x, y) = tie(a, b, c, d);
		}
	}
};

int N,K,S,dp[MXN];
pii dpxia[MXN][2];
pii maxd[MXN][3];
Answer ans;
vector<int> E[MXN];

void init() {
	REP(i,N) maxd[i][0] = maxd[i][1] = maxd[i][2] = {0,-1};
}
void DFS1(int u, int f) {
	dp[u] = 0;
	REP(i,2)
		dpxia[u][i] = {0,-1};
	for (auto v:E[u]) {
		if (v == f) continue;
		DFS1(v, u);
		pii p = {maxd[v][0].F + 1, v};
		if (p > maxd[u][0]) {
			maxd[u][2] = maxd[u][1];
			maxd[u][1] = maxd[u][0];
			maxd[u][0] = p;
		} else if (p > maxd[u][1]) {
			maxd[u][2] = maxd[u][1];
			maxd[u][1] = p;
		} else if (p > maxd[u][2]) {
			maxd[u][2] = p;
		}

		p = {dp[v], v};
		if (p > dpxia[u][0]) {
			dpxia[u][1] = dpxia[u][0];
			dpxia[u][0] = p;
		} else if (p > dpxia[u][1]) {
			dpxia[u][1] = p;
		}
		dp[u] = max(dp[u], dp[v]);
	}
	dp[u] = max(dp[u], maxd[u][0].F + maxd[u][1].F);
}
void DFS(int u, int f, int mx, int shang, int dep) {
	if (dep >= K) return;
	for (auto v:E[u]) {
		if (v == f) continue;
		pii x, y, tmpxia;
		x = y = tmpxia = {0, -1};
		REP(i,3) {
			if (maxd[u][i].S == v) continue;
			if (x.S == -1) x = maxd[u][i];
			else if (y.S == -1) y = maxd[u][i];
		}
		REP(i,2) {
			if (dpxia[u][i].S == v) continue;
			tmpxia = dpxia[u][i];
			break;
		}
		int vshang = shang;
		vshang = max(vshang, x.F + mx);
		vshang = max(vshang, x.F + y.F);
		vshang = max(vshang, tmpxia.F);
		int sz = max(mx, x.F);

		int xz = maxd[v][0].F;
		int xia = dp[v];
		
		int c = max(vshang, xia);
		c = max(c, sz + xz);
			
		ans.update(c, dep+1, S, v);

		DFS(v, u, sz, vshang, dep+1);
		
	}
}
void check(int st) {
	S = st;
	init();
	DFS1(st, st);
	ans.update(dp[st], 0, 0, 0);
	DFS(st, st, 0, 0, 0);
}
int main() {
	IOS;
	cin >> N >> K;
	REP(i,N-1) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
		E[v].PB(u);
	}
	ans.a1 = INF;
	REP(i,N) {
		check(i);
	}
	cout << ans.a1 << endl;
	cout << ans.t << endl;
	if (ans.t) cout << ans.x << " " << ans.y << endl;

    return 0;
}
