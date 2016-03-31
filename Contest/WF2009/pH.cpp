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

typedef pair<int,int> pii;
const int MXN = 205;
struct Scc{
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    FZ(vst);
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    FZ(vst);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
  bool can(int st, int ed) {
	REP(i,n) vst[i] = 0;
	queue<int> que;
	que.push(st);
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto v:E[u]) {
			if (vst[v]) continue;
			if (v == ed) return true;
			vst[v] = 1;
			que.push(v);
		}
	}
	return false;
  }
}scc;

int N,M;

inline int id(pii x) {
	return x.S ? x.F : x.F+N;
}
inline char check(int x) {
	int y = x+N;
	int xy = scc.can(x,y);
	int yx = scc.can(y,x);
	assert(!(xy and yx));
	if (!xy and !yx) return '?';
	if (xy) return 'n';
	return 'y';
}
int main() {
	IOS;
	int cas = 0;
	while (true) {
		cin >> N >> M;
		if (N == 0 and M == 0) break;
		scc.init(2*N);
		REP(i,M) {
			int m;
			cin >> m;
			vector<pii> vec;
			REP(j,m) {
				int v;
				string yn;
				cin >> v >> yn;
				vec.PB({v-1,yn[0] == 'y' ? 1 : 0});
			}
			if (m <= 2) {
				REP(j,m) {
					pii x = vec[j];
					pii y = vec[j];
					y.S ^= 1;
					scc.add_edge(id(y),id(x));
				}
			} else {
				REP(j,m) {
					pii y = vec[j];
					y.S ^= 1;
					REP(k,m) {
						if (j == k) continue;
						pii x = vec[k];
						scc.add_edge(id(y),id(x));
					}
				}
			}
		}
		scc.solve();
		int fail = 0;
		REP(i,N) {
			if (scc.bln[i] == scc.bln[i+N]) {
				fail = 1;
				break;
			}
		}

		cas++;
		cout << "Case " << cas << ": ";
		if (fail) {
			cout << "impossible" << endl;
		} else {
			REP(i,N) cout << check(i);
			cout << endl;
		}
	}

	return 0;
}

