#include<bits/stdc++.h>/*{{{*/
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
}/*}}}*/
// Let's Fight!


typedef array<int,3> Arr;
typedef pair<int,int> pii;

struct KM{
  // Maximum Bipartite Weighted Matching (Perfect Match)
  static const int MXN = 405;
  static const int INF = 2147483647; // long long
  int n,match[MXN],vx[MXN],vy[MXN];
  int edge[MXN][MXN],lx[MXN],ly[MXN],slack[MXN];
  // ^^^^ long long
  void init(int _n){
    n = _n;
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        edge[i][j] = 0;
  }
  void add_edge(int x, int y, int w){ // long long
    edge[x][y] = w;
  }
  bool DFS(int x){
    vx[x] = 1;
    for (int y=0; y<n; y++){
      if (vy[y]) continue;
      if (lx[x]+ly[y] > edge[x][y]){
        slack[y] = min(slack[y], lx[x]+ly[y]-edge[x][y]);
      } else {
        vy[y] = 1;
        if (match[y] == -1 || DFS(match[y])){
          match[y] = x;
          return true;
        }
      }
    }
    return false;
  }
  int solve(){
    fill(match,match+n,-1);
    fill(lx,lx+n,-INF);
    fill(ly,ly+n,0);
    for (int i=0; i<n; i++)
      for (int j=0; j<n; j++)
        lx[i] = max(lx[i], edge[i][j]);
    for (int i=0; i<n; i++){
      fill(slack,slack+n,INF);
      while (true){
        fill(vx,vx+n,0);
        fill(vy,vy+n,0);
        if ( DFS(i) ) break;
        int d = INF; // long long
        for (int j=0; j<n; j++)
          if (!vy[j]) d = min(d, slack[j]);
        for (int j=0; j<n; j++){
          if (vx[j]) lx[j] -= d;
          if (vy[j]) ly[j] += d;
          else slack[j] -= d;
        }
      }
    }
    int res=0;
    for (int i=0; i<n; i++)
      res += edge[match[i]][i];
    return res;
  }
}graph;

ostream& operator << (ostream &s, Arr a) {
  return s << "(" << a[0] << "," << a[1] << "," << a[2] <<")";
}

int N,M,K,S;
int tian[25][25];
pii human[405];
vector<Arr> choose[405];
vector<pii> v1,v2;
int match[405];
int idx[25][25];
int ban[25][25];
int at[405];
int ok[405];

int main() {
  FILEIO("agrarian");
  IOS;
  cin >> N >> M >> K >> S;
  REP1(i,1,N) REP1(j,1,M) {
    tian[i][j] = 1;
  }
  REP1(i,1,K) {
    cin >> human[i].F >> human[i].S;
    tian[human[i].F][human[i].S] = 0;
  }
  REP(_,S) {
    int a,b;
    cin >> a >> b;
    tian[a][b] = 0;
  }

  REP1(i,1,K) {
    int x = human[i].F;
    int y = human[i].S;
    REP1(j,1,N) REP1(k,1,M) {
      if (!tian[j][k]) continue;
      Arr c;
      c[0] = abs(x-j)+abs(y-k);
      c[1] = j;
      c[2] = k;
      choose[i].PB(c);
    }
    sort(ALL(choose[i]));
  }

  REP1(i,1,N) REP1(j,1,M) {
    if (tian[i][j]) {
      idx[i][j] = SZ(v2);
      v2.PB({i,j});
    }
  }
  REP1(i,1,K) {
    int x = human[i].F, y = human[i].S;
    idx[x][y] = SZ(v1);
    v1.PB({x,y});
  }

  const int MAG = 100000;
  graph.init(SZ(v2));
  for (auto x:v1) for (auto y:v2) {
    int a = x.F;
    int b = x.S;
    int c = y.F;
    int d = y.S;
    int cost = abs(a-c)+abs(b-d);
    graph.add_edge(idx[a][b],idx[c][d],MAG-cost);
  }

  int tot = graph.solve();
  tot = MAG*SZ(v1) - tot;
  cerr << tot << endl;

  REP(i,SZ(v2)) {
    if (graph.match[i] < SZ(v1)) {
      int j = graph.match[i];
      match[j] = i;
    }
  }

  vector<pii> vec;
  REP1(i,1,K) {
    int m = match[i-1];
    int fail = 1;
    REP(j,SZ(choose[i])) {
      if (choose[i][j][1] == v2[m].F and choose[i][j][2] == v2[m].S) {
        at[i] = j;
        fail = 0;
        break;
      }
    }
    assert(!fail);
  }

  REP1(i,1,N) REP1(j,1,M) ban[i][j] = 0;
  REP1(i,1,K) {
    //cerr << i << " " << at[i] << " " << choose[i] << endl;
    int x = choose[i][at[i]][1];
    int y = choose[i][at[i]][2];
    ban[x][y] = 1;
  }

  vector<int> ans;
  REP1(i,1,K) {
    int best = 0;
    REP1(j,1,K) {
      if (ok[j]) continue;
      best = j;
      REP(k,at[j]) {
        int x = choose[j][k][1];
        int y = choose[j][k][2];
        if (ban[x][y]) {
          best = 0;
          break;
        }
      }
      if (best) break;
    }
    assert(best);
    ok[best] = 1;
    ans.PB(best);
    int x = choose[best][at[best]][1];
    int y = choose[best][at[best]][2];
    ban[x][y] = 0;
  }

  for (auto it:ans) cout << it << " ";
  cout << endl;

  int realtot = 0;
  for (auto i:ans) {
    for (auto it:choose[i]) {
      int x = it[1];
      int y = it[2];
      if (!ban[x][y]) {
        realtot += it[0];
        ban[x][y] = 1;
        break;
      }
    }
  }
  cerr << "REAL = " << realtot << endl;
  assert(realtot == tot);

  return 0;
}
