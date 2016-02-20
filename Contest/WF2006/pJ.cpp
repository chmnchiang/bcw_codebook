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

const int MXN = 105;
const int INF = 1e6;

int N,M,dis[MXN][MXN],dp[MXN][MXN];
int inq[MXN][MXN];

void init_all() {
  REP(i,MXN) {
    REP(j,MXN) {
      dis[i][j] = dp[i][j] = INF;
      inq[i][j] = 0;
    }
    dis[i][i] = 0;
  }
}
void input() {
  REP(i,M) {
    int u,v;
    cin >> u >> v;
    u--; v--;
    dis[u][v] = 1;
  }
}
void predo() {
  REP(k,N) REP(i,N) REP(j,N)
    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}
void check(int x, int y, int c, queue<int> &que) {
  if (dp[x][y] > c) {
    dp[x][y] = c;
    if (!inq[x][y]) {
      que.push(x);
      que.push(y);
      inq[x][y] = 1;
    }
  }
}
void solve() {
  //REP(i,N) {
    //REP(j,N)
      //cout << dis[i][j] << " ";
    //cout << endl;
  //}
  queue<int> que;
  check(0, 0, 0, que);
  while (!que.empty()) {
    int a = que.front(); que.pop();
    int b = que.front(); que.pop();
    inq[a][b] = 0;
    if (a != b) {
      check(b, a, dp[a][b]+dis[b][a]-1, que);
      check(a, a, dp[a][b]+dis[b][a]-1, que);
      check(b, b, dp[a][b]+dis[b][a]-1, que);
    }
    REP(i,N) {
      // walk a
      check(i, b, dp[a][b]+dis[i][a], que);
      // walk b
      check(a, i, dp[a][b]+dis[b][i], que);
    }
  }

  if (dp[1][1] == INF) {
    // .............. capitalize will get WA
    cout << "Impossible\n";
  } else {
    int ans = 1 + dp[1][1];
    cout << "Minimum number of nodes = " << ans << "\n";
  }
}
int main(int argc, char** argv) {
  int cas = 0;
  IOS;
  while (cin >> N >> M) {
    if (not N and not M) break;
    cas++;
    cout << "Network " << cas << "\n";
    init_all();
    input();
    predo();
    solve();
    cout << endl;
  }

  return 0;
}

