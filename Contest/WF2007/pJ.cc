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
#define ALL(x) x.begin(),x.end()
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#define SZ(x) ((int)(x).size())
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=a; (i)<(b); (i)++
#define range(...) _MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__)

#ifdef DEBUG
#define debug(a) cout << #a << " = " << a << endl;
#endif
template<typename T>
ostream& operator << (ostream &o, vector<T> &vec) {
    cout << "[";
    for (int i=0; i<SZ(vec); i++) {
        if (i) cout << ", ";
        cout << vec[i];
    }
    cout << "]";
    return o;
}

template<typename T1, typename T2>
ostream& operator << (ostream &o, pair<T1, T2> &pair) {
    cout << "(" << pair.F << ", " << pair.S << ")";
    return o;
}

struct Isap{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
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
    FZ(h); FZ(gap);
    gap[0] = n;
    while (h[s] < n) res += DFS(s,2147483647);
    return res;
  }
}flow;

const int MX = 55;
int V, E;
int el[MX][MX];
typedef pair<int, int> pii;
vector<pii> el2[MX];
vector<int> del;
bool isd[MX];
int ans[MX];

const int INF = 1029384756;

int calc(int v) {

    flow.init(V, v, 0);
    for (int i=0; i<V; i++) {
        if (isd[i]) continue;
        for (auto x: el2[i]) {
            if (isd[x.F]) continue;
            flow.add_edge(i, x.F, x.S);
            //cout << i << ' ' << x.F << endl;
        }
    }

    return flow.flow();
}

int solve() {
    V++;
    for (int i=0; i<=V; i++) {
        fill(el[i], el[i]+V+1, 0);
        el2[i].clear();
    }
    del.clear();
    fill(isd, isd+V+1, false);
    fill(ans, ans+V+1, 0);

    for (int i=0; i<E; i++) {
        int u, v; cin >> u >> v;
        el[u][v]++;
        el[v][u]++;
    }

    for (int i=0; i<V; i++)
        for (int j=0; j<V; j++) {
            if (el[i][j]) {
                el2[i].PB({j, el[i][j]});
            }
        }
    
    //cout << 123 << endl;

    /*
    for (int i=0; i<V; i++) {
        for (auto x: el2[i]) {
            cout << x.F << "(" << x.S << ") ";
        } cout << endl;
    }*/

    fill(ans, ans+V+1, INF);
    
    int nmv = 0;
    for (int i=1; i<V; i++) {
        int bs = -1, bv = INF;
        for (int j=1; j<V; j++) {
            if (isd[j]) continue;
            int t = calc(j);
            ans[j] = min(ans[j], nmv+t);
            if (ans[j] < bv) {
                bv = ans[j];
                bs = j;
            }
        }
        //cout << bs << ' ' << bv << endl;
        del.PB(bs);
        isd[bs] = true;
        nmv = max(nmv, bv);
    }

    return ans[1];
}

int main() {

    int cas = 0;
    while (true) {
        cin >> V >> E;

        if (not V and not E) break;

        cas++;
        int a = solve();
        cout << "Case " << cas << ": " << a << endl;
        cout << endl;
    }

    return 0;
}

