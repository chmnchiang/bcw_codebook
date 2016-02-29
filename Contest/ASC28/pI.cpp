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
const int MXN = 200005;

int N,M,dfn[MXN],low[MXN],step;
ll ans[MXN];
vector<int> E[MXN];

int DFS(int u, int f) {
	int rsz = 1;
	int sz = 0;
	dfn[u] = low[u] = ++step;
	long long cnt = 0;
	int isap = 0;
	for (auto v:E[u]) {
		if (v == f) continue;
		if (dfn[v]) {
			low[u] = min(low[u], dfn[v]);
		} else {
			int vsz = DFS(v, u);
			low[u] = min(low[u], low[v]);
			rsz += vsz;
			if (low[v] >= dfn[u]) {
				isap = 1;
				cnt += 1LL * sz * vsz;
				sz += vsz;
	//			cout << "COUNT " << u << " " << v << " " <<  sz << endl;
			}
		}
	}
	if (isap && u != f) {
//		cout << "COUNT " << u << " " << sz << endl;
//		cout << cnt << endl;
		cnt += 1LL * sz * (N-sz-1);
	}
	cnt += N-1;
	ans[u] = cnt;
	return rsz;
}

int main() {
	IOS;
	FILEIO("travel");
	cin >> N >> M;
	REP(_,M) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
		E[v].PB(u);
	}
	REP1(i,1,N) {
		if (!dfn[i]) {
			DFS(i,i);
		}
	}
	REP1(i,1,N) {
		cout << ans[i] << endl;
	}


    return 0;
}

