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

struct Dinic{
	static const int MXN = 10000;
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

int N,M;
int ip[55][55];

inline int getid(int i, int j) { return i * M + j; }

int main() {
	IOS;
	int ts;
	cin >> ts;
	while (ts--) {
		cin >> N >> M;
		REP(i,N) REP(j,M) cin >> ip[i][j];
		int V = N * M + 2;
		int S = V - 2;
		int T = V - 1;
		int sum = 0;
		flow.init(V,S,T);
		static const int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
		REP(i,N) {
			REP(j,M) {
				sum += ip[i][j];
				if ((i + j) & 1) {
					flow.add_edge(S, getid(i,j), ip[i][j]);
					REP(d,4) {
						int x = i + dir[d][0];
						int y = j + dir[d][1];
						if (x < 0 or x >= N or y < 0 or y >= M) continue;
						flow.add_edge(getid(i,j), getid(x,y), 2147483647);
					}
				} else {
					flow.add_edge(getid(i,j), T, ip[i][j]);
				}
			}
		}
		int ans = sum - flow.flow();
		cout << ans << endl;
	}

	return 0;
}

