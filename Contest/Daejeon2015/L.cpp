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

int N,M,ip[10000];
ll X,Y;

void input() {
	cin >> N >> M;
	X = 0;
	REP(i,M) {
		int v;
		cin >> v;
		X = X * 10 + v;
	}
	Y = 0;
	REP(i,M) {
		int v;
		cin >> v;
		Y = Y * 10 + v;
	}
	REP(i,N) cin >> ip[i];
}
void solve() {
	int ans = 0;
	REP(i,N) {
		ll Z = 0;
		REP(j,M) {
			int k = (i + j) % N;
			Z = Z * 10 + ip[k];
		}
		if (X <= Z and Z <= Y) ans++;
	}
	cout << ans << endl;
}
int main() {
	IOS;
	int ts;
	cin >> ts;
	while (ts--) {
		input();
		solve();
	}

    return 0;
}

