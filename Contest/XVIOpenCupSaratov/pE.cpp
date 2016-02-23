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
#define int long long

const int MXN = 100005;
struct Answer {
  int u,v;
  double d,t;
  Answer () : u(0), v(0), d(0), t(1e17) {}
  void update(int tu, int tv, double td, double tt) {
    if (tt < t) {
      tie(u, v, d, t) = tie(tu, tv, td, tt);
    }
  }
};

int N,C,S,ip[MXN],dis[MXN],isp[MXN],sz[MXN];
int fr,bk,que[MXN],fa[MXN];
vector<pii> edge[MXN], ct[MXN];
Answer ans;

void DFS1(int u, int f, int d, int vid) {
  dis[u] = d;
  ct[vid].PB({d, ip[u]});
  for (auto it:edge[u]) {
    if (it.F == f) continue;
    DFS1(it.F, u, d+it.S, vid);
  }
}
ll calc_time(vector<pii>& v) {
  ll curt = 0;
  ll curc = 0;
  sort(ALL(v));
  for (auto it:v) {
    int nt = it.F, c = it.S;
    if (nt <= curt) {
      curc += c;
    } else {
      curt = nt;
      curc = c;
    }
    curt += curc / C;
    curc %= C;
  }
  if (curc) curt++;
  return curt;
}
int calc_point(int cen) {
//  cout << "CALC POINT " << cen << endl;
  ll t = 0;
  ll from = 0;
  for (auto it:edge[cen]) {
    int v=it.F, d=it.S;
    ct[v].clear();
    DFS1(v, cen, 0, v);
    ll tmp = calc_time(ct[v]) + d;
//    cout << ct[v] << " " << tmp << endl;
    if (tmp > t) {
      t = tmp;
      from = v;
    }
  }
//  cout << "CALC POINT " << cen << " " << t << " FROM " << from << endl;
  ans.update(cen, cen, 0, t);
  return from;
}
void calc_edge(int x, int y, int d) {
  ct[x].clear();
  DFS1(x, y, 0, x);
  ct[y].clear();
  DFS1(y, x, 0, y);
  ll tx = calc_time(ct[x]);
  ll ty = calc_time(ct[y]);
  double td = abs(tx-ty);
  if (abs(tx-ty) >= d) return;
  if (tx <= ty) {
    td += (d - td) * 0.5;
  } else {
    td = (d - td) * 0.5;
  }
  ans.update(x, y, td, tx+td);
}
void DFS(int u, int f, vector<int>& vec) {
  vec.PB(u);
  for (auto it:edge[u]) {
    if (it.F == f || !isp[it.F]) continue;
    DFS(it.F, u, vec);
  }
}
void solve(vector<int> vec) {
  for (auto v:vec) {
    isp[v] = 1;
    fa[v] = v;
  }
  if (vec.empty()) return;
  if (SZ(vec) == 1) {
    calc_point(vec[0]);
    return;
  }
  fr = bk = 0;
  que[bk++] = vec[0];
  while (fr < bk) {
    int u = que[fr++];
    for (auto it:edge[u]) {
      int v=it.F;
      if (v == fa[u] || !isp[v]) continue;
      fa[v] = u;
      que[bk++] = v;
    }
  }
  int tot = SZ(vec);
  int cen = -1;
  int cost = 1e9;
  for (int i=bk-1; i>=0; i--) {
    int u = que[i];
    sz[u] = 1;
    int tc = 0;
    for (auto it:edge[u]) {
      int v=it.F;
      if (v == fa[u] || !isp[v]) continue;
      sz[u] += sz[v];
      tc = max(tc, sz[v]);
    }
    tc = max(tc, tot-sz[u]);
    if (tc < cost) {
      cen = u;
      cost = tc;
    }
  }
  assert(cen != -1);
  int nxt = calc_point(cen);
  for (auto it:edge[cen]) {
    if (it.F == nxt)
      calc_edge(cen, nxt, it.S);
  }
  if (!isp[nxt]) return;
  vector<int> nxtvec;
  DFS(nxt, cen, nxtvec);
  for (auto v:vec) isp[v] = 0;
  solve(nxtvec);
}
int32_t main() {
  IOS;
  cin >> N >> C >> S;
  REP1(i,1,N) cin >> ip[i];
  REP1(i,1,N-1) {
    int u,v,d;
    cin >> u >> v >> d;
    d *= S;
    edge[u].PB({v,d});
    edge[v].PB({u,d});
  }
  /*
  REP1(i,1,N) calc_point(i);
  REP1(u,1,N) {
    for (auto it:edge[u]) {
      calc_edge(u, it.F, it.S);
    }
  }
  */
  vector<int> vec;
  REP1(i,1,N) {
    vec.PB(i);
    isp[i] = 0;
  }
  solve(vec);
  ans.d /= S;
  if (ans.u == ans.v) cout << ans.u << endl;
  else cout << fixed << setprecision(10) << ans.u << " " << ans.v << " " << ans.d << endl;
//  cout << ans.t << endl;

  return 0;
}

