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
	static const int MXN = 105*105*2;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r, tag;
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
		E[u].PB({v, SZ(E[v])  , 1, f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, 0, -c});
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
//			cout << tf << " " << dis[t] << endl;
			cost += tf * dis[t];
			fl += tf;
		}
		return {fl, cost};
	}
	void DFS(int u, vector<int> &res) {
		res.PB(u);
		if (u == t) return;
		for (auto &it: E[u]) {
			if (!it.tag) continue;
			int r = it.r;
			int v = it.v;
			if (E[v][r].f > 0) {
				E[v][r].f--;
				DFS(v, res);
				return;
			}
		}
	}
	vector<vector<int>> getAns() {
		vector<vector<int>> res;
		for (int i=0; i<fl; i++) {
			vector<int> tmp;
			DFS(s, tmp);
			res.PB(tmp);
//			cout << tmp << endl;
		}
		return res;
	}
}flow;

typedef pair<int,int> pii;
const int MXN = 105;
const int INF = 1029384756;

int N, M, K, q[MXN];
int tot;
pii mapping[MXN*MXN];
vector<int> photo[MXN];
int boy[MXN][MXN];

vector<int> filt(vector<int> vec) {
	vector<int> res;
	for (auto v : vec)
		if (v > N*M+N && v <= N*M+N+tot)
			res.PB(v - N*M - N);
	return res;
}
int main() {
	IOS;
	cin >> N >> K >> M;
	for (int i=1; i<=M; i++) {
		cin >> q[i];
	}
	int cnt = 0;
	for (int i=1, c, v; i<=N; i++) {
		cin >> c;
		cnt += c;
		while (c--) {
			cin >> v;
			photo[i].PB(v);
		}
	}
	tot = cnt;
	for (int i=1, x=1; i<=N; i++) {
		for (auto v : photo[i]) {
			mapping[x] = {i, v};
			x++;
		}
	}
	int V = N*M+N+cnt+4;
	int S = V-2;
	int T = V-1;
	flow.init(V, S, T);
	flow.add_edge(S, 0, K, 0);
	for (int i=1; i<=M; i++) {
		flow.add_edge(0, i, INF, 0);
	}
	for (int i=1; i<=N; i++) {
		int zj = N*M+i;
		for (int j=1; j<=M; j++) {
			int id = (i-1)*M + j;
			flow.add_edge(id, zj, INF, 0);
			if (i != N) {
				flow.add_edge(id, id+M, INF, 0);
			}
			if (i != 1) {
				flow.add_edge(zj-1, id, INF, q[j]);
			}
		}
	}
	flow.add_edge(N*M+N, T, INF, 0);

	for (int i=1, v=N*M+N+1; i<=N; i++) {
		int zj = N*M+i;
		for (auto x : photo[i]) {
			int nxt = i*M + x;
			flow.add_edge(nxt-M, v, 1, -INF);
			flow.add_edge(v, zj, 1, 0);
			if (i != N) {
				flow.add_edge(v, nxt, 1, 0);
			}
			v++;
		}
	}

	long long cost = flow.flow().S + 1LL * INF * cnt;
	cout << cost << endl;
	vector<vector<int>> vec = flow.getAns();
	for (int i=0; i<SZ(vec); i++) {
		vector<int> vec2 = filt(vec[i]);
		for (auto it2 : vec2) {
//			cout << mapping[it2] << " ";
			auto x = mapping[it2];
			boy[x.F][x.S] = i+1;
		}
//		cout << endl;
	}
	for (int i=1; i<=N; i++) {
		for (auto j : photo[i]) {
			cout << boy[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

