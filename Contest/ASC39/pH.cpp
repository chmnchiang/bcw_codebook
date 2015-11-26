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

const int MX = 111;
struct Isap{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,f,SZ(E[u])-1});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (nf){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  int flow(int res=0){
    FZ(h); FZ(gap);
    gap[0] = n;
    while (h[s] < n) res += DFS(s,2147483647);
    return res;
  }
}flow;

int V, E, K;
vector<int> el[MX];
int deg[MX];

bool judge(int v) {
	int VV = V + 2, S = 0, T = VV - 1;
	flow.init(VV, S, T);

	for (int i=1; i<=V; i++) {
		for (auto u: el[i]) {
			if (u < i) {
				flow.add_edge(i, u, 1);
			}
		}
	}

	int sm = 0;
	for (int i=1; i<=V; i++) {
		int z = 2*K - deg[i];
		if (z >= 0) {
			flow.add_edge(i, T, z);
		} else if (z < 0) {
			flow.add_edge(S, i, -z);
			sm += -z;
		}
	}

	const int INF = 102938475;
	flow.add_edge(S, v, INF);

	int fl = flow.flow();
	fl -= sm;
	return fl < 2*K;
}

bool vt[MX];
int ans;

void dfs(int v) {
	if (vt[v]) return;
	vt[v] = true;
	ans ++;

	for (auto e: flow.E[v]) {
		int u = e.v, f = e.f;
		if (f > 0) dfs(u);
	}
}

void findAns() {
	ans = 0;
	dfs(0);

	cout << "Redundant" << endl;
	cout << ans-1 << endl;
	bool _f = true;
	for (int i=1; i<=V; i++) {
		if (vt[i]) {
			if (_f) {
				_f = false;
			} else cout << ' ';
			cout << i;
		}
	}
}

int main() {
    FILEIO("highways");
	cin >> V >> E >> K;

	for (int i=0; i<E; i++) {
		int u, v; cin >> u >> v;
		el[u].PB(v);
		el[v].PB(u);
		deg[u]++;
		deg[v]++;
	}

	for (int i=1; i<=V; i++) {
		if (judge(i)) {
			findAns();
			return 0;
		}
	}

	cout << "OK" << endl;



    return 0;
}

