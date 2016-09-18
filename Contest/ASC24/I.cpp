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

void Zval(const char *s, int len, int *z) {
	z[0] = 0;
	for (int b=0, i=1; i<len; i++) {
		z[i] = max(min(z[i-b], z[b] + b - i), 0);
		while (s[i + z[i]] == s[z[i]]) z[i] ++;
		if (i+z[i] > b+z[b]) b=i;
	}
}
using pii = pair<int, int>;

const int MX = 3010;
char ip[2][MX];
short dp[2][MX][MX];
int L[2];
/*
void build(int id) {
	slen = 0;
	for (int i=id; i<L[0]; i++) {
		ss[slen++] = ip[0][i];
	}
	ss[slen++] = '@';
	int cc = slen;
	for (int i=0; i<L[1]; i++) {
		ss[slen++] = ip[1][i];
	}
	Zval(ss, slen, tz);

	for (int i=0; i<L[1]; i++) {
		dp[1][id][i] = tz[cc+i];
	}

	slen = 0;
	for (int i=id-1; i>=0; i--) {
		ss[slen++] = ip[0][i];
	}
	ss[slen++] = '@';
	cc = slen;

	Zval(ss, slen, tz);
	for (int i=L[1]-1; i>=0; i--) {
		dp[0][id][i+1] = tz[cc+i];
	}
}*/

int main() {
	IOS;
	FILEIO("subpair");

	cin >> ip[0] >> ip[1];
	L[0] = strlen(ip[0]);
	L[1] = strlen(ip[1]);

	for (int i=0; i<=L[0]; i++) {
		for (int j=0; j<=L[1]; j++) {
			if (j and i) {
				if (ip[0][i-1] == ip[1][j-1]) {
					dp[0][i][j] = dp[0][i-1][j-1] + 1;
				}
			}
		}
	}

	for (int i=L[0]; i>=0; i--) {
		for (int j=L[1]; j>=0; j--) {
			if (i != L[0] and j != L[1]) {
				if (ip[0][i] == ip[1][j]) {
					dp[1][i][j] = dp[1][i+1][j+1] + 1;
				}
			}
		}
	}

	for (int i=0; i<=L[0]; i++) {
		for (int j=0; j<=L[1]; j++) {
			if (i) dp[0][i][j] = max(dp[0][i][j], dp[0][i-1][j]);
			if (j) dp[0][i][j] = max(dp[0][i][j], dp[0][i][j-1]);
		}
	}

	for (int i=L[0]; i>=0; i--) {
		for (int j=L[1]; j>=0; j--) {
			if (i!=L[0]) dp[1][i][j] = max(dp[1][i][j], dp[1][i+1][j]);
			if (j!=L[1]) dp[1][i][j] = max(dp[1][i][j], dp[1][i][j+1]);
		}
	}

	int bv = -1;
	int bi, bj;
	int l1, l2;
	for (int i=0; i<=L[0]; i++) {
		for (int j=0; j<=L[1]; j++) {
			int t1 = dp[0][i][j], t2 = dp[1][i][j];
			int v = t1+t2;
			if (v > bv) {
				bv = v;
				bi = i; bj = j;
				l1 = t1; l2 = t2;
			}
		}
	}


	int ni = bi, nj = bj;
	while (ni > 0 and dp[0][ni-1][nj] == l1) ni--;
	for (int i=l1-1; i>=0; i--) {
		cout << ip[0][ni-1-i];
	}
	cout << endl;

	ni = bi, nj = bj;
	while (ni < L[0] and dp[1][ni+1][nj] == l2) ni++;
	for (int i=0; i<l2; i++) {
		cout << ip[0][ni+i];
	}
	cout << endl;

	
	

	return 0;
}

