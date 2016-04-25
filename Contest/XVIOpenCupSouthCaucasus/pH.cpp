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
typedef pair<int, int> pii;
const int MX = 555555;
int N, M;
vector<int> el[MX];
pii val[MX];

int cost;
void dfs(int u, int fa) {
	if (u <= M) return;

	vector<int> vec;
	int cnt = 0;
	for (auto v: el[u]) {
		if (v == fa) continue;

		dfs(v, u);
		vec.PB(val[v].F);
		vec.PB(val[v].S);
		cnt ++;
	}
	sort(ALL(vec));

	int x = vec[SZ(vec)/2-1], y = vec[SZ(vec)/2];
	//cout << x << ' ' << y << endl;
	for (auto v: el[u]) {
		if (v == fa) continue;
		pii p = val[v];
		if (x < p.F) cost += abs(p.F - x);
		else if (x > p.S) cost += abs(p.S - x);
	}
	//cout << cost << endl;
	val[u] = {x, y};
}

int32_t main() {
	IOS;
	cin>>N>>M;
	for (int i=0; i<N-1; i++) {
		int u,v; cin>>u>>v;
		el[u].PB(v);
		el[v].PB(u);
	}

	for (int i=1; i<=M; i++) {
		int t;cin>>t;
		val[i] = pii(t, t);
	}

	if (N == M) {
		int ans = 0;
		for (int u=1; u<=M; u++) {
			for (auto v: el[u]) {
				if (v > u) continue;
				ans += abs(val[u].F - val[v].F);
			}
		}
		cout << ans << endl;
		return 0;
	}

	dfs(M+1, -1);
	cout << cost << endl;



	return 0;
}

