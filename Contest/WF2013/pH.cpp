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

const int MXN = 514;
const int INF = 1029384756;

int N,ip[MXN],isunq[MXN][MXN],app[MXN];
int ok[MXN][MXN],dp[MXN];
int cost[MXN][MXN];
vector<int> vec[MXN][MXN];

inline int merge(int l1, int r1, int l2, int r2) {
	int x = max(vec[l1][r1][0], vec[l2][r2][0]);
//	int res = cost[l1][r1] + cost[l2][r2];
	int res = 0;
	res += end(vec[l1][r1]) - lower_bound(ALL(vec[l1][r1]),x);
	res += end(vec[l2][r2]) - lower_bound(ALL(vec[l2][r2]),x);
	//cout << "MERGE " << vec[l1][r1] << " " << vec[l2][r2] << " " << res << endl;
	return res;
}
int main() {
	IOS;
	cin >> N;
	REP(i,N) cin >> ip[i];
	REP(l,N) {
		REP1(r,l,N-1) {
			vec[l][r].clear();
			isunq[l][r] = 1;
			REP1(m,l,r) {
				vec[l][r].PB(ip[m]);
				if (app[ip[m]]) {
					isunq[l][r] = 0;
				}
				app[ip[m]] = 1;
			}
			sort(ALL(vec[l][r]));
			REP1(m,l,r) {
				app[ip[m]] = 0;
			}
		}
	}
	

	REP(l,N) {
		int mx = 0;
		REP1(r,l,N-1) {
			ok[l][r] = 0;
			mx = max(mx, ip[r]);
			if (mx == r-l+1 and isunq[l][r]) ok[l][r] = 1;
		}
	}

	REP(i,N) {
		REP(j,N) cost[i][j] = INF;
		cost[i][i] = 0;
	}
	REP(r,N) {
		for (int l=r-1; l>=0; l--) {
			if (!isunq[l][r]) continue;
		//	cout << l << " " << r << endl;
			REP1(m,l,r-1) {
				if (cost[l][m] == INF or cost[m+1][r] == INF) continue;
				cost[l][r] = min(cost[l][r], merge(l,m,m+1,r) + cost[l][m] + cost[m+1][r]);
			}
		}
	}
/*
	REP(l,N) REP(r,N)
		if (ok[l][r]) cout << "OK " << l << " " << r << " " << cost[l][r] << endl;
*/
	REP(i,N) dp[i]= INF;
	dp[N] = 0;
	for (int i=N-1; i>=0; i--) {
		REP1(j,i,N-1) {
			if (ok[i][j]) dp[i] = min(dp[i], cost[i][j] + dp[j+1]);
		}
	}

	if (dp[0] == INF) cout << "impossible" << endl;
	else cout << dp[0] << endl;


	return 0;
}

