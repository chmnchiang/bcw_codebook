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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

#define int long long
const int MX = 333;
const int MT = 1111;
int V, M, T;
using pii=pair<int,int>;
pii E[MX][MX];
int dp[MX][MT];
pii bs[MX];
const int INF = 1029384756;

bool operator < (pii p1, pii p2) {
	return p1.S * p2.F < p1.F * p2.S;
}

int32_t main() {
	IOS;
	cin>>V>>M>>T;
	loop(i, 0, V) {
		bs[i] = pii{INF, 0};
	}
	loop(i, 0, M) {
		int u, v, a, b;
		cin>>u>>v>>a>>b;
		u--;
		v--;
		E[u][v] = E[v][u] = pii{a, b};
		if (bs[u] < pii{a, b}) bs[u] = pii{a, b};
		if (bs[v] < pii{a, b}) bs[v] = pii{a, b};
	}

	for (int i=0; i<V; i++) {
		for (int j=0; j<=T; j++) {
			dp[i][j] = -INF;
		}
	}

	dp[0][0] = 0;
	for (int t=1; t<=T; t++) {
		for (int v=0; v<V; v++) {
			for (int u=0; u<V; u++) {
				int d = E[u][v].F, c = E[u][v].S;
				if (!d and !c) continue;
				if (t - d < 0) continue;
				dp[v][t] = max(dp[v][t], dp[u][t-d] + c);
			}
		}
	}

	double ans = 0.0;
	for (int t=0; t<=T/2; t++) {
		for (int v=0; v<V; v++) {
			double q = 1.0*bs[v].S / bs[v].F * (T-t*2);
			ans = max(ans, q+2.0*dp[v][t]);
		}
	}

	cout << fixed << setprecision(10) << ans << endl;


	return 0;
}

