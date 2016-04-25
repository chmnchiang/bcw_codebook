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

#define int long long
typedef pair<int, int> pii;
const int MX = 201010;
const int INF = 102938485723342;
int N, D, P;
vector<pii> ip;
int dp1[MX];
double dp2[MX];

int32_t main() {
	IOS;
	cin>>N>>D>>P;
	ip.resize(N);
	for (int i=0; i<N; i++) {
		cin>>ip[i].F>>ip[i].S;
	}
	for (int i=1; i<=D*2; i++) dp1[i] = INF;

	for (int i=1; i<=D*2; i++) {
		for (int j=0; j<N; j++) {
			int c=ip[j].F, cps=ip[j].S;
			if (i-cps < 0) continue;
			dp1[i] = min(dp1[i], dp1[i-cps]+c);
		}
	}

	for (int i=0; i<=D*2; i++) {
		dp2[i] = INF;
	}

	for (int i=1; i<=D; i++) {
		if (dp1[i] > P) continue;
		dp2[i] = 0;

		int rem = P - dp1[i];
		for (int j=0; j<N; j++) {
			int c=ip[j].F, cps=ip[j].S;
			int ned = max(c - rem, 0LL);
			double nedt = 1.0 * ned / i;
			int afcps = cps + i;
			dp2[afcps] = min(dp2[afcps], nedt);
		}
	}
	//for (int i=0; i<D*2; i++) cout << dp2[i] << ' '; cout << endl;

	for (int i=1; i<=D; i++) {
		for (auto p: ip) {
			int c = p.F, cps = p.S;
			double ndt = 1.0*c / i;
			dp2[cps+i] = min(dp2[cps+i], dp2[i] + ndt);
		}
	}
	//for (int i=0; i<D*2; i++) cout << dp2[i] << ' '; cout << endl;
	double ans = INF;
	for (int i=D; i<=D*2; i++) {
		ans = min(ans, dp2[i]);
	}
	
	cout << fixed << setprecision(10) << ans << endl;


	return 0;
}

