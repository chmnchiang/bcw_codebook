class Scc{
public:
	int n,vst[MAXN];
	int nScc,bln[MAXN];
	vector<int> E[MAXN], rE[MAXN], vc;
	void init(int _n){
		n = _n;
		for (int i=0; i<MAXN; i++){
			E[i].clear();
			rE[i].clear();
		}
	}
	void add_edge(int u, int v){
		E[u]._PB(v);
		rE[v]._PB(u);
	}
	void DFS(int u){
		vst[u]=1;
		FOR(it,E[u]){
			if (!vst[*it])
				DFS(*it);
		}
		vc._PB(u);
	}
	void rDFS(int u){
		vst[u] = 1;
		bln[u] = nScc;
		FOR(it,rE[u]){
			if (!vst[*it])
				rDFS(*it);
		}
	}
	void solve(){
		nScc=0;
		vc.clear();
		_SZ(vst);
		for (int i=0; i<n; i++){
			if (!vst[i])
				DFS(i);
		}
		reverse(vc.begin(),vc.end());
		_SZ(vst);
		FOR(it,vc){
			if (!vst[*it]){
				rDFS(*it);
				nScc++;
			}
		}
	}
};
