//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

struct Point{/*{{{*/
  typedef ll T;
  T x, y;
  
  Point() : x(0), y(0) {}
  Point(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const Point &b) const{
    return tie(x,y) < tie(b.x,b.y);
  }
  bool operator == (const Point &b) const{
    return tie(x,y) == tie(b.x,b.y);
  }
  Point operator + (const Point &b) const{
    return Point(x+b.x, y+b.y);
  }
  Point operator - (const Point &b) const{
    return Point(x-b.x, y-b.y);
  }
  T operator * (const Point &b) const{
    return x*b.x + y*b.y;
  }
  T operator % (const Point &b) const{
    return x*b.y - y*b.x;
  }
  Point operator * (const T &b) const{
    return Point(x*b, y*b);
  }
  T abs(){
    return sqrt(abs2());
  }
  T abs2(){
    return x*x + y*y;
  }
};/*}}}*/

struct Dinic{/*{{{*/
  static const int MXN = 105;
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
    fill(level,level+n,-1);
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
  vector<int> get_sol() {
    vector<int> res;
    queue<int> que;
    que.push(s);
    fill(level,level+n,0);
    level[s] = 1;
    while (!que.empty()) {
      int u = que.front(); que.pop();
      for (auto it:E[u]) {
        if (it.f <= 0) continue;
        if (level[it.v]) continue;
        que.push(it.v);
        level[it.v] = 1;
        res.PB(it.v);
      }
    }
    return res;
  }
}flow;/*}}}*/

int N,D;
Point pt[105];
pii p;
int mx;
vector<int> ans;

void solve(int i, int j, int saveFlag=0) {
  ll K = (pt[i]-pt[j]).abs2();
  vector<int> v1,v2;
  REP(k,N) {
    if (k == i or k == j) continue;
    if ((pt[k]-pt[i]).abs2() <= K and (pt[k]-pt[j]).abs2() <= K) {
      if ((pt[k]-pt[i]) % (pt[j] - pt[i]) >= 0) v1.PB(k);
      else v2.PB(k);
    }
  }

  int V = SZ(v1) + SZ(v2) + 2;
  if (!saveFlag and V <= mx) return;
  int S = V-2;
  int T = V-1;
  flow.init(V,S,T);
  REP(k,SZ(v1)) {
    int x = v1[k];
    REP(l,SZ(v2)) {
      int y = v2[l];
      if ((pt[x]-pt[y]).abs2() > K) {
        flow.add_edge(k,l+SZ(v1),1);
      }
    }
  }
  REP(k,SZ(v1)) flow.add_edge(S,k,1);
  REP(l,SZ(v2)) flow.add_edge(l+SZ(v1),T,1);
  int f = flow.flow();
  int res = SZ(v1) + SZ(v2) - f + 2;
  if (res >= mx) {
    if (!saveFlag) {
      mx = res;
      p = {i,j};
    } else {
      vector<int> bye;
      bye.resize(SZ(v2));
      fill(ALL(bye),0);
      vector<int> vec;
      for (auto it:flow.get_sol()) {
        if (it < SZ(v1)) vec.PB(v1[it]);
        else bye[it-SZ(v1)] = 1;
      }
      REP(k,SZ(v2)) {
        if (bye[k]) continue;
        vec.PB(v2[k]);
      }
      vec.PB(i);
      vec.PB(j);
      assert(res == SZ(vec));
      sort(ALL(vec));
      if (SZ(vec) > SZ(ans)) {
        ans = vec;
      }
    }
  }
}
int main() {
  IOS;
  cin >> N >> D;
  REP(i,N) cin >> pt[i].x >> pt[i].y;
  mx = 1;
  ans.PB(0);
  ll D2 = D * D;
  REP(i,N) {
    REP(j,i) {
      ll K = (pt[i]-pt[j]).abs2();
      if (K > D2) continue;
      solve(i,j);
    }
  }
  if (mx > 1) solve(p.F,p.S,1);
  cout << SZ(ans) << endl;
  REP(i,SZ(ans)) cout << ans[i]+1 << " ";
  cout << endl;

  return 0;
}

