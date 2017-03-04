#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
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
}
// Let's Fight!

#define int long long
const int MX = 555555;
int djs[MX];
int ans[MX];
int cs[MX];
int need[MX];
int V, E;

struct Edge {
  int u, v, w;
  bool operator < (const Edge &e) const {
    return w < e.w;
  }
};

int ffa(int a) {
  return (djs[a] == a ? a : (djs[a] = ffa(djs[a])));
}

int32_t main() {
  IOS;  

  cin >> V >> E;
  int a = 0;
  for (int i=1; i<=V; i++) {
    cin >> need[i] >> cs[i];
    ans[i] = need[i] * cs[i];
    a += ans[i];
    djs[i] = i;
  }
  int A = a;

  vector<Edge> ed;

  for (int i=0; i<E; i++) {
    int u, v, w; cin >> u >> v >> w;
    ed.PB({u, v, w});
  }
  sort(ALL(ed));

  int Z = V;
  for (int i=0; i<E; i++) {
    if (Z == 1) break;

    auto &e = ed[i];
    int u = e.u, v = e.v, w = e.w;

    int fu = ffa(u), fv = ffa(v);
    if (fu == fv) continue;

    a -= ans[fu];
    a -= ans[fv];

    djs[fv] = fu;
    cs[fu] = min(cs[fu], cs[fv]);
    need[fu] = max(need[fu], need[fv]);
    need[fu] = max(need[fu], w);
    ans[fu] = min(need[fu] * cs[fu], ans[fu] + ans[fv]);
    a += ans[fu];
    A = min(a, A);

    Z--;
  }

  cout << A << endl;

  return 0;
}
