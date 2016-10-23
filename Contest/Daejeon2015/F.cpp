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


const int MXN = 200005;
struct Scc{
	int n, nScc, vst[MXN], bln[MXN], prv[MXN];
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
		REP(i,n) vst[i] = 0;
		for (int i=0; i<n; i++)
			if (!vst[i]) DFS(i);
		reverse(vec.begin(),vec.end());
		REP(i,n) vst[i] = 0;
		for (auto v : vec){
			if (!vst[v]){
				rDFS(v);
				nScc++;
			}
		}
	}
	vector<int> get_path(int st, int ed) {
		queue<int> que;
		REP(i,n) vst[i] = 0;
		que.push(st);
		vst[st] = 1;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (auto v:E[u]) {
				if (vst[v]) continue;
				que.push(v);
				prv[v] = u;
				vst[v] = 1;
			}
		}
		assert(vst[ed]);
		vector<int> res;
		int v = ed;
		while (v != st) {
			res.PB(v);
			v = prv[v];
		}
		res.PB(v);
		reverse(ALL(res));
		return res;
	}
}G;

int at[MXN];

int main() {
	IOS;
	int T;
	cin >> T;
	while(T--) {
		int N,M;
		cin >> N >> M;
		G.init(2*N);
		REP(i,M) {
			int u,v;
			cin >> u >> v;
			u--;
			v--;
			G.add_edge(u, v+N);
			G.add_edge(u+N, v);
		}
		G.solve();
		vector<int> cyc;
		REP(i,N) {
			if (G.bln[i] == G.bln[i+N]) {
				cyc = G.get_path(i, i+N);
			}
		}
		if (cyc.empty()) cout << "-1" << endl;
		else {
			cout << "1" << endl;
			REP(i,N) at[i] = -1;
			vector<int> ans;
			int sz = SZ(cyc);
			for (int i=0; i<sz; i++) {
				int v = cyc[i] % N;
				if (at[v] == -1) {
					at[v] = i;
				} else {
					for (int j=at[v]; j<i; j++)
						ans.PB(cyc[j]%N+1);
					break;
				}
			}
			cout << SZ(ans) << "\n";
			for (auto i:ans) cout << i << "\n";
		}
	}

	return 0;
}

