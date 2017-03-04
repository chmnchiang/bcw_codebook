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

const int MXN = 105;
using pii = pair<int,int>;

int N,vst[MXN],edge[MXN][MXN];
int ans[MXN*MXN][3];
vector<pii> path;

void DFS(int u) {
  if (vst[u]) return;
  REP1(v,1,N) {
    if (!edge[u][v]) continue;
    if (edge[u][v]) {
      edge[u][v] = 0;
      DFS(v);
      path.PB({v,u});
    }
  }
}

int main() {
  IOS;
  cin >> N;
  REP1(i,1,N) {
    REP1(j,1,N) edge[i][j] = 1;
    edge[i][i] = 0;
  }
  DFS(1);
  vector<int> vec;
  vec.PB(path[0].F);
  for (auto it:path)
    vec.PB(it.S);
//  cout << vec << endl;
  int sz = SZ(vec);
  for (int i=0; i<sz; i++) ans[i][0] = vec[i];
  ans[sz-1][0] = 0;
  for (int i=0; i<sz; i++) ans[i][1] = vec[i];
  ans[0][2] = 0;
  for (int i=1; i<sz; i++) ans[i][2] = vec[i-1];

  for (int i=0; i<sz; i++)
    cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << "\n";

  return 0;
}
