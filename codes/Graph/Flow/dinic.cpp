class Dinic{
public:
	static const int MXN = 10000;
  class Edge{
  public:
    int v,f,re;
    Edge (){ v=f=re=-1; }
    Edge (int _v, int _f, int _r){
      v = _v;
      f = _f;
      re = _r;
    }
  };
  int n,s,t;
	int fr,bk,que[MXN],level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n;
    s = _s;
    t = _t;
    for (int i=0; i<n; i++)
      E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB(Edge(v,f,E[v].size()));
    E[v].PB(Edge(u,0,E[u].size()-1));
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
					level[it.v] = level[u]+1;
					que[bk++] = it.v;
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
