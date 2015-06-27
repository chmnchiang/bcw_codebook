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

typedef pair<long long, int> pii;
typedef long long LL;

const int MX = 514;
const LL INF = 1ll << 62;

int N,M,C,prv[MX],done[MX];
pii eg[MX][MX];
LL dis[MX];

int main(){
  FILEIO("gas");
  cin >> N >> M >> C;
  for (int i=1; i<=N; i++)
    for (int j=1; j<=N; j++)
      eg[i][j] = MP(INF,0);
  for (int i=1; i<=M; i++){
    int u,v,w;
    cin >> u >> v >> w;
    if (eg[u][v].F > w)
      eg[u][v] = eg[v][u] = MP(w, i);
  }
  for (int i=1; i<=N; i++){
    dis[i] = INF;
    done[i] = 0;
    prv[i] = 0;
  }
  dis[1] = 0;
  for (int t=1; t<=N; t++){
    int u = 0;
    LL best = INF;
    for (int v=1; v<=N; v++){
      if (!done[v] && dis[v] < best){
        u = v;
        best = dis[v];
      }
    }
    if (u == 0) break;
    done[u] = 1;
    for (int v=1; v<=N; v++){
      if (!done[v] && dis[v] > dis[u] + eg[u][v].F){
        dis[v] = dis[u] + eg[u][v].F;
        prv[v] = u;
      }
    }
  }
  LL w = 0;
  vector<int> vec;
  int cur = N;
  while (prv[cur] != 0){
    int p = prv[cur];
    w += eg[p][cur].F;
    vec.PB(eg[p][cur].S);
    cur = p;
  }
  LL c = 1;
  if (dis[N] != INF) c = C;
  else c = 0;
  if (w < c){
    cout << "Unfair\n";
    cout << vec.size() << endl;
    sort(vec.begin(), vec.end());
    int x = vec.size();
    for (int i=0; i<x; i++){
      cout << vec[i];
      if (i == x-1) cout << endl;
      else cout << " ";
    }
  } else {
    cout << "Fair" ;
  }

	return 0;
}

