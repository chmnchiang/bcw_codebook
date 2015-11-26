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

class Edge { public:
	int v,f,c,r;
};
struct edge_t {
	int v, f;
	double c;
};

const int MXN = 35;
const double eps = 1e-2;

int N, M, vst[MXN], prve[MXN], prv[MXN];
int onstk[MXN];
double dis[MXN];
vector<Edge> E[MXN];
vector<edge_t> eg[MXN];
vector<int> stk, cyc;

bool SPFA(int u){
	if (onstk[u]) {
		cyc.clear();
		while (stk.back() != u) {
			cyc.PB(stk.back());
			stk.pop_back();
		}
		cyc.PB(u);
		return true;
	}
	stk.PB(u);
	onstk[u] = 1;
	for (int i=0; i<SZ(eg[u]); i++) {
		if (eg[u][i].f <= 0) continue;
		int v = eg[u][i].v;
		double c = eg[u][i].c;
		if (dis[v] > dis[u] + c){
			prv[v] = u;
			prve[v] = i;
			dis[v] = dis[u] + c;
			if (SPFA(v)) return true;
		}
	}
	onstk[u] = 0;
	stk.pop_back();
	return false;
}


int main() {
	IOS;
	FILEIO("arbitrage");
	cin >> N >> M;
	for (int i=0, u, v, a, c; i<M; i++) {
		cin >> u >> v >> a >> c;
		E[u].PB({v,c,-a,SZ(E[v])});
		E[v].PB({u,0, a,SZ(E[u])-1});
	}
	for (int i=1; i<=N; i++) {
		E[0].PB({i,100000,0,SZ(E[i])});
		E[i].PB({0,0,0,SZ(E[i])-1});
	}
	long long ans = 0;
	
	double lst = -101;
	while (true) {
		double l = lst, r = 0;
		int have;
		while (r-l > eps) {
			double mid = (l+r)/2;
			eg[0].clear();
			for (int i=1; i<=N; i++) {
				eg[0].PB({i,1,0});
				eg[i].clear();
				for (auto &it : E[i]) {
					eg[i].PB({it.v, it.f, (double)it.c-mid});
				}
			}
			for (int i=1; i<=N; i++) dis[i] = 1e10;
			dis[0] = 0;
			FZ(onstk);
			stk.clear();
			cyc.clear();
			have = SPFA(0);
			if (have) r = mid;
			else l = mid;
		}
		eg[0].clear();
		for (int i=1; i<=N; i++) {
			eg[0].PB({i,1,0});
			eg[i].clear();
			for (auto &it : E[i]) {
				eg[i].PB({it.v, it.f, (double)it.c-r});
			}
		}
		for (int i=1; i<=N; i++) dis[i] = 1029384756;
		dis[0] = 0;
		FZ(onstk);
		stk.clear();
		cyc.clear();
		have = SPFA(0);
		if (!have) break;
		lst = r;
		int nf = 1029384756;
		int c = 0;
		for (auto v : cyc) {
			int u = prv[v];
			int id = prve[v];
			nf = min(nf, E[u][id].f);
			c += E[u][id].c;
		}
		for (auto v : cyc) {
			int u = prv[v];
			int id = prve[v];
			E[u][id].f -= nf;
			E[v][E[u][id].r].f += nf;
		}
		ans += nf * c;
	}
	ans = -ans;
	cout << ans << endl;

	return 0;
}

