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

struct BIT {
  int bit[MX];
  int lb(int x) { return x & -x; }
  void add(int p, int v) {
    p++;
    for (int i=p; i<MX; i+=lb(i))
      bit[i] += v;
  }
  int qry() {
    int v = 0;
    for (int i=1<<LOG; i>0; i>>=1) {
      if ((v|i) < MX and bit[v|i]==i) v |= i;
    }
    return v;
  }
}bit;

struct Query {
  int l,r,qid;
}qry[MX];
struct Edge {
  int v,x;
};

int N,Q,timestamp[MX],ans[MX];
int in[MX],cnt[MX];
vector<Edge> E[MX];
vector<Edge> seq;

void DFS(int u, int f) {
  timestamp[u] = SZ(seq);
  for (auto it:E[u]) {
    if (it.v == f) continue;
    seq.PB(it);
    DFS(it.v,u);
    seq.PB(it);
  }
}
void poke(int id) {
  int v = seq[id].v;
  int x = seq[id].x;
  in[v] ^= 1;
  cnt[x] += in[v] ? 1 : -1;
  if (in[v] and cnt[x] == 1) bit.add(x, 1);
  if (!in[v] and cnt[x] == 0) bit.add(x, -1);
}
int main() {
  IOS;
  cin >> N >> Q;
  REP(_,N-1) {
    int u,v,x;
    cin >> u >> v >> x;
    x = min(x,N);
    E[u].PB({v,x});
    E[v].PB({u,x});
  }
  DFS(1,1);
  REP1(i,1,Q) {
    int u,v;
    cin >> u >> v;
    int l = timestamp[u], r = timestamp[v];
    if (l > r) swap(l,r);
    r--;
    qry[i] = {l,r,i};
  }
  sort(qry+1,qry+1+Q, [](Query a, Query b) {
      return make_pair(a.l/SQ,a.r) < make_pair(b.l/SQ,b.r);
      });

  int curL = 1, curR = 0;
  REP1(i,1,Q) {
    int ql=qry[i].l,qr=qry[i].r;
    while (curL > ql) poke(--curL);
    while (curR < qr) poke(++curR);
    while (curL < ql) poke(curL++);
    while (curR > qr) poke(curR--);
    ans[qry[i].qid] = bit.qry();
  }

  REP1(i,1,Q) {
    cout << ans[i] << "\n";
  }

  return 0;
}

