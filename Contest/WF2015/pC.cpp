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
typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = 305;
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

const int INF = 1e12;
const int MX = 333;
int N, K;
int mp[MX][MX];

int32_t main() {
	IOS;
	cin>>N>>K;
	for (int i=0; i<N; i++) {
		for (int j=i+1; j<=N; j++) {
			cin >> mp[i][j];
		}
	}

	int V = N*2+3;
	int S = N+N+1, SS = 0, T = N*2+2;

	flow.init(V, S, T);
	flow.add_edge(S, SS, K, 0);
	flow.add_edge(SS, T, K, 0);
	for (int i=1; i<=N; i++) {
		flow.add_edge(SS, i, 1, mp[0][i]);
		flow.add_edge(i+N, T, 1, 0);
		flow.add_edge(i, i+N, 1, -INF);

		for (int j=i+1; j<=N; j++) {
			flow.add_edge(i+N, j, 1, mp[i][j]);
		}
	}

	auto p = flow.flow();
	int c = p.S + INF*N;
	cout << c << endl;

	return 0;
}

