#pragma GCC optimize ("O2")
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


using pii = pair<int,int>;

const int MXN = 100005;
const int MX = 1000005;

struct DisjoinSet {
	int fa[MXN],ne[MXN];
	void init(int n) {
		REP(i,n) {
			fa[i] = i;
			ne[i] = 0;
		}
	}
	int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
	void uni(int x, int y) {
		x = f(x);
		y = f(y);
		if (x == y) return;
		fa[y] = x;
		ne[x] += ne[y];
		ne[y] = 0;
	}
	void add(int x) {
		x = f(x);
		ne[x]++;
	}
};

struct BccEdge {
  static const int MXN = 100005;
  struct Edge { int v,eid; };
  int n,m,step,par[MXN],dfn[MXN],low[MXN];
  int deg[MXN];
  vector<Edge> E[MXN];
  DisjoinSet djs;

  void init(int _n) {
    n = _n; m = 0;
    for (int i=0; i<n; i++) E[i].clear();
    djs.init(n);
  }
  void add_edge(int u, int v) {
    E[u].PB({v, m});
    E[v].PB({u, m});
    m++;
  }
  void DFS(int u, int f, int f_eid) {
    par[u] = f;
    dfn[u] = low[u] = step++;
    for (auto it:E[u]) {
      if (it.eid == f_eid) continue;
      int v = it.v;
      if (dfn[v] == -1) {
        DFS(v, u, it.eid);
        low[u] = min(low[u], low[v]);
      } else {
        low[u] = min(low[u], dfn[v]);
      }
    }
  }
  vector<int> solve() {
    step = 0;
    memset(dfn, -1, sizeof(int)*n);
    for (int i=0; i<n; i++) {
      if (dfn[i] == -1) DFS(i, i, -1);
    }
    djs.init(n);
	vector<int> res;
    for (int i=0; i<n; i++) {
      if (low[i] < dfn[i]) {
		  djs.uni(par[i], i);
	  } else {
		  for (auto it:E[i]) {
			  if (it.v == par[i])
				  res.PB(it.eid);
		  }
	  }
    }
	return res;
  }
} graph;

struct Edge {
	int u,v,w;
} edge[MX];

int N,M,bye[MX],bridge[MX],par[MXN],vt[MXN],peid[MXN];
int ws360[MX];
int dir[MX];
long long dp[MXN],deg[MXN];
vector<int> conn[MXN],eee[MXN];
vector<pii> E[MXN];
DisjoinSet djs;
vector<int> vvv[MXN];

void init() {
	REP(i,MXN) {
		par[i] = vt[i] = peid[i] = dp[i] = deg[i] = 0;
		conn[i].clear();
		eee[i].clear();
		E[i].clear();
		vvv[i].clear();
	}
	REP(i,MX) {
		bye[i] = bridge[i] = ws360[i] = dir[i] = 0;
	}
}
void DFS(int u, int f) {
	par[u] = f;
	dp[u] = deg[u];
	vt[u] = 1;
	for (auto v:eee[u]) {
		if (v == f or vt[v]) continue;
		DFS(v,u);
		dp[u] += dp[v];
	}
}
int DFS2(int u, int f) {
	vt[u] = 1;
	par[u] = f;
	vector<int> vec;

	for (auto it:E[u]) {
		int v = it.F;
		if (vt[v]) continue;
		peid[v] = it.S;
		int x = DFS2(v, u);
		if (x != -1) vec.PB(x);
	}
	if (ws360[u]) vec.PB(u);

	while (SZ(vec) >= 2) {
		int a = vec.back(); vec.pop_back();
		int b = vec.back(); vec.pop_back();

		while (a != u) {
			dir[peid[a]] ^= 1;
			a = par[a];
		}

		while (b != u) {
			dir[peid[b]] ^= 1;
			b = par[b];
		}
	}

	if (vec.empty()) return -1;
	return vec[0];
}
void del_edge(int u, int v) {
	int sz = SZ(E[u]);
	REP(i,sz) {
		if (E[u][i].F == v) {
			swap(E[u][i], E[u].back());
			E[u].pop_back();
			return;
		}
	}
}

void solve(int cid) {
	auto &V = conn[cid];
	if (V.empty()) return;

	if (djs.ne[cid] % 2 == 1) {
		vector<int> eid;
		for (auto u:V) {
			for (auto it:E[u]) {
				int v = it.F;
				int id = it.S;
				if (u < v) eid.PB(id);
			}
		}
		sort(ALL(eid), [](int a, int b) { return edge[a].w < edge[b].w; });
		int gg = -1;
		for (auto i:eid) {
			if (!bridge[i]) {
				int u = edge[i].u;
				int v = edge[i].v;
				gg = i;
				del_edge(u,v);
				del_edge(v,u);
				break;
			} else {
				int u = edge[i].u;
				int v = edge[i].v;
				if (graph.djs.f(v) == par[graph.djs.f(u)]) swap(u, v);
				assert(graph.djs.f(u) == par[graph.djs.f(v)]);

				if ((dp[v]-1)/2 % 2 == 0) {
					gg = i;
					del_edge(u,v);
					del_edge(v,u);
					break;
				}
			}
		}
		bye[gg] = 1;
	} else {
		//		go(V[0]);
	}
}
int main() {
	IOS;
	int T;
	cin>>T;
	REP(t,T) {
		init();
		//		cerr<<"Case "<<t<<endl;
		cin>>N>>M;
		djs.init(N);
		graph.init(N);
		REP(i,N) {
			E[i].clear();
			eee[i].clear();
			deg[i] = 0;
			vt[i] = 0;
		}

		REP(i,M) {
			cin>>edge[i].u>>edge[i].v>>edge[i].w;
			edge[i].u--;
			edge[i].v--;
			if (edge[i].u > edge[i].v) swap(edge[i].u, edge[i].v);
			int u = edge[i].u, v = edge[i].v;
			if (djs.f(u) != djs.f(v)) {
				djs.uni(u,v);
			}
			djs.add(u);

			E[u].PB({v,i});
			E[v].PB({u,i});
			graph.add_edge(u,v);

			bye[i] = 0;
			bridge[i] = 0;
		}

		for (auto i:graph.solve()) {
			bridge[i] = 1;
		}

		REP(i,N) {
			deg[graph.djs.f(i)] += SZ(E[i]);
		}

		REP(i,M) {
			int u = edge[i].u;
			int v = edge[i].v;
			u = graph.djs.f(u);
			v = graph.djs.f(v);
			if (u == v) continue;
			eee[u].PB(v);
			eee[v].PB(u);
		}
		REP(i,N) {
			sort(ALL(eee[i]));
			eee[i].resize(unique(ALL(eee[i]))-begin(eee[i]));
		}

		REP(i,N) {
			conn[djs.f(i)].PB(i);
		}

		REP(i,N) vt[i] = 0;
		REP(i,N) if (graph.djs.f(i) == i and !vt[i]) DFS(i,i);

		REP(i,N) vt[i] = 0;
		REP(i,N) {
			solve(i);
		}


		long long ans = 0;
		REP(i,N) deg[i] = 0;
		REP(i,M) {
			if (bye[i]) continue;
			ans += edge[i].w;
			deg[edge[i].v]++;
			dir[i] = 0;
			//			cout<<edge[i].u<<"=>"<<edge[i].v<<endl;
		}

		REP(i,N) {
			ws360[i] = deg[i] & 1;
		}

		REP(i,N) {
			vt[i] = 0;
			vvv[i].clear();
		}
		REP(i,N) {
			if (!vt[i]) DFS2(i,i);
		}

		REP(i,M) {
			if (bye[i]) continue;
			if (dir[i] == 0) vvv[edge[i].v].PB(i);
			else vvv[edge[i].u].PB(i);
		}
		//		REP(i,N) cout<<i<<" "<<vvv[i]<<endl;

		vector<pii> vec;
		REP(i,N) {
			int sz = SZ(vvv[i]);
			assert(sz % 2 == 0);
			for (int j=0; j<sz; j+=2) {
				vec.PB({vvv[i][j],vvv[i][j+1]});
			}
		}
		cout<<ans<<endl;
		cout<<SZ(vec)<<endl;
		for (auto it:vec) cout<<it.F+1<<" "<<it.S+1<<"\n";
	}

	return 0;
}

