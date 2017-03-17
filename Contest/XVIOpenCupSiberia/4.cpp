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



using ld = long double;
using ll = long long;

const int MAXN = 100005;
const ld INF = 1e20;

int N;
ll S[MAXN],X[MAXN];
ld P[MAXN],dp[MAXN];

int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;
	cin>>N;
	REP1(i,1,N) {
		cin>>S[i]>>X[i]>>P[i];
		P[i] = (1.0 + P[i] / 100.0);
	}
	REP1(i,1,N) {
		dp[i] = dp[i-1] + S[i] + X[i];
		ld cost = S[i] + X[i];
		ld m = 1;
		for (int j=i-1,lim=0; j>0 and lim<50; j--, lim++) {
			m *= P[j];
			cost += S[j] * m;
			dp[i] = min(dp[i], dp[j-1]+cost);
		}
	}
	cout<<fixed<<setprecision(10)<<dp[N]<<endl;


	return 0;
}

