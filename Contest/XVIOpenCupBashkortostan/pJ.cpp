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

typedef pair<int,int> pii;

bitset<1000006> prv[105];
int N,P,Q,dp[1000006];
pii ip[105];

bool solve() {
//	cout << "SOLVE " << P << " " << Q << endl;
	REP(i,Q) dp[i] = -1;
	dp[0] = 0;
	REP1(i,1,N) {
		prv[i].reset();
		for (int j=Q-1; j>=ip[i].F; j--) {
			if (dp[j-ip[i].F] != -1 && dp[j] < dp[j-ip[i].F]+ip[i].S) {
				dp[j] = dp[j-ip[i].F]+ip[i].S;
				prv[i][j] = 1;
			}
		}
		/*
		REP(j,Q) cout << dp[j] << " ";
		cout << endl;
		*/
	}
	int best = -1;
	REP(i,Q) {
		if (dp[i] >= P) {
			best = i;
			break;
		}
	}
	if (best == -1) {
		return false;
	} else {
		string ans = "";
		int j = best;
		for (int i=N; i>=1; i--) {
			if (prv[i][j]) {
				ans += "1";
				j -= ip[i].F;
			} else {
				ans += "0";
			}
		}
		reverse(ALL(ans));
		cout << "NO" << endl;
		cout << ans << endl;
		return true;
	}
}

int main() {
	IOS;
	cin >> N;
	cin >> P;
	REP1(i,1,N) cin >> ip[i].S;
	cin >> Q;
	REP1(i,1,N) cin >> ip[i].F;

	if (!solve()) {
		REP1(i,1,N) swap(ip[i].F, ip[i].S);
		swap(P,Q);
		if (!solve()) {
			cout << "YES" << endl;
		} 
	} 

	
	return 0;
}

