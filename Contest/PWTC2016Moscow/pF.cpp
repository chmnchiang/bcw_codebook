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

const int MX = 500005;
const int SQ = 1400;
const int LOG = 17;

struct Query {
  int l,r,bid,qid;
}qry[MX];

struct BIT {
  int bit[MX];
  int lb(int x) { return x & -x; }
  void add(int p, int v) {
    for (int i=p; i<MX; i+=lb(i))
      bit[i] += v;
  }
  int qry() {
    int v = 0;
    for (int i=LOG-1; i>=0; i--) {
      if (!bit[v | (1<<i)]) v += 1<<i;
    }
    return v+1;
  }
}bit;

int fa[LOG][MX],dep[MX];
int N,Q,val[MX],app[MX];
int st[MX],ed[MX];
int step,seq[MX*2];
int ans[MX];
int cnt[MX];
vector<pii> E[MX];

inline void add(int x) {
  if (x > 100005) return;
  //cout << "ADD " << x << endl;
  if (cnt[x] == 0) bit.add(x+1,-1);
  cnt[x]++;
}
inline void sub(int x) {
  if (x > 100005) return;
  //cout << "SUB " << x << endl;
  cnt[x]--;
  if (cnt[x] == 0) bit.add(x+1,1);
}
inline int findLCA(int u, int v) {
  if (dep[u] > dep[v]) swap(u,v);
  int diff = dep[v] - dep[u];
  REP(i,LOG) {
    if (!diff) break;
    if (diff & (1<<i)) {
      diff -= 1<<i;
      v = fa[i][v];
    }
  }
  if (u == v) return u;
  for (int i=LOG-1; i>=0; i--) {
    if (fa[i][u] != fa[i][v]) {
      u = fa[i][u];
      v = fa[i][v];
    }
  }
  return fa[0][u];
}
void DFS(int u, int f, int d) {
  dep[u] = d;
  fa[0][u] = f;
  seq[++step] = u;
  st[u] = step;
  for (auto it:E[u]) {
    int v = it.F;
    if (v == f) continue;
    val[v] = it.S;
    DFS(v,u,d+1);
  }
  seq[++step] = u;
  ed[u] = step;
}

int ev;
int ap2[MX],a2[MX];
int chans;
void check(int u, int f) {
  if (u == ev) {
    REP(i,MX) if (!ap2[i]) {
      chans = i;
      return;
    }
  }
  for (auto it:E[u]) {
    if (it.F == f) continue;
    if (it.S < MX) ap2[it.S]++;
    check(it.F,u);
    if (it.S < MX) ap2[it.S]--;
  }
}
int main() {
  IOS;
  cin >> N >> Q;
  REP(_,N-1) {
    int u,v,x;
    cin >> u >> v >> x;
    E[u].PB({v,x});
    E[v].PB({u,x});
  }
  val[1] = 1e9;
  step = 0;
  DFS(1,1,0);

  REP1(i,1,LOG-1) REP1(j,1,N)
    fa[i][j] = fa[i-1][fa[i-1][j]];

  REP1(i,1,Q) {
    int u,v;
    cin >> u >> v;

    //ev = v;
    //check(u,u);
    //a2[i] = chans;

    int l = st[u];
    int r = st[v];
    if (l > r) swap(l,r);
    qry[i] = {l,r,int(l/SQ),i};
  }

  sort(qry+1,qry+1+Q, [](Query a, Query b) {
      if (a.bid == b.bid) return a.r < b.r;
      return a.bid < b.bid;
      });

  REP1(i,0,N) {
    bit.add(i+1,1);
  }

  //REP1(i,1,step) cout << seq[i] << " ";
  //cout << endl;
  

  int l = 1, r = 1;
  app[seq[1]]++;
  add(val[seq[1]]);

  REP1(i,1,Q) {
    int ql = qry[i].l;
    int qr = qry[i].r;
    //cout << ql << " " << qr << endl;
    while (r < qr) {
      r++;
      int v = seq[r];
      app[v]++;
      if (app[v] == 1) add(val[v]);
      else sub(val[v]);
    }
    while (l > ql) {
      l--;
      int v = seq[l];
      app[v]++;
      if (app[v] == 1) add(val[v]);
      else sub(val[v]);
    }
    while (r > qr) {
      int v = seq[r--];
      app[v]--;

      if (app[v] == 1) add(val[v]);
      else sub(val[v]);
      
    }
    while (l < ql) {
      int v = seq[l++];
      app[v]--;
      if (app[v] == 1) add(val[v]);
      else sub(val[v]);
      
    }
    int v = seq[l];
    int flag = 0;
    if (app[v] != 1) {
      flag = 1;
      add(val[v]);
    }
    int lca = findLCA(seq[ql],seq[qr]);
    int flag2 = 0;
    if (app[lca] == 1) {
      flag2 = 1;
      sub(val[lca]);
    }

    ans[qry[i].qid] = bit.qry() - 1;
    if (flag) {
      sub(val[v]);
    }
    if (flag2) {
      add(val[lca]);
    }
  }


  REP1(i,1,Q) {
    //cout << a2[i] << " " << ans[i] << endl;
   //assert(ans[i] == a2[i]);
   cout << ans[i] << "\n";
  }

  return 0;
}

