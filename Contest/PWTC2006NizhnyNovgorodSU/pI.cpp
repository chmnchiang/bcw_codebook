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

const int MV = 1010101;
const int INF = 1029384756;

struct DisjointSet {
  int fa[25];
  void init() {
    REP(i,25) fa[i] = i;
  }
  int f(int x) { return fa[x] == x ? x : fa[x]=f(fa[x]); }
  void uni(int x, int y) { fa[f(y)] = f(x); }
} djs;
struct Edge {
  int u, v, c, id, ru, rv, nc;
};


int add[MV];
using pii = pair<int, int>;
struct Graph {
  int n;
  vector<Edge> el[25];
  int E[25][25];
  vector<pii> states;
  static const int MX = (1<<20);
  int dp[MX];
  int bk[MX];
  bool state_ok[MX], state_vis[MX];
  int state_val[MX];
  int tdeg[25];

  void init(int _n) {
    n = _n;
    REP(i,n) el[i].clear();
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) E[i][j] = 0;
    }

    states.clear();
    int m = (1<<n);
    for (int i=0; i<m; i++) {
      dp[i] = -INF;
      bk[i] = -1;
    }
    dp[0] = 0;
  }

  void add_edge(int u, int v, int c, int id) {
    el[u].PB({u,v,c,id});
    el[v].PB({v,u,c,id});
    E[u][v] ++;
    E[v][u] ++;
  }

  void dfs(int st, int val)
  {
    if(state_vis[st]) return;
    state_vis[st] = true;
    state_ok[st] = true;
    state_val[st] = val + 2;
    for(int i=0; i<n; i++)
    {
      if((1<<i)&st) continue;
      int tote = tdeg[i];
      if(st && !tote) continue;
      if(tote >= 2) state_ok[st] = false;
      int nst = st | (1<<i);
      if(state_vis[nst]) continue;
      for(int j=0; j<n; j++)
        tdeg[j] += E[i][j];
      dfs(nst, val + tote);
      for(int j=0; j<n; j++)
        tdeg[j] -= E[i][j];
    }
  }

  void make_state()
  {
    int m = (1<<n);
    for(int i=0; i<m; i++)
    {
      state_ok[i] = state_vis[i] = false;
      state_val[i] = 0;
    }
    for(int i=0; i<n; i++)
      tdeg[i] = 0;
    dfs(0, 0);

    for(int i=1; i<m; i++)
      if(state_ok[i])
        states.PB({i, state_val[i]});
  }

  void solve() {
    // calc for add[]
    int m = (1<<n);
    make_state();

    for (int i=1; i<m; i++) {
      for (auto r: states) {
        if (r.F > i) continue;
        if ((r.F|i) != i) continue;
        int l = i^r.F;
        if (dp[i] < dp[l] + r.S) {
          dp[i] = dp[l] + r.S;
          bk[i] = l;
        }
      }
    }

    vector<vector<int>> grp;
    int color[25] = {};
    int ns = m-1;
    while (ns) {
      int b = bk[ns];
      int c = b^ns;
      vector<int> res;
      for (int i=0; i<n; i++) {
        if ((1<<i) & c) {
          res.PB(i);
        }
      }
      grp.PB(res);
      ns = b;
    }

    for(int i=0; i<n; i++)
      for(auto e: el[i])
        add[e.id] = 0;

    DisjointSet dj;

    for(int i=0; i<SZ(grp); i++)
      for(auto x: grp[i])
        color[x] = i;

    for (int i=0; i<SZ(grp); i++) {
      dj.init();

      for (auto u: grp[i]) {
        for (auto e: el[u]) {
          int v = e.v;
          if (color[u] != color[v]) continue;
          if (dj.f(u) == dj.f(v)) continue;
          int id = e.id;
          add[id] = -1;
          dj.uni(u, v);
        }
      }
    }

    dj.init();
    for (int i=0; i<n; i++) {
      for (auto e: el[i]) {
        int u = e.u, v = e.v, id = e.id;
        if(u > v) continue;

        int cu = color[u], cv = color[v];
        if (cu == cv) continue;
        if (dj.f(cu) == dj.f(cv))
        {
          add[id] = 1;
          continue;
        }
        dj.uni(cu, cv);
      }
    }
  }
}G;

int V, E;
vector<Edge> el[MV];

void calc(int weight) {
  if (el[weight].empty()) return;

  vector<int> seq;
  REP(i,V) seq.PB(djs.f(i));
  sort(ALL(seq));
  seq.resize(unique(ALL(seq))-begin(seq));
  int n = SZ(seq);
  vector<int> edge[25];
  int vst[25], inq[25];
  REP(i,V) vst[i] = 1, inq[i] = 0;

  for (auto &it:el[weight]) {
    it.ru = lower_bound(ALL(seq),djs.f(it.u))-begin(seq);
    it.rv = lower_bound(ALL(seq),djs.f(it.v))-begin(seq);
    edge[it.ru].PB(it.rv);
    edge[it.rv].PB(it.ru);
    vst[it.ru] = vst[it.rv] = 0;
  }

  REP(i,n) {
    if (vst[i]) continue;
    REP(j,n) inq[j] = 0;
    vector<int> que;
    int fr = 0;
    que.PB(i);
    vst[i] = 1;
    while (fr < SZ(que)) {
      int u = que[fr++];
      for (auto v:edge[u]) {
        if (vst[v]) continue;
        vst[v] = 1;
        que.PB(v);
      }
    }

    sort(ALL(que));
    for (auto it:que) inq[it] = 1;
    G.init(SZ(que));

    for (auto it:el[weight]) {
      if (inq[it.ru] and inq[it.rv]) {
        int u = lower_bound(ALL(que),it.ru)-begin(que);
        int v = lower_bound(ALL(que),it.rv)-begin(que);
        int c = it.c;
        if (u == v) continue;
        G.add_edge(u,v,c,it.id);
      }
    }

    G.solve();
  }

  for (auto it:el[weight]) {
    djs.uni(it.u, it.v);
  }
}

int main() {
  cin >> V >> E;

  for (int i=0; i<E; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    u--; v--;
    el[c].PB({u, v, c, i, u, v, c});
  }

  djs.init();
  REP(i,MV) {
    calc(i);
  }

  vector<Edge> op;
  REP(i,MV) {
    op.insert(op.end(),ALL(el[i]));
  }
  sort(ALL(op), [](Edge a, Edge b) { return a.id < b.id; });

  int ans = 0;
  REP(i,E) {
    ans += abs(add[i]);
    op[i].nc = op[i].c + add[i];
  }

  cout << ans << endl;
  for (auto it:op) cout << it.u+1 << " " << it.v+1 << " " << it.nc << endl;

  return 0;
}
