//a34021501 {{{
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

#ifdef HAO123
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef HAO123
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif
// }}}
// Let's Fight! !111111111!

struct Dinic{
  static const int MXN = 2000000;
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
    for (int i=0; i<n; i++) level[i] = -1;
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
} flow;

const int MAXN = 205;
const ll MAX = 200005;
const ll MOD = 987777733;
const ll MUL = 331;
const ll MOD2 = 999991921;
//const ll MOD = 100000000;
//const ll MUL = 100;
ll pw[MAX], pw2[MAX];

struct Hasher {
  vector<ll> h,h2;
  void build(const string &s) {
    int n = SZ(s);
    h.resize(n+1);
    h2.resize(n+1);
    h[0] = 0;
    h2[0] = 0;
    REP(i,n) {
      h[i+1] = (h[i] * MUL + s[i]) % MOD;
      h2[i+1] = (h2[i] * MUL + s[i]) % MOD2;
    }
  }
  pll qry(int l, int r) {
    r++;
    ll res = h[r] - h[l] * pw[r-l] % MOD;
    if (res < 0) res += MOD;
    ll res2 = h2[r] - h2[l] * pw2[r-l] % MOD2;
    if (res2 < 0) res2 += MOD2;
    return pll(res, res2);
  }
} hs[MAXN];

int N, len[MAXN];
string ip[MAXN];
vector<pll> vec[MAXN],all;

bool check(int k) {
  all.clear();
  int goal = 0;
  REP(i,N) {
    vec[i].clear();
    int l = k;
    if (l > len[i]) l = len[i];
    REP(j,SZ(ip[i])) {
      if (j + l - 1 >= SZ(ip[i])) break;
      pll h = hs[i].qry(j, j+l-1);
      vec[i].PB(h);
    }
    sort(ALL(vec[i]));
    vec[i].resize(unique(ALL(vec[i]))-begin(vec[i]));
    //dump(i,vec[i]);
    if (SZ(vec[i]) < N) {
      all.insert(end(all), ALL(vec[i]));
      goal++;
    }
  }

  sort(ALL(all));
  all.resize(unique(ALL(all))-begin(all));

  int V = N+SZ(all)+2;
  int S = V-2;
  int T = V-1;

  flow.init(V,S,T);

  REP(i,SZ(all)) {
    flow.add_edge(i+N,T,1);
  }
  
  REP(i,N) {
    if (SZ(vec[i]) >= N) continue;
    flow.add_edge(S,i,1);
    for (auto it:vec[i]) {
      int id = lower_bound(ALL(all),it) - begin(all);
      flow.add_edge(i, id+N, 1);
    }
  }

  int f = flow.flow();
  return f == goal;
}
int main() {
  IOS;
  cin>>N;
  REP(i,N) {
    cin>>ip[i];
    len[i] = SZ(ip[i]);
    ip[i] += ip[i];
    hs[i].build(ip[i]);
  }

  pw[0] = pw2[0] = 1;
  REP1(i,1,MAX-1) {
    pw[i] = pw[i-1] * MUL % MOD;
    pw2[i] = pw2[i-1] * MUL % MOD2;
  }

  int l = 0, r = MAX;

  while (l < r) {
    int m = (l + r) / 2;
    if (check(m)) r = m;
    else l = m + 1;
  }
  //assert(l != MAX);
  cout<<l<<endl;

  return 0;
}

