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

/* genB can hack some codes ! */

typedef pair<int,int> pii;
const int MAXN = 100005;

int deg[MAXN], col[MAXN];
set<int> E[MAXN];
vector<int> leafSon[MAXN];
set<int> s;
vector<int> c2v[MAXN];
priority_queue<pii, vector<pii>> pq;

void init(){
  FZ(deg);
  s.clear();
}
void add_son(int v){
  for (auto f : E[v]){
    if (s.count(f)){
      leafSon[f].PB(v);
      pq.push(MP(deg[f], f));
      break;
    }
  }
}
int get_top(){
  while (true){
    assert(!pq.empty());
    int f = pq.top().S;
    if (pq.top().F != deg[f]){
      pq.pop();
      continue;
    }
    pq.pop();
    return f;
  }
}
void set_col(int v, int c){
  c2v[c].PB(v);
  col[v] = c;
}
void swap_col(int u, int v){
  int d = 0;
  for (auto &it : c2v[col[u]])
    if (it == u) it = v, d++;
  for (auto &it : c2v[col[v]])
    if (it == v) it = u, d++;
  assert(d == 2);
  swap(col[u], col[v]);
}
pii solve(int N){
  if (N == 2){
    int c = 1;
    for (auto v : s){
      set_col(v,c);
      c++;
    }
    return MP(1,2);
  }
  int f1 = get_top();
  int v1 = leafSon[f1].back();
  leafSon[f1].pop_back();
  int f2 = get_top();
  while (f1 == f2)
    f2 = get_top();
  int v2 = leafSon[f2].back();
  leafSon[f2].pop_back();
  
  s.erase(v1); s.erase(v2);
  for (auto it : E[v1]) deg[it]--;
  for (auto it : E[v2]) deg[it]--;
  for (auto it : E[v1]){
    if (s.count(it) && deg[it] == 1){
      add_son(it);
    }
  }
  for (auto it : E[v2]){
    if (s.count(it) && deg[it] == 1){
      add_son(it);
    }
  }
  if (leafSon[f1].size()){
    pq.push(MP(deg[f1], f1));
  }
  if (leafSon[f2].size()){
    pq.push(MP(deg[f2], f2));
  }
  pii tmp = solve(N-2);
  int c = N/2 + 1;
  if (col[f1] != col[f2]){
    set_col(v1, c);
    set_col(v2, c);
    return tmp;
  } else {
    if (tmp.F == tmp.S){
      set_col(v1, tmp.F);
      set_col(v2, c);
      return MP(tmp.S, c);
    } else {
      int u = c2v[tmp.F][0];
      if (E[u].count(f2)){
        swap(f1,f2);
        swap(v1,v2);
      }
      if (E[u].count(f1)){
        set_col(v1, c);
        swap_col(v1, f1);
        set_col(v2, tmp.F);
      } else {
        set_col(v1, tmp.F);
        set_col(v2, c);
      }
      return MP(tmp.S, c);
    }
  }
}

int main(){
  int N;
  IOS;
  FILEIO("bicoloring");
  cin>>N;
  init();
  for (int i=1; i<=N; i++)
    s.insert(i);
  for (int i=1, u, v; i<=N-1; i++){
    cin >> u >> v;
    E[u].insert(v);
    E[v].insert(u);
    deg[u]++;
    deg[v]++;
  }
  for (int i=1; i<=N; i++){
    if (deg[i] == 1){
      add_son(i);
    }
  }
  solve(N);
  for (int i=1; i<=N; i++)
    cout << col[i] << (i == N ? "\n" : " "); 

  return 0;
}

