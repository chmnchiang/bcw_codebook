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



#define int long long
const int MX = 222;
const int MD = 1000000007;
int N, M, P;
int mem[MX][MX][2];
int hao[MX][MX];

int digit(int n) {
	if (!n) return 1;
	int t = 0;
	while (n) {
		t++; n/=10;
	}
	return t;
}

void pre() {
	for (int i=0; i<M; i++) hao[digit(i)][i]++;

}


bool us[MX][MX][2];
int dp(int l, int r, int p, bool h) {

	int len = r - l;
	if (us[len][p][h]) return mem[len][p][h];

	us[len][p][h] = 1;
	int &res = mem[len][p][h];
	res = hao[len][p];

	if (len >= 3) {
		res += dp(l+1, r-1, p, 0);
		res %= MD;
	}

	if (h) return res;

	for (int k=l+1; k<r-1; k++) {
		for (int i=0; i<M; i++) {
			int j = (p - i + M) % M;
			res += dp(l, k, i, 0) * dp(k+1, r, j, 1);
			res %= MD;

			j = (p + i) % M;
			res += dp(l, k, j, 0) * dp(k+1, r, i, 1);
			res %= MD;
		}
	}

	return res;
}

int32_t main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;

	cin >> N >> M >> P;
	pre();

	cout << dp(0, N, P, 0) << endl;

	return 0;
}

