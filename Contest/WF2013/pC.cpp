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

#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

using pii=pair<int,int>;
int V, E, C;
const int MX = 33333;
vector<pii> el[MX];
int dis[MX];
bool inq[MX];
const int INF = 1029384756;

void spfa() {
	fill(dis, dis+V+1, INF);
	dis[1] = 0;
	priority_queue<pii> qe;
	qe.push({0, 1});

	while (SZ(qe)) {
		int v = qe.top().S;
		int cc = -qe.top().F;
		qe.pop();
		if (cc != dis[v]) continue;
		for (auto p: el[v]) {
			int u = p.F, c = p.S;
			if (dis[u] > dis[v] + c) {
				dis[u] = dis[v] + c;
				qe.push({-dis[u],u});
			}
		}
	}
}

struct Dinic{
	static const int MXN = MX;
	struct Edge{ int v,f,re; };
	int n,s,t,level[MXN];
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t){
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
	}
	void add_edge(int u, int v, int f){
		E[u].PB({v,f,SZ(E[v])});
		E[v].PB({u,0,SZ(E[u])-1});
	}
	bool BFS(){
		FMO(level);
		queue<int> que;
		que.push(s);
		level[s] = 0;
		while (!que.empty()){
			int u = que.front(); que.pop();
			for (auto it : E[u]){
				if (it.f > 0 && level[it.v] == -1){
					level[it.v] = level[u]+1;
					que.push(it.v);
				}
			}
		}
		return level[t] != -1;
	}
	int DFS(int u, int nf){
		if (u == t) return nf;
		int res = 0;
		for (auto &it : E[u]){
			if (it.f > 0 && level[it.v] == level[u]+1){
				int tf = DFS(it.v, min(nf,it.f));
				res += tf; nf -= tf; it.f -= tf;
				E[it.v][it.re].f += tf;
				if (nf == 0) return res;
			}
		}
		if (!res) level[u] = -1;
		return res;
	}
	int flow(int res=0){
		while ( BFS() )
			res += DFS(s,2147483647);
		return res;
	}
}flow;
int main() {
	IOS;
	cin >> V >> E >> C;

	loop (i, 0, E) {
		int u, v, c;
		cin >> u >> v >> c;
		el[u].PB({v, c});
		el[v].PB({u, c});
	}

	spfa();

	vector<int> vtx(C);
	for (int i=0; i<C; i++) {
		cin >> vtx[i];
	}
	sort(ALL(vtx), [&](int i, int j) { return dis[i] < dis[j]; });

	//for (int i=1; i<=V; i++) cout << dis[i] << ' '; cout << endl;

	int nl, nr;
	nl = nr = 0;
	int ans=0;
	while (nl < C) {
		while (nr < C and dis[vtx[nr]] == dis[vtx[nl]]) nr++;

		int vv = V+1+2, ss=vv-2, tt=vv-1;
		flow.init(vv, ss, tt);
		for (int i=nl; i<nr; i++) {
			flow.add_edge(ss, vtx[i], 1);
		}
		flow.add_edge(1, tt, nr-nl);

		for (int i=1; i<=V; i++) {
			for (auto p: el[i]) {
				if (dis[i] + p.S != dis[p.F]) continue;
				flow.add_edge(p.F,i, 1);
			}
		}
		ans += flow.flow();
		nl = nr;
	}
	cout << ans << endl;

	return 0;
}

