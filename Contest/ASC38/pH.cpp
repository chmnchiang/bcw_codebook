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

const int MX = 33;
int N;
string name[MX];
int wins[MX];
int deg[MX];
int fig[MX][MX];

struct Isap{
  static const int MXN = 10000;
  struct Edge{ int v,f,re; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,0,SZ(E[u])-1});
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
    while (h[s] < n) res += DFS(s,2147483647);
    return res;
  }
}flow;

bool check(int a, int k) {
	//cout << a << ' ' << k << endl;
	int S = N;
	int T = N + 1;
	int V = N + 2;
	flow.init(V, S, T);

	int neg_tot = 0;
	for (int i=0; i<N; i++) {
		if (i == a) continue;
		int c = 2*k - 2*wins[i] - (deg[i] - fig[a][i]);
			//cout << "I " << i << endl;
		if (c >= 0) {
			flow.add_edge(i, T, c);
		} else {
			flow.add_edge(S, i, -c);
			neg_tot += c;
		}
	}

	for (int i=0; i<N; i++) {
		if (i == a) continue;
		for (int j=0; j<N; j++) {
			if (j == a) continue;

			flow.add_edge(i, j, fig[i][j]);
		}
	}

	int f = flow.flow();
	int res = f + neg_tot;
	if (res < 0) return false;
	else return true;
}

bool vt[MX];
vector<int> ans;
void dfs(int v = N) {
	vt[v] = true;
	if (v != N) ans.PB(v);
	for (auto ed : flow.E[v]) {
		if (!ed.f) continue;
		if (vt[ed.v]) continue;

		dfs(ed.v);
	}
}

int main() {
	FILEIO("high");
	IOS;

	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> name[i] >> wins[i];
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> fig[i][j];
			deg[i] += fig[i][j];
		}
	}

	for (int i=0; i<N; i++) {
		int k = wins[i] + deg[i];
		if (check(i, k)) {
			cout << name[i] << " can win" << endl;
		} else {
			ans.clear();
			FZ(vt);
			dfs();
			cout << name[i] << " cannot win because of the following teams:" << endl;
			cout << "  ";
			for (int j=0; j<SZ(ans); j++) {
				cout << name[ans[j]] << (j == SZ(ans)-1 ? "\n" : ", ");
			}
		}
	}

	return 0;
}
