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

typedef pair<int,int> pii;
const int MXN = 100005;

int N,M,ip[MXN],dp[MXN], ind[MXN], done[MXN];
vector<int> E[MXN];

void init(){
  for (int i=1; i<=N; i++){
    E[i].clear();
    dp[i] = -1;
    ind[i] = 0;
    done[i] = -1;
  }
}
int f(int x){
  if (dp[x] != -1) return dp[x];
  int ret = ip[x];
  for (auto v : E[x]){
    ret = min(ret, f(v));
  }
  return dp[x] = ret;
}
int main(){
  IOS;
  FILEIO("grand");
  while (cin >> N && N){
    init();
    for (int i=1; i<=N; i++) cin >> ip[i];
    cin >> M;
    for (int i=1,x,y; i<=M; i++){
      cin >> x >> y;
      E[x].PB(y);
      ind[y]++;
    }
    priority_queue<pii, vector<pii>> pq;
    for (int i=1; i<=N; i++){
      if (ind[i] == 0){
        pq.push(MP(-f(i),i));
      }
    }
    for (int i=1; i<=N; i++){
      pii ret = pq.top();
      pq.pop();
      int u = ret.S;
      done[u] = i;
      for (auto v : E[u]){
        ind[v]--;
        if (ind[v] == 0){
          pq.push(MP(-f(v),v));
        }
      }
    }
    vector<pii> vec;
    int ans = 0;
    for (int i=1; i<=N; i++){
      ans = max(ans, max(0,done[i]-ip[i]));
      vec.PB(MP(done[i],i));
    }
    sort(vec.begin(), vec.end());
    cout << ans << "\n";
    for (int i=0; i<N; i++){
      cout << vec[i].S << (i==N-1 ? "\n" : " ");
    }
  }

	return 0;
}

