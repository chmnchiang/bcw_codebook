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
typedef pair<ll,ll> pll;
const ll INF = 1LL<<60;

int N,M;
pll dis[305][305];

int main() {
	FILEIO("trip");
	IOS;
	cin >> N >> M;
	REP1(i,1,N) {
		REP1(j,1,N) dis[i][j] = {INF,INF};
		dis[i][i] = {0,0};
	}

	REP(_,M) {
		int a,b,c;
		cin >> a >> b >> c;
		dis[a][b] = dis[b][a] = min(dis[a][b], {c,1});
	}

	REP1(k,1,N) REP1(i,1,N) REP1(j,1,N) {
		ll x = dis[i][k].F + dis[k][j].F;
		ll y = dis[i][k].S + dis[k][j].S;
		dis[i][j] = min(dis[i][j], {x,y});
	}
	ll x = 0;
	ll y = 0;
	REP1(i,1,N) {
		REP1(j,i+1,N) {
			x += dis[i][j].S;
			y++;
		}
	}
	long double a = x;
	a /= y;
	cout << fixed << setprecision(20) << a << endl;

	return 0;
}
