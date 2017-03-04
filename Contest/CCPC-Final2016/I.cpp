#pragma GCC optimize ("O2")
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

using pii = pair<int,int>;
const int MX = 10005;
const int MXN = 205;
const int INF = 1029384756;

struct Rule {
	int goal;
	vector<pii> vec;
} rule[MXN];

int M,N,K;
int cost[MXN];
int dp[MX];
// .F = price, .S = cost of magic
pii AcThPaU[MXN];

void input() {
	cin>>M>>N>>K;
	REP1(i,1,N) {
		int can;
		cin>>can;
		if (!can) {
			cin>>AcThPaU[i].F;
			AcThPaU[i].S = INF;
		} else {
			cin>>AcThPaU[i].S>>AcThPaU[i].F;
		}
	}
	REP1(i,1,K) {
		int m;
		cin>>rule[i].goal>>m;
		rule[i].vec.resize(m);
		REP(j,m) cin>>rule[i].vec[j].F>>rule[i].vec[j].S;
	}
}
int solve() {
	REP1(i,1,N) {
		cost[i] = AcThPaU[i].S;
	}
	REP(_,N+2) {
		REP1(i,1,K) {
			int e = rule[i].goal;
			int tmp = 0;
			for (auto it:rule[i].vec)
				tmp += 1LL * it.S * cost[it.F];
			cost[e] = min(cost[e], tmp);
		}
	}

//	REP1(i,1,N) cout<<i<<" "<<cost[i]<<endl;

	FZ(dp);
	REP1(j,1,N) {
		int w = cost[j];
		int v = AcThPaU[j].F;
		REP1(i,w,M) {
			dp[i] = max(dp[i], dp[i-w]+v);
		}
	}

	return dp[M];
}
int32_t main() {
	IOS;
	int nT;
	cin>>nT;
	REP1(cas,1,nT) {
		input();
		int ans = solve();
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}

	return 0;
}

