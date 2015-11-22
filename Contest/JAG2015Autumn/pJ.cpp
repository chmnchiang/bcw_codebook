#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

typedef pair<long long, long long> pll;

struct CostFlow {
	static const int MXN = 205;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r;
		long long f, c;
	};
	int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
	long long dis[MXN], cost, fl;
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
		cost = fl = 0;
	}
	void add_edge(int u, int v, long long f, long long c) {
		E[u].PB({v, SZ(E[v])  , f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, -c});
	}
	pll flow() {
		while (true) {
			for (int i=0; i<n; i++) {
				dis[i] = INF;
				prv[i] = prvL[i] = -1;
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
						prv[v] = u;
						prvL[v] = i;
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
			int v = t;
			while (v != s) {
				int u = prv[v], l = prvL[v];
				tf = min(tf, E[u][l].f);
				v = u;
			}
			v = t;
			while (v != s) {
				int u = prv[v], l = prvL[v];
				E[u][l].f -= tf;
				E[v][E[u][l].r].f += tf;
				v = u;
			}
			cost += tf * dis[t];
			fl += tf;
			return {fl, cost};
		}
		return {fl, cost};
	}

}flow;

int N, M, S, T;
double P;

int main() {
    IOS;
	while (cin >> N >> M >> P >> S >> T) {
		S--; T--;
		flow.init(N, S, T);
		for (int i=0, u, v, c, f; i<M; i++) {
			cin >> u >> v >> c >> f;
			u--; v--;
			flow.add_edge(u, v, f, c);
		}
		long long fl = 0, cost = 0;
		double ans = 1E30;
		while (true) {
			pll r = flow.flow();
			if (r.F == fl && r.S == cost) break;
			fl = r.F;
			cost = r.S;

			double val = (P + cost) / (double)fl;
			ans = min(ans, val);
		}

		cout<<fixed<<setprecision(12)<<ans<<endl;
	}

    return 0;
}

