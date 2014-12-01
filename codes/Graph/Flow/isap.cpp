class Isap{
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
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n;
    s = _s;
    t = _t;
    for (int i=0; i<n; i++)
      E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u]._PB(Edge(v,f,E[v].size()));
    E[v]._PB(Edge(u,f,E[u].size()-1));
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf;
        nf -= tf;
        it.f -= tf;
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
    _SZ(h);
    _SZ(gap);
    gap[0] = n;
    while (h[s] < n)
      res += DFS(s,2147483647);
    return res;
  }
}flow;
