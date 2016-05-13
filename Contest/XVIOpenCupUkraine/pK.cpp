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


typedef long long ll;

const int MX = 5005;
const ll INF = 1LL<<31;

struct Car {
	ll x,v;
	ll at(ll t) { return x + v * t; }
	friend ostream& operator << (ostream &sout, Car c) { return sout << "(" << c.x << "," << c.v <<")"; }
};

int N,M,f[MX];
ll dp[3005][5005],u[MX],s[MX];
Car car[MX];
int deq[MX],fr,bk;

bool better(const Car &a, const Car &b, const Car &c) {
	return abs(b.x-a.x)*abs(c.v-b.v) >= abs(c.x-b.x)*abs(b.v-a.v);
}
int main() {
	IOS;
	cin >> N >> M;
	REP(i,N) cin >> f[i];
	s[0] = 0;
	u[0] = 0;
	REP1(i,1,N) {
		s[i] = s[i-1] + f[i-1] * i;
		u[i] = u[i-1] + f[i-1];
	}
	REP1(j,0,M) REP1(i,0,N) dp[j][i] = INF;
	dp[0][0] = 0;
	REP1(j,1,M) {
		fr = bk = 0;
		REP(i,N) car[i] = Car{dp[j-1][i]-s[i]+i*u[i],-i};
		REP1(i,0,N) {
//			REP(k,i) dp[j][i] = min(dp[j][i], dp[j-1][k]+s[i]-s[k]-k*u[i]+k*u[k]);
//			continue;
			int t= u[i];
			while (bk-fr >= 2) {
				int x = deq[fr], y = deq[fr+1];
				if (car[x].at(t) < car[y].at(t)) break;
				fr++;
			}
//			REP1(k,fr,bk-1)	dp[j][i] = min(dp[j][i], car[deq[k]].at(t)+s[i]);
			if (fr != bk) dp[j][i] = car[deq[fr]].at(t) + s[i];
			dp[j][i] = min(dp[j][i],INF);
			
			while (bk-fr >= 2 and better(car[deq[bk-2]],car[deq[bk-1]],car[i])) bk--;
			deq[bk++] = i;
		}
	}
	/*
	REP1(i,0,M) {
		REP1(j,0,N) cout << dp[i][j] << " ";
		cout << endl;
	}
	*/


	cout << dp[M][N] << endl;

	return 0;
}

