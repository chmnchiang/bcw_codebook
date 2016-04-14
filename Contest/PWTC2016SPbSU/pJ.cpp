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
const int MX = 3333;
const int MD = 1000000007;
struct BIT {
	int val[MX];
	void init() {
		FZ(val);
	}
	int lb(int a) {
		return a&(-a);
	}
	int qry(int a) {
		a+=2;
		int res=0;
		for (int x=a; x; x-=lb(x)) {
			res=(res+val[x])%MD;
		}
		return res;
	}

	void add(int a, int v) {
		a+=2;
		for (int x=a; x<MX; x+=lb(x)) {
			val[x]=(val[x]+v)%MD;
		}
	}
} bit;
int N;
int ip[MX];
int dp[MX][MX];
int G[MX];

int pow(int a, int b) {
	if (!b) return 1%MD;
	int t = pow(a*a%MD, b/2);
	if (b&1) t = (t*a)%MD;
	return t;
}

int mem[MX][MX];
int us[MX][MX];
int C(int n, int m) {
	if (m == n or m == 0) return 1;
	if (m > n or m < 0) return 0;
	if (us[n][m]) return mem[n][m];
	us[n][m] = 1;

	return (mem[n][m] = (C(n-1, m) + C(n-1, m-1)) % MD);
}

void pre() {
	G[0] = 0;
	for (int i=1; i<=N; i++) {
		G[i] = pow(i, N); 
		//cout << i << ' ' << G[i] << endl;
		for (int j=i-1, k=-1; j>=0; j--) {
			int t = G[j] * C(i, j) * k % MD;
			t = (t+MD)%MD;
			G[i] += t;
			G[i] %= MD;
		}
	}
}

int32_t main() {
	IOS;

	cin>>N;
	for (int i=1; i<=N; i++) {
		cin>>ip[i];
	}
	pre();
	dp[0][0] = 1;
	for (int j=1; j<=N; j++) {
		bit.init();
		if (j == 1) {
			bit.add(0, 1);
		}
		for (int i=1; i<=N; i++) {
			int t = bit.qry(ip[i]-1);
			dp[j][i] = t;
			bit.add(ip[i], dp[j-1][i]);
		}
	}
	
	int ans = 0;
	for (int i=1; i<=N; i++) {
		int t = 0;
		for (int j=1; j<=N; j++) {
			t += dp[i][j];
			t %= MD;
		}


	//	cout << t << ' ' << G[i] << endl;
		ans += t * G[i];
		ans %= MD;
	}
	cout << ans << endl;

	return 0;
}

