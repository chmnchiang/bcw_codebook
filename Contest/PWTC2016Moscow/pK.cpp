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

#define loop(i, a, b) for (auto (i)=(a); (i)!=(b); ((i) += ((a) < (b) ? 1 : -1)))
int V, E;
const int MX = 502020;
vector<int> el[MX];
int deg[MX];
vector<int> ans;

bool vt[MX];
int forb;
bool dfs(int u, int fa) {
  if (u == forb) return false;
  if (vt[u]) return true;
  vt[u] = 1;
  for (auto v: el[u]) {
    if (v == fa) continue;
    if (dfs(v, u)) return true;
  }
  return false;
}

bool calc(int v) {
  loop (i, 0, V+3) vt[i] = 0;
  forb = v;
  loop (i, 1, V+1) {
    if (vt[i]) continue;
    if (dfs(i,-1)) return true;
  }
  return false;
}

void solve() {
  vector<int> mxd;
  int mv = 0;
  bool all2 = 1;
  loop (i, 1, V+1) {
    if (deg[i] % 2) return;

    if (deg[i] > mv) {
        mxd.clear();
        mv = deg[i];
    }
    if (deg[i] == mv) {
      mxd.PB(i);
    }
    all2 &= (deg[i] == 2);
  }
  if (all2) {
    loop (i, 1, V+1) ans.PB(i);
    return;
  }

  if (SZ(mxd) > 2) return;
  for (auto x: mxd) {
    if (not calc(x)) ans.PB(x);
  }

}

int main() {
  IOS;
  cin>>V>>E;
  
  loop (i, 0, E) {
    int a, b; cin>>a>>b;
    el[a].PB(b);
    el[b].PB(a);
    deg[a] ++;
    deg[b] ++;
  }

  solve();
  sort(ALL(ans));
  cout << SZ(ans) << endl;
  for (auto x: ans) {
    cout << x << ' ';
  }
  cout << endl;

  return 0;
}

