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

const int MXN = 200005;
const int LOG = 18;

int N;
int root,fa[LOG][MXN],dep[MXN];
vector<int> E[MXN];

void init(){
  root = 1;
  for (int i=1; i<=N; i++){
    E[i].clear();
    fa[0][i] = 0;
  }
}
void BFS(int st){
  int fr=0;
  vector<int> que;
  dep[st] = 0;
  fa[0][st] = st;
  que.PB(st);
  while (fr < (int)que.size()){
    int u = que[fr++];
    for (auto v : E[u]){
      if (fa[0][v] != 0) continue;
      fa[0][v] = u;
      dep[v] = dep[u] + 1;
      que.PB(v);
    }
  }
}
int up(int u, int step){
  for (int i=0; step && i<LOG; i++){
    if (step & 1){
      u = fa[i][u];
    }
    step >>= 1;
  }
  return u;
}
int findLCA(int u, int v){
  if (dep[u] > dep[v]) swap(u,v);
  v = up(v, dep[v]-dep[u]);
  if (u == v) return u;
  for (int i=LOG-1; i>=0; i--){
    if (fa[i][u] != fa[i][v]){
      u = fa[i][u];
      v = fa[i][v];
    }
  }
  return fa[0][u];
}
int dis(int u, int v){
  int lca = findLCA(u,v);
  return dep[u] - dep[lca] + dep[v] - dep[lca];
}
int walk(int u, int v, int step){
  int lca = findLCA(u,v);
  int d = dep[u] - dep[lca] + dep[v] - dep[lca];
  if (d <= step) return v;
  if (dep[u] - dep[lca] >= step){
    return up(u, step);
  } else {
    return up(v, d-step);
  }
}
int solve(int u, int v){
  if (dis(u,root) > dis(v,root)) swap(u, v);
  v = walk(v, u, dis(v,root) - dis(u,root));
  if (u == v) return u;
  int l = 0, r = N;
  while (l < r){
    int mid = (l+r) / 2;
    if (walk(u,root,mid) == walk(v,root,mid)) r = mid;
    else l = mid+1;
  }
  return walk(u,root,l);
}
int main(){
  IOS;
  FILEIO("dynamic");
  while (cin >> N && N){
    init();
    for (int i=1,u,v; i<=N-1; i++){
      cin >> u >> v;
      E[u].PB(v);
      E[v].PB(u);
    }
    BFS(1);
    for (int i=1; i<LOG; i++){
      for (int j=1; j<=N; j++){
        fa[i][j] = fa[i-1][fa[i-1][j]];
      }
    }
    int Q;
    cin >> Q;
    while (Q--){
      string cmd;
      cin >> cmd;
      if (cmd == "?"){ // query
        int u, v;
        cin >> u >> v;
        cout << solve(u,v) << "\n";
      } else if (cmd == "!"){ // change root
        cin >> root;
      }
    }
  }
	return 0;
}

