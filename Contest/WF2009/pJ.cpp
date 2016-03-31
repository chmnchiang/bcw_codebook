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
typedef pair<int,int> pii;
const int MXN = 105;

int N,K,dp[MXN][121];
vector<pii> E[MXN];

void DFS(int v, int f) {
	dp[v][0] = 0;
	REP1(i,1,120) dp[v][i] = INF;
	for (auto it:E[v]) {
		int u = it.F;
		int w = it.S;
		if (u == f) continue;
		DFS(u,v);
		REP1(i,0,120) dp[0][i] = INF;
		REP(_,2) {
			int alpha = w;
			if (_) alpha -= 60;

			REP1(av,0,120) {
				REP1(au,0,120) {
					int aup = max(au-alpha,0);
					if (aup <= 120 and dp[v][av] != INF and dp[u][au] != INF) {
						if (av + aup > K) {
							continue;
						}
						int bv = dp[v][av];
						int bup = max(dp[u][au]+alpha,0);
						if (bv + bup > K) {
							continue;
						}
						int x = max(av,aup);
						int y = max(bv,bup);
						dp[0][x] = min(dp[0][x],y);
					}
				}
			}
		}
		REP1(i,0,120) dp[v][i] = dp[0][i];
	}
}
int check_ok(int limit) {
	K = limit;
	DFS(1,1);
	REP1(i,0,120) if (dp[1][i] != INF) return 1; 
	return 0;
}
int main() {
	IOS;
	int cas = 0;
	while (cin >> N and N) {
		REP1(i,1,N) E[i].clear();
		REP1(i,1,N-1) {
			int u,v,t;
			cin >> u >> v >> t;
			t %= 60;
			E[u].PB({v,t});
			E[v].PB({u,t});
		}
		int l = 0, r = 121;
		while (l < r) {
			int m = (l + r) / 2;
			if (check_ok(m)) r = m;
			else l = m+1;
		}
		cas++;
		cout << "Case " << cas << ": ";
		cout << l << "\n";
	}

	return 0;
}


