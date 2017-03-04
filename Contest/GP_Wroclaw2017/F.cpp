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
const int MX = 5011;
int N;
short fl[MX][MX];
#define fr fl
int ip[MX];
const int MD = 1000000007;

void build() {
	for (int i=0; i<N; i++) {
		fl[i][i+1] = ip[i] == 0 ? i : -1;

		for (int j=i+2; j<=N; j++) {
			int jj = j-1;
			fl[i][j] = fl[i][j-1];
			if (fl[i][j] != -1 and ip[jj] == j-i-1) {
				fl[i][j] = jj;
			}
		}
	}

	for (int i=N; i>=1; i--) {
		fr[i][i-1] = ip[i-1] == 0 ? i-1 : -1;

		for (int j=i-2; j>=0; j--) {
			fr[i][j] = fr[i][j+1];
			if (fr[i][j] != -1 and ip[j] == i-j-1) {
				fr[i][j] = j;
			}
		}
	}
}

int _C[MX][MX];
bool _us[MX][MX];

int C(int n, int m) {
	if (n == m or m == 0) return 1;
	if (m > n or m < 0) return 0;

	if (_us[n][m]) return _C[n][m];
	_us[n][m] = 1;
	return _C[n][m] = (C(n-1, m) + C(n-1, m-1)) % MD;
}


int mem[MX][MX];
bool us[MX][MX];
bool hao[MX][MX];
int dp(int l, int r);

inline int conv(int l, int pv, int r) {
	int res = (dp(l, pv) * dp(pv+1, r)) % MD * C(r-l-1, pv-l) % MD;
	hao[l][r] |= hao[l][pv] && hao[pv+1][r];
	return res;
}

int dp(int l, int r) {
	if (l == r) {
		hao[l][r] = 1;
		return 1;
	}
	if (r == l+1) {
		if (ip[l] == 0) {
			hao[l][r] = 1;
			return 1;
		} else {
			hao[l][r] = 0;
			return 0;
		}
	}

	if (us[l][r]) return mem[l][r];
	us[l][r] = 1;
	int &ans = mem[l][r];
	ans = 0;

	int len = r-l;

	if (len%2) {
		int md = (l+r)/2;
		if (ip[md] == len/2) {
			ans = conv(l, md, r);
		} else {
			{
				int pv = fl[l][md];
				if (pv != -1) {
					(ans += conv(l, pv, r)) %= MD;
				}
			}

			{
				int pv = fr[r][md+1];
				if (pv != -1) {
					(ans += conv(l, pv, r)) %= MD;
				}
			}
		}
	} else {
		int md = (l+r)/2;
		{
			int pv = fl[l][md];
			if (pv != -1) {
				(ans += conv(l, pv, r)) %= MD;
			}
		}

		{
			int pv = fr[r][md];
			if (pv != -1) {
				(ans += conv(l, pv, r)) %= MD;
			}
		}
	}

	return ans;
}

int32_t main() {
	IOS;

	int T;
	cin >> T;
	while (T--) {
		cin >> N;
		for (int i=0; i<N; i++) cin >> ip[i];

		build();

		for (int i=0; i<=N; i++)
			for (int j=0; j<=N; j++) {
				us[i][j] = 0;
				hao[i][j] = 0;
			}

		int res = dp(0, N);
		if (hao[0][N]) cout << res << endl;
		else cout << "NO" << endl;
	}

	return 0;
}

