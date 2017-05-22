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

void bye() {
  cout<<"There is no route, Karl!"<<endl;
  exit(0);
}

const int MAXN = 100005;
struct DisjoinSet {
  int conn,fa[MAXN];
  void init(int n) {
    REP(i,MAXN) fa[i] = i;
    conn = n;
  }
  int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
  void uni(int x, int y) {
    x = f(x);
    y = f(y);
    if (x == y) return;
    conn--;
    fa[y] = x;
  }
} djs;

int N,M,ind[MAXN],outd[MAXN],V,S,vst[MAXN];
vector<int> E[MAXN],rE[MAXN],path,hao[MAXN];
set<pii> edge;

bool go(int u, int step) {
  path.PB(u);
  if (step == V) {
    for (auto v:hao[u]) {
      if (v == S) return true;
    }
    path.pop_back();
    return false;
  }
  for (auto v:hao[u]) {
    if (vst[v]) continue;
    vst[v] = 1;
    if (go(v, step+1)) return true;
    vst[v] = 0;
  }
  path.pop_back();
  return false;
}
int is2(int x) {
  return ind[x] == 1 and outd[x] == 1;
}
bool trivial() {
  REP1(i,1,N) if (!is2(i)) return false;
  if (djs.conn == 1) return true;
  return false;
}
int main() {
#ifndef HAO123
  FILEIO("king");
#endif
  IOS;
  cin>>N>>M;
  djs.init(N);
  REP(_,M) {
    int u,v;
    cin>>u>>v;
    if (u == v) continue;
    if (edge.count(pii(u,v))) continue;
    E[u].PB(v);
    rE[v].PB(u);

    ind[v]++;
    outd[u]++;
    edge.insert(pii(u,v));
    djs.uni(u,v);
  }

  REP1(i,1,N) {
    if (ind[i] == 0 or outd[i] == 0) bye();
  }

  if (trivial()) {
    cout<<1;
    int u =1;
    REP(_,N) {
      u = E[u][0];
      cout<<" "<<u;
    }
    cout<<endl;
    return 0;
  }

  djs.init(N);
  REP1(i,1,N) {
    if (!is2(i)) continue;
    if (djs.f(i) != i) continue;
    int x = i;
    int y = i;
    while (is2(E[x][0])) x = E[x][0];
    while (is2(rE[y][0])) y = rE[y][0];

    for (int j=y; j!=x; j=E[j][0]) {
      djs.uni(E[j][0], j);
    }
  }

  S = 0;
  V = 0;
  REP1(i,1,N) if (djs.f(i) == i) {
    S = i;
    V++;
  }

  REP1(i,1,N) {
    if (djs.f(i) != i) continue;
    for (auto j:E[i]) {
      hao[i].PB(djs.f(j));
    }
    sort(ALL(hao[i]));
    hao[i].resize(unique(ALL(hao[i]))-begin(hao[i]));
    //cout<<i<<" "<<hao[i]<<endl;
  }
  vst[S] = 1;
  if (!go(S, 1)) {
    //cout<<"NOT FOUND"<<endl;
    bye();
  }
  //cout<<"PATH = "<<path<<endl;
  vector<int> ans,vec;
  for (auto it:path) {
    int u = it;
    vec.clear();
    while (true) {
      vec.PB(u);
      int ok = 0;
      for (auto v:rE[u]) {
        if (djs.f(v) == djs.f(u)) {
          u = v;
          ok = 1;
          break;
        }
      }
      if (!ok) break;
    }
    reverse(ALL(vec));
    ans.insert(end(ans),ALL(vec));
  }
  assert(find(ALL(ans),1) != end(ans));
  rotate(begin(ans), find(ALL(ans),1), end(ans));
  REP(i,N) cout<<ans[i]<<" ";
  cout<<ans[0]<<endl;

  assert(SZ(ans) == N);
  ans.PB(ans[0]);
  REP(i,N) {
    vst[ans[i]] = 1;
    assert(edge.count(pii(ans[i],ans[i+1])));
  }
  REP1(i,1,N) assert(vst[i]);

  return 0;
}

