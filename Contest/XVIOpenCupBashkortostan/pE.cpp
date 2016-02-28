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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef long long ll;
typedef pair<int,int> pii;
const int MXN = 28;
const int MX3 = 2188;
const int MX2 = 1<<6;


int pw3[10];
int N,K,S,L,R,p[MXN];
ll dp[2][MX3][MX2][MXN];
ll jie[11];
int usep[MXN];

vector<pii> trans3[MX3],trans2[MX2];

int getv(int s, int i) {
	REP(_,i) s /= 3;
	return s%3;
}
int setv(int s, int i, int v) {
	s -= getv(s,i) * pw3[i];
	s += v * pw3[i];
	return s;
}
void predo() {
	jie[0] = 1;
	REP1(i,1,10) jie[i] = jie[i-1] * i;
	pw3[0] = 1;
	REP1(i,1,9) pw3[i] = pw3[i-1]*3;
	REP(i,MX3) {
		REP(j,7) {
			int v = getv(i,j);
			if (v == 0) continue;
			trans3[i].PB({j+L, setv(i,j,v-1)});
		}
	}
	REP(i,MX2) {
		REP(j,6) {
			if (i & (1<<j)) {
				trans2[i].PB({j+S+1, i-(1<<j)});
			}
		}
	}
}

bool check1(int x) {
	return !usep[x] and K+1 <= x and x <= N;
}
int main() {
	IOS;
	cin >> N;
	REP(i,N) cin >> p[i];
	K = (N-1)/2;
	S = (K+1)/2;
	L = (K+1)/2;
	R = N/2;
	
	predo();
	
	FZ(usep);
	REP(i,N) {
		if (p[i]) usep[p[i]] = 1;
	}

	int three = 0;

	REP1(i,K+1,N) {
		three += pw3[i/2-L];
	}

	int two = (1<<(K-S))-1;
	int u = 0;
	dp[u][three][two][0] = 1;
	REP(i,N) {
		if (i % 2 == 0) {
			REP(j,MX3) {
				REP(k,MX2) {
					REP1(l,0,K) {
						if (dp[u][j][k][l] == 0) continue;
	//					cout << i << " " << j << " " << k << " " << l << " : " << dp[u][j][k][l] << endl;
						for (auto it:trans3[j]) {
							if (it.F < l) continue;
							if (p[i] != 0 and p[i]/2 != it.F) continue;
	//						cout << "TRANS3 " << it.F << " " << it.S << endl; 
							dp[u^1][it.S][k][it.F] += dp[u][j][k][l];
						}
					}
				}
			}
		} else {
			REP(j,MX3) REP(k,MX2) REP1(l,L,R) {
				if (dp[u][j][k][l] == 0) continue;
	//			cout << i << " " << j << " " << k << " " << l << " : " << dp[u][j][k][l] << endl;
				for (auto it:trans2[k]) {
					if (it.F > l) continue;
					if (p[i] != 0 and p[i] != it.F) continue;
					dp[u^1][j][it.S][it.F] += dp[u][j][k][l];
				}
				if (p[i] > S) continue;
				dp[u^1][j][k][0] += dp[u][j][k][l];
			}
		}
		u ^= 1;
	}
	/*
	REP(j,MX3)REP(k,MX2)REP1(l,0,N) {
		if (dp[u][j][k][l] == 0) continue;
		cout << N << " " << j << " " << k << " " << l << " : " << dp[u][j][k][l] << endl;
	}
	*/

	ll ans = 0;
	REP(i,MXN)
		ans += dp[u][0][0][i];

//	cout << "ORIGIN " << ans << endl;

	int cnts = 0;
	REP1(i,1,S) {
		if (not usep[i]) cnts++;
	}
	ans = ans * jie[cnts];

	REP1(i,L,R) {
		if (check1(2*i) and check1(2*i+1)) {
			ans = ans * 2;
		}
	}
	cout << ans << endl;

	
	return 0;
}

