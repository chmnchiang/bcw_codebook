//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

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

typedef long long LL;
typedef pair<LL,LL> pii;
const int MX = 100005;

int N,ip[MX], fa[MX];
LL faE[MX];
LL dp1[MX], dp2[MX];
LL sumD[MX], tot;
vector<pii> E[MX];
LL ans, cost;

LL go1(int u);
LL go2(int u);

LL DFS(int u, int f){
  LL ret = ip[u];
  fa[u] = f;
  for (auto it : E[u]){
    if (f == it.F){
      faE[u] = it.S;
      continue;
    }
    ret += DFS(it.F, u);
  }
  return sumD[u] = ret;
}
LL go2(int u){
  if (u == 1) return 0;
  if (dp2[u] != -1) return dp2[u];
  int f = fa[u];
  LL ret = go1(f) + go2(f) - go1(u) - sumD[u] * faE[u] + (tot - sumD[u]) * faE[u];
  return dp2[u] = ret;
}

LL go1(int u){
  if (dp1[u] != -1) return dp1[u];
  LL ret = 0;
  for (auto it : E[u]){
    if (it.F == fa[u]) continue;
    int v = it.F;
    ret += go1(v) + sumD[v] * it.S;
  }
  return dp1[u] = ret;
}

int main(){
  IOS;
  FILEIO("house");
  cin >> N;
  for (int i=1; i<=N; i++){
    dp1[i] = dp2[i] = -1;
    cin >> ip[i];
  }
  for (int i=1, u, v, w; i<=N-1; i++){
    cin >> u >> v >> w;
    E[u].PB(MP(v,w));
    E[v].PB(MP(u,w));
  }
  DFS(1,1);
  tot = sumD[1];
  cost = 1ll << 62;
  for (int i=1; i<=N; i++){
    LL tmp = go1(i) + go2(i);
   // cout << "# " << i << " : " << go1(i) << " " << go2(i) << " " << tmp << endl;
    if (tmp < cost){
      cost = tmp;
      ans = i;
    }
  }
  cout << ans << " " << cost << endl;
  
	return 0;
}

