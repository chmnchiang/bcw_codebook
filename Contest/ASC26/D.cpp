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


int N;
struct Edge {
	int u, v, w;
	bool operator < (const Edge &e) const {
		return w < e.w;
	}
};
vector<Edge> E;

const int MX = 3333;
int djs[MX];
vector<int> el[MX];
int mat[MX][MX];
int mn[MX];

static void dinit() {
	for (int i=0; i<MX; i++) djs[i] = i;
}

int ffa(int a) {
	return (djs[a] == a ? a : (djs[a] = ffa(djs[a])));
}

void dfs(int u, int fa, int val) {
	//cout << "u = " << u << endl;
	mn[u] = val;
	for (auto e: el[u]) {
		auto ee = E[e];

		int v = (ee.u == u ? ee.v : ee.u);
		if (v == fa) continue;

		dfs(v, u, min(ee.w, val));
	}
}

const int INF = 1029384756;

bool check(int u) {
	dfs(u, -1, INF);

	//cout << "u = " << u << endl;
	/*
	for (int i=0; i<N; i++) {
		cout << mn[i] << ' ';
	}
	cout << endl;
	*/

	for (int i=0; i<N; i++) {
		if (i == u) continue;
		if (mn[i] != mat[u][i]) return false;
	}
	return true;
}

int main() {
	FILEIO("matrix");

	cin >> N;

	dinit();

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			int x;
			cin >> x;
			mat[i][j] = x;
			if (i < j) {
				E.PB({i, j, x});
			}
		}
	}
	sort(ALL(E));
	reverse(ALL(E));


	vector<int> ans;

	for (int i=0; i<SZ(E); i++) {
		auto e = E[i];
		if (ffa(e.u) == ffa(e.v)) continue;

		ans.PB(i);
		djs[ffa(e.u)] = ffa(e.v);

		el[e.u].PB(i);
		el[e.v].PB(i);
	}

	assert(SZ(ans) == N-1);

	/*
	for (auto x: ans) {
		cout << E[x].u << ' ' << E[x].v << ' ' << E[x].w << endl;
	}*/


	for (int i=0; i<N; i++) {
		if (!check(i)) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;
	cout << SZ(ans) << endl;
	for (auto x: ans) {
		cout << E[x].u+1 << ' ' << E[x].v+1 << ' ' << E[x].w << endl;
	}

    return 0;
}

