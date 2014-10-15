#define N 256 // max vertex num
class Graph { public:
	// n,g[i][j]=0/1, match() => match: (i,mate[i]) (or mate[i]=-1)
	int n, mate[N];
	bool g[N][N], inQ[N], inBlo[N];
	queue<int> Q;
	int start, newBase, prev[N], base[N];
	int lca(int u, int v) {
		bool path[N] = { false };
		while(true) {
			u = base[u]; path[u] = true;
			if(u == start) break;
			u = prev[mate[u]];
		}
		while(true) {
			v = base[v];
			if(path[v]) break;
			v = prev[mate[v]];
		}
		return v;
	}
	void trace(int u) {
		while(base[u] != newBase) {
			int v = mate[u];
			inBlo[base[u]] = inBlo[base[v]] = true;
			u = prev[v];
			if(base[u] != newBase) prev[u] = v;
		}
	}
	void contract(int u, int v) {
		newBase = lca(u, v);
		memset(inBlo, false, sizeof(inBlo));
		trace(u); trace(v);
		if(base[u] != newBase) prev[u] = v;
		if(base[v] != newBase) prev[v] = u;
		for(int i = 0; i < n; i++)
			if(inBlo[base[i]]) {
				base[i] = newBase;
				if(!inQ[i]) { Q.push(i); inQ[i] = true; }
			}
	}
	bool search() {
		memset(inQ, false, sizeof(inQ));
		memset(prev, -1, sizeof(prev));
		for(int i = 0; i < n; i++) base[i] = i;
		while(!Q.empty()) Q.pop();
		Q.push(start); inQ[start] = true;
		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			for(int i = 0; i < n; i++)
				if(g[u][i] && base[u] != base[i] && mate[u] != i){
					if(i == start || (mate[i] >= 0 && prev[mate[i]] >= 0)) contract(u, i);
					else if(prev[i] < 0) {
						prev[i] = u;
						if(mate[i] != -1) { Q.push(mate[i]); inQ[mate[i]] = true; }
						else { augment(i); return true; }
					}
				}
		}
		return false;
	}
	void augment(int u) {
		while(u >= 0) {
			int v = prev[u], w = mate[v];
			mate[v] = u; mate[u] = v; u = w;
		}
	}
	int match() {
		memset(mate, -1, sizeof(mate));
		int mth = 0;
		for(int i = 0; i < n; i++) {
			if(mate[i] >= 0) continue;
			start = i;
			if(search()) mth++;
		}
		return mth;
	}
};
