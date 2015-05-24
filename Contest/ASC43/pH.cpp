//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef long long LL;

struct Isap{
	static const int MX_NODE = 10000;
	struct Edge{
		int v,re;
		LL f;
		Edge () { v = f = re = -1; }
		Edge (int _v, LL _f, int _r) : v(_v), re(_r), f(_f) {}
	};
	int n,s,t;
	int fr,bk,que[MX_NODE], level[MX_NODE];
	vector<Edge> E[MX_NODE];
	vector<int> sol;
	bool vt[MX_NODE];
	void init(int _n, int _s, int _t){
		n = _n;
		s = _s;
		t = _t;
		for (int i=0; i<n; i++)
			E[i].clear();

		sol.clear();
		FZ(vt);
	}
	void add_edge(int u, int v, LL f){
		E[u].PB(Edge(v,f,E[v].size()));
		E[v].PB(Edge(u,f,E[u].size()-1));
	}
	bool BFS(){
		FMO(level);
		fr = bk = 0;
		que[bk++] = s;
		level[s] = 0;
		while (fr < bk){
			int u = que[fr++];
			for (auto it : E[u]){
				if (it.f > 0 && level[it.v] == -1){
					level[it.v] = level[u] + 1;
					que[bk++] = it.v;
				}
			}
		}
		return level[t] != -1;
	}
	LL DFS(int u, LL nf){
		if (u == t) return nf;
		LL res = 0;
		for (auto &it : E[u]){
			if (it.f > 0 && level[it.v] == level[u]+1){
				LL tf = DFS(it.v, min(it.f, nf));
				res += tf; nf -= tf; it.f -= tf;
				E[it.v][it.re].f += tf;
				if (nf == 0) return res;
			}
		}
		if (!res) level[u] = -1;
		return res;
	}
	LL flow(){
		LL res = 0;
		while ( BFS() ){
			res += DFS(s, 1ll<<62);
		}
		return res;
	}

	void calcSol(int u) {
		sol.PB(u);
		vt[u] = true;
		for (auto &it : E[u]) {
			if( it.f and !vt[it.v]) {
				calcSol(it.v);
			}
		}
	}
}flow;

int N;
int main(){

	FILEIO("hentium");
	while(cin >> N and N) {
		int S, T, V;
		S = N; T = N + 1; V = N + 2;
		flow.init(V, S, T);

		for(int i=0; i<N; i++) {
			int a, b;
			cin >> a >> b;
			flow.add_edge(S, i, a);
			flow.add_edge(i, T, b);
		}

		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++) {
				int a;
				cin >> a;
				if( j <= i ) continue;
				flow.add_edge(i, j, a);
			}

		LL ans = flow.flow();
		cout << ans << endl;
		flow.calcSol(S);
		for(int i=0; i<N; i++) {
			if(i != 0) cout << ' ';
			if( flow.vt[i] ) 
				cout << 2;
			else cout << 1;
		}
		cout << endl;
	}

	return 0;
}

