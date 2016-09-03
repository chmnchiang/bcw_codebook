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


const int INF = 1029384756;
typedef pair<int,int> pii;

int N,M;
int cb,ci,cd,cc;
int dp[3005][3005];
int nxtb[3005][3005];
uint8_t tp[3005][3005];

string A,B;

int main() {
	FILEIO("block");
	IOS;
	cin >> cb >> ci >> cd >> cc;
	cin >> A >> B;
	N = SZ(A);
	M = SZ(B);
	REP1(j,0,M) REP1(i,0,N) dp[j][i] = INF;
	for (int j=M; j>=0; j--) {
		int minc = INF;
		int mink = N+1;
		for (int i=N; i>=0; i--) {
			int &res = dp[j][i];
			if (j == M and i == N) {
				res = 0;
				if (minc > res) {
					minc = res;
					mink = i;
				}
				continue;
			}
			res = INF;
			if (i < N and res > dp[j][i+1] + cd) {
				res = dp[j][i+1] + cd;
				tp[j][i] = 0;
			}
			if (j < M and res > dp[j+1][i] + ci) {
				res = dp[j+1][i] + ci;
				tp[j][i] = 1;
			}
			if (i < N and j < M and A[i] == B[j] and res > dp[j+1][i+1] + cc) {
				res = dp[j+1][i+1]+cc;
				tp[j][i] = 2;
			}
			/*
			for (int k=i+1; k<=N; k++) {
				if (res > dp[j][k] + cb) {
					res = dp[j][k] + cb;
					tp[j][i] = 3;
					nxtb[j][i] = k;
				}
			}
			*/
			if (res > minc + cb) {
				res = minc + cb;
				tp[j][i] = 3;
				nxtb[j][i] = mink;
			}
			if (minc > res) {
				minc = res;
				mink = i;
			}
		}
	}

	int i = 0, j = 0;
	vector<pii> vec;
	string ans;
	while (i < N or j < M) {
		if (tp[j][i] == 0) {
			ans += "D";
			i++;
		} else if (tp[j][i] == 1) {
			ans += "I";
			j++;
		} else if (tp[j][i] == 2) {
			ans += "C";
			i++;
			j++;
		} else if (tp[j][i] == 3) {
			vec.PB({i,nxtb[j][i]-1});
			i = nxtb[j][i];
		} else {
			assert(false);
		}
	}

	cout << dp[0][0] << endl;
	cout << SZ(vec) << endl;
	for (auto it:vec) cout << it.F+1 << " " << it.S+1 << endl;
	cout << ans << endl;


	return 0;
}
