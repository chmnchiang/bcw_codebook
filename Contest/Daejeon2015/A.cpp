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
const int MX = 666;
int V, E;
vector<int> el[MX];
int _dis[MX][MX];
bool vt[MX];
const int INF = 1029384756;

void bfs(int s, int *dis) {
	queue<int> qe;
	qe.push(s);
	for (int i=0; i<=V; i++) {
		vt[i] = 0;
		dis[i] = INF;
	}
	dis[s] = 0;
	vt[s] = 1;
	while (SZ(qe)) {
		int v = qe.front(); qe.pop();
		for (auto u: el[v]) {
			if (vt[u]) continue;
			dis[u] = dis[v] + 1;
			vt[u] = 1;
			qe.push(u);
		}
	}
}

typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = 205;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r;
		long long f, c;
	};
	int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
	long long dis[MXN], fl, cost;
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
		fl = cost = 0;
	}
	void add_edge(int u, int v, long long f, long long c) {
		E[u].PB({v, SZ(E[v])  , f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, -c});
	}
	pll flow() {
		while (true) {
			for (int i=0; i<n; i++) {
				dis[i] = INF;
        inq[i] = 0;
			}
			dis[s] = 0;
			queue<int> que;
			que.push(s);
			while (!que.empty()) {
				int u = que.front(); que.pop();
				inq[u] = 0;
				for (int i=0; i<SZ(E[u]); i++) {
					int v = E[u][i].v;
					long long w = E[u][i].c;
					if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
						prv[v] = u; prvL[v] = i;
						dis[v] = dis[u] + w;
						if (!inq[v]) {
							inq[v] = 1;
							que.push(v);
						}
					}
				}
			}
			if (dis[t] == INF) break;
			long long tf = INF;
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				tf = min(tf, E[u][l].f);
			}
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				E[u][l].f -= tf;
				E[v][E[u][l].r].f += tf;
			}
			cost += tf * dis[t];
			fl += tf;
		}
		return {fl, cost};
	}
}flow;

int main() {
	IOS;

	int T;
	cin >> T;
	while (T--) {
		cin >> V >> E;
		for (int i=0; i<=V; i++) el[i].clear();
		for (int i=0; i<E; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			el[u].PB(v);
			el[v].PB(u);
		}

		for (int i=0; i<V; i++) {
			bfs(i, _dis[i]);
		}


		vector<int> V1, V2;
		for (int i=0; i<V; i++) {
			int t; cin >> t;
			if (t) V1.PB(i);
		}
		for (int i=0; i<V; i++) {
			int t; cin >> t;
			if (t) V2.PB(i);
		}


		int Z = SZ(V1);
		int S = Z*2, U = S+1, N = U+1;
		flow.init(N, S, U);
		for (int i=0; i<Z; i++) flow.add_edge(S, i, 1, 0);
		for (int i=0; i<Z; i++) flow.add_edge(i+Z, U, 1, 0);

		for (int i=0; i<Z; i++)
			for (int j=0; j<Z; j++) flow.add_edge(i, Z+j, 1, _dis[V1[i]][V2[j]]);

		auto p = flow.flow();
		cout << p.S << endl;

	}

	return 0;
}


