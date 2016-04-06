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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

#define int long long

const int INF = 11234567890123456LL;
struct Isap{
  static const int MXN = 10000;
  struct Edge{ int v,f,re,id; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void dump() {
	  loop (i, 0, n) {
		  cout << i << ": ";
		  for(auto x:E[i]) cout << x.v << ' ';
		  cout << endl;
	  }
  }
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f, int id){
	 
    E[u].PB({v,f,SZ(E[v]), -1});
    E[v].PB({u,0,SZ(E[u])-1, id});

	int uu = (v >= n/2 ? v-n/2 : v+n/2), 
		vv = (u >= n/2 ? u-n/2 : u+n/2);
    E[uu].PB({vv,f,SZ(E[vv]), -1});
    E[vv].PB({uu,0,SZ(E[uu])-1, id});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (nf){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  int flow(int res=0){
    FZ(h); FZ(gap);
    gap[0] = n;
    while (h[s] < n) res += DFS(s,INF);
    return res;
  }
}flow;

int N, M;
const int MX = 111111;
int ans[MX];
int32_t main() {
	IOS;
	FILEIO("transportation");

	cin>>N>>M;

	flow.init(N*2, 0, N);

	const int MAG = 10000;
	loop (i, 0, M) {
		int u, v;
		double f;
		cin >> u >> v >> f;
		u--; v--;
		int _f = round(f*MAG);
		flow.add_edge(u, v, _f, i);
	}
	//flow.dump();
	cout << fixed << setprecision(10);
	cout << 1.0 / MAG * flow.flow() << endl;
	loop (i, 0, N*2) {
		for (auto e: flow.E[i]) {
			if (e.id != -1) {
				ans[e.id] += e.f;
			}
		}
	}
	loop (i, 0, M) {
		 cout << (0.5 * ans[i] / MAG) << " \n"[i == M-1];
	}


	return 0;
}
