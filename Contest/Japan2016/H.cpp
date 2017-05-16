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

typedef pair<pii, int> ppi;

const int MAXN = 1010101;
const int INF = 1029384756;

struct Graph {
  int n,s,t,gg,dp[MAXN];
  int ins[MAXN];
  vector<int> stk;
  vector<pii> E[MAXN];
  void init(int tn, int a, int b) {
    n = tn;
    s = a;
    t = b;
    REP1(i,0,n) E[i].clear();
  }
  void add_edge(int u, int v, int x) {
    //cout<<u<<" "<<v<<" "<<xendl;
    E[u].PB({v,x});
  }

  int go(int u) {
    if (u == t) return 0;
    if (dp[u] != -1) return dp[u];
    ins[u] = 1;
    stk.PB(u);
    dp[u] = 0;

    for (auto it:E[u]) {
      int v = it.F;
      int x = it.S;
      if (dp[v] != -1 and ins[v]) {
        gg = 1;
        return -INF;
      }
           
      dp[u] = max(dp[u], go(v)+x);
    }

    ins[u] = 0;
    stk.pop_back();

    return dp[u];
  }

  int solve() {
    stk.clear();
    REP1(i,0,n) {
      ins[i] = 0;
      dp[i] = -1;
    }
    gg = 0;
    int res = go(s);
    if (gg) return -INF;
    return res;
  }
} graph;

int N, M, V;
map<pii, int> vmp;
vector<pii> vout[MAXN], vin[MAXN];
vector<ppi> es;

int get_node(pii p)
{
  if(vmp.count(p)) return vmp[p];
  else return vmp[p] = V++;
}

int main() {
  IOS;

  while(cin>>N>>M)
  {
    V = 0;
    vmp.clear();
    es.clear();
    for(int i=0; i<N; i++)
    {
      vout[i].clear();
      vin[i].clear();
    }

    for(int i=0; i<N; i++)
    {
      get_node({i, -1});
      vin[i].PB({i, -1});
    }
    for(int i=0; i<M; i++)
    {
      int x, y, w;
      cin>>x>>y>>w;
      x--;
      y--;
      get_node({x, i});
      get_node({y, i});
      vin[x].PB({x, i});
      vin[y].PB({y, i});
      vout[x].PB({y, i});
      if(w == 2)
        vout[y].PB({x, i});
    }

    for(int i=0; i<V; i++)
    {
      int sz = SZ(vout[i]);
      if(sz == 0) continue;
      map<int, int> emp;
      for(int j=0; j<sz; j++)
        emp[vout[i][j].S] = j;

      vector<int> lft, rgt;
      for(int j=0; j<sz; j++)
      {
        lft.PB(V++);
        rgt.PB(V++);
      }
      for(int j=0; j<sz; j++)
      {
        int x = get_node(vout[i][j]);
        es.PB({{lft[j], x}, 0});
        es.PB({{rgt[j], x}, 0});
        if(j > 0) es.PB({{lft[j], lft[j-1]}, 0});
        if(j < sz-1) es.PB({{rgt[j], rgt[j+1]}, 0});
      }

      for(auto p: vin[i])
      {
        int x = get_node(p);
        int e = p.S;
        if(!emp.count(e))
        {
          es.PB({{x, rgt[0]}, 1});
        }
        else
        {
          int j = emp[e];
          if(j > 0) es.PB({{x, lft[j-1]}, 1});
          if(j < sz-1) es.PB({{x, rgt[j+1]}, 1});
        }
      }
    }

    int SS = V++;
    int TT = V++;
    for(int i=0; i<N; i++)
    {
      for(auto x: vin[i])
      {
        int v = get_node(x);
        es.PB({{SS, v}, 0});
        es.PB({{v, TT}, 0});
      }
    }

    graph.init(V, SS, TT);
    for(auto p: es)
      graph.add_edge(p.F.F, p.F.S, p.S);

    int ans = graph.solve();
    if(ans == -INF)
      cout<<"Infinite"<<endl;
    else
      cout<<ans<<endl;
  }

  return 0;
}

