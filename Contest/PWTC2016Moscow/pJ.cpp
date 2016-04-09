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

const int MXN = 500005;

int N,M;
pii ans;
pii best[MXN], bestRev[MXN];
vector<pii> E[MXN];
string str;

int tot=0;
void update_suf(pii a[], pii v) {
  if (v < a[0]) {
    a[1] = a[0];
    a[0] = v;
  } else if (v < a[1]) {
    a[1] = v;
  }
}
void DFS(int u, int f) {
  tot++;
  best[u] = {-1,u};
  bestRev[u] = {M,u};
  vector<pii> v1;

  pii v2[2];
  v2[0] = v2[1] = {M,u};

  for (auto it:E[u]) {
    int v = it.F;
    int c = it.S;
    if (v == f) continue;
    DFS(v,u);
    int prev = best[v].F;
    if (prev < M-1 and c == str[prev+1]) {
      if (prev+1 > best[u].F) {
        best[u] = best[v];
        best[u].F++;
      }
      v1.PB({prev+1,v});
    } else {
      if (best[v] > best[u]) best[u] = best[v];
      v1.PB({prev,v});
    }
    int sufv = bestRev[v].F;
    if (sufv > 0 and c == str[sufv-1]) {
      if (sufv-1 < bestRev[u].F) {
        bestRev[u] = bestRev[v];
        bestRev[u].F--;
      }
      update_suf(v2,{sufv-1,v});
    } else {
      if (bestRev[v] < bestRev[u]) bestRev[u] = bestRev[v];
      update_suf(v2,{sufv,v});
    }
  }
  //cout << u << " ,FA=" << f << " " << best[u] << " " << bestRev[u] << endl;
  //cout << v1 << endl;
  //cout << v2[0] << " " << v2[1] << endl;

  if (bestRev[u].F == 0) {
    ans.F = u;
    ans.S = bestRev[u].S;
    //cout << "UPDATE " << u << endl;
  }
  for (auto pre:v1) {
    int pl = pre.F;
    int pv = pre.S;
    REP(i,2) {
      int pu = v2[i].S;
      if (pu == pv) continue;
      if (pl >= v2[i].F-1) {
        ans.F = best[pv].S;
        ans.S = bestRev[pu].S;
        if (pv == u) ans.F = u;
        if (pu == u) ans.S = u;
        //cout << "UPDATE " << pv << " " << pu << endl;
      }
      break;
    }
  }

}
void check(int u, int f, int m) {
  if (u == ans.S) {
    assert(m == M);
    return;
  }
  for (auto it:E[u]) {
    int v = it.F;
    int c = it.S;
    if (v == f) continue;
    int x = m;
    if (m < M and str[m] == c) x++;
    check(v,u,x);
  }
}
int main() {
  IOS;
  cin >> N >> M;
  REP(i,N-1) {
    int u,v;
    string c;
    cin >> u >> v >> c;
    E[u].PB({v,c[0]});
    E[v].PB({u,c[0]});
  }
  cin >> str;
  ans = {-1,-1};
  DFS(1,1);
  cout << ans.F << " " << ans.S << endl;
  if (ans.F != -1) {
    check(ans.F,ans.F,0);
  }

  return 0;
}

