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
template<typename T, size_t N>
ostream& operator <<(ostream &s, const array<T, N> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!
#define int long long
using i3 = array<int, 3>;
const int INF = 1029384756;
int N, K;
vector<i3> ip;
const int MX = 1000;
int dp[2][MX][MX];

int32_t main() {
	IOS;
	cin>>N>>K;
	for (int i=0; i<N; i++) {
		int a, b, c;
		cin>>a>>b>>c;
		ip.PB(i3{b, a == 1 ? 3 : a-1, c});
	}

	sort(ALL(ip));

	for (int i=0; i<=2*K; i++) {
		for (int j=0; j<=K; j++) {
			dp[0][i][j] = INF;
		}
	}
	dp[0][0][0] = 0;

	for (int x=0; x<N; x++) {
		int he = x&1, my = he^1;
		int nt = ip[x][1];
		int myc = ip[x][2];

		for (int i=0; i<=2*K; i++)
			for (int j=0; j<=K; j++) dp[my][i][j] = dp[he][i][j];

		if (nt == 1 or nt == 2) {
			for (int i=1; i<=2*K; i++) {
				for (int j=0; j<=K; j++) {
					int z = i - j;
					if (j > z or (!z)) break; 
					dp[my][i][j] = min(dp[my][i][j], dp[he][i-1][j] + myc);
				}
			}
		}
		if (nt == 3 or nt == 2) {
			for (int i=1; i<=2*K; i++) {
				for (int j=1; j<=K; j++) {
					int z = i - j;
					if (j > z) break; 
					dp[my][i][j] = min(dp[my][i][j], dp[he][i-1][j-1] + myc);
				}
			}
		}

		/*
		for (int i=0; i<=2*K; i++) {
			for (int j=0; j<=K; j++) {
				cout << dp[my][i][j] << ' ';
			}
			cout << endl;
		}
		cout << "---" << endl;
		*/
	}

	cout << dp[N%2][2*K][K] << endl;


	return 0;
}

