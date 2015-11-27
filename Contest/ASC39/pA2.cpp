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

const int MAXE = 1805;
const int MAXN = 35;
const double inf = 1029384756;
const double eps = 1e-6;
struct Edge {
  int v,u,f;
  double c;
};
int n,m,prv[MAXN][MAXN], prve[MAXN][MAXN], vst[MAXN];
Edge e[MAXE];
vector<int> edgeID, cycle;
double d[MAXN][MAXN];
inline void bellman_ford() {
  for(int i=0; i<n; i++) d[0][i]=0;
  for(int i=0; i<n; i++) {
    fill(d[i+1], d[i+1]+n, inf);
    for(int j=0; j<m; j++) {
      if (e[j].f <= 0) continue;
      int v = e[j].v, u = e[j].u;
      if(d[i][e[j].v]<inf && d[i+1][u]>d[i][v]+e[j].c) {
        d[i+1][u] = d[i][v]+e[j].c;
        prv[i+1][u] = v;
        prve[i+1][u] = j;
      }
    }
  }
}
double karp_mmc() {
  // returns inf if no cycle, mmc otherwise
  double mmc=inf;
  int st = -1;
  bellman_ford();
  for(int i=0; i<n; i++) {
    double avg=-inf;
    for(int k=0; k<n; k++) {
      if(d[n][i]<inf-eps)	avg=max(avg,(d[n][i]-d[k][i])/(n-k));
      else avg=max(avg,inf);
    }
    if (avg < mmc) {
      mmc = avg;
      st = i;
    }
  }
  FZ(vst); edgeID.clear(); cycle.clear();
  vector<int> rho;
  for (int i = st, lv = n; !vst[i]; i = st = prv[lv--][i]) {
    vst[i] = 1;
    rho.PB(lv);
    rho.PB(i);
  }
  while (vst[st] != 2) {
    int v = rho.back(); rho.pop_back();
    int lv = rho.back(); rho.pop_back();
    edgeID.PB(prve[lv][v]);
    cycle.PB(v);
    vst[v]++;
  }

  return mmc;
}

const int MXN = 35;

int N, M;

int main() {
  IOS;
  FILEIO("arbitrage");
  cin >> N >> M;
  for (int i=0, u, v, a, c; i<M; i++) {
    cin >> u >> v >> a >> c;
    u--; v--;
    e[2*i] = {u, v, c, 1.*-a};
    e[2*i+1] = {v, u, 0, 1.*a};
  }
  long long ans = 0;
  while (true) {
    n = N;
    m = M*2;
    double mmc = karp_mmc();
    if (mmc >= 0) break;
    int nf = 1029384756;
    int c = 0;
    for (auto id : edgeID) {
      nf = min(nf, e[id].f);
      c += e[id].c;
    }
    for (auto id : edgeID) {
      e[id].f -= nf;
      e[id^1].f += nf;
    }
    ans += nf * c;
  }
  ans = -ans;
  cout << ans << endl;

  return 0;
}

