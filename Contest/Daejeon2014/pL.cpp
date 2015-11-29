//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
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

const int MXN = 20005;
typedef pair<long long, long long> pll;
struct CostFlow {
  static const long long INF = 102938475610293847LL;
  struct Edge {
    int v, r;
    long long f, c;
  };
  int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
  long long dis[MXN], fl, cost;
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
    fl = cost = 0;
  }
  void add_edge(int u, int v, long long f, long long c) {
//    cout << "ADD EDGE " << u << " " << v << " " << f << " " << c << endl;
    E[u].PB({v, SZ(E[v])  , f,  c});
    E[v].PB({u, SZ(E[u])-1, 0, -c});
  }
  pll flow() {
    while (true) {
      for (int i=0; i<n; i++) {
        dis[i] = INF;
        inq[i] = 0;
      }
      dis[s] = 0;
      queue<int> que;
      que.push(s);
      while (!que.empty()) {
        int u = que.front(); que.pop();
        inq[u] = 0;
        for (int i=0; i<SZ(E[u]); i++) {
          int v = E[u][i].v;
          long long w = E[u][i].c;
          if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
            prv[v] = u; prvL[v] = i;
            dis[v] = dis[u] + w;
            if (!inq[v]) {
              inq[v] = 1;
              que.push(v);
            }
          }
        }
      }
      if (dis[t] == INF) break;
      long long tf = INF;
      for (int v=t, u, l; v!=s; v=u) {
        u=prv[v], l=prvL[v];
        tf = min(tf, E[u][l].f);
      }
      for (int v=t, u, l; v!=s; v=u) {
        u=prv[v], l=prvL[v];
        E[u][l].f -= tf;
        E[v][E[u][l].r].f += tf;
      }
      cost += tf * dis[t];
      fl += tf;
    }
    return {fl, cost};
  }
}flow;

struct Lisan {
  vector<long long> seq;
  void init() { seq.clear(); }
  void add(long long x) { seq.PB(x); }
  void build() {
    sort(ALL(seq));
    seq.resize(unique(ALL(seq)) - begin(seq));
  }
  int query(long long x) {
    return lower_bound(ALL(seq), x) - begin(seq);
  }
}lisan;

struct Segment {
  long long l, r, cost;
};

int N;
Segment ip[MXN];

int main() {
  IOS;
  int nT;
  cin >> nT;
  while (nT--) {
    cin >> N;
    lisan.init();
    for (int i=0; i<N; i++) {
      cin >> ip[i].l >> ip[i].r >> ip[i].cost;
      ip[i].r++;
      lisan.add(ip[i].l);
      lisan.add(ip[i].r);
    }
    lisan.build();
    int V = lisan.seq.size() + 2;
    int S = V-2;
    int T = V-1;
//    cout << "V = " << V << endl;
    flow.init(V, S, T);
    for (int i=0; i<S-1; i++) {
      flow.add_edge(i, i+1, 10, 0);
    }
    for (int i=0; i<N; i++) {
      ip[i].l = lisan.query(ip[i].l);
      ip[i].r = lisan.query(ip[i].r);
      flow.add_edge(ip[i].l, ip[i].r, 1, -ip[i].cost);
    }
    flow.add_edge(S, 0, 2, 0);
    flow.add_edge(V-3, T, 2, 0);
    long long ans = -flow.flow().S;
    cout << ans << endl;
  }

  return 0;
}

