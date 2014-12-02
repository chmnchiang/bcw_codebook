struct GenMatch { // 1-base
	static const int MAXN = 250;
	int V;
	bool el[MAXN][MAXN];
	int pr[MAXN];
	bool inq[MAXN],inp[MAXN],inb[MAXN];
	queue<int> qe;
	int st,ed;
	int nb;
	int bk[MAXN],djs[MAXN];
	int ans;
	void init(int _V) {
		V = _V;
		memset(el,0,sizeof(el));
		memset(pr,0,sizeof(pr));
		memset(inq,0,sizeof(inq));
		memset(inp,0,sizeof(inp));
		memset(inb,0,sizeof(inb));
		memset(djs,0,sizeof(djs));
		memset(bk,0,sizeof(bk));
		ans = 0;
	}
	void add_edge(int u, int v) {
		el[u][v] = el[v][u] = 1;
	}
	int lca(int u,int v) {
		memset(inp,0,sizeof(inp));
		while(1) {
			u = djs[u];
			inp[u] = true;
			if(u == st) break;
			u = bk[pr[u]];
		}
		while(1) {
			v = djs[v];
			if(inp[v]) return v;
			v = bk[pr[v]];
		}
		return v;
	}
	void upd(int u) {
		int v;
		while(djs[u] != nb) {
			v = pr[u];
			inb[djs[u]] = inb[djs[v]] = true;
			u = bk[v];
			if(djs[u] != nb) bk[u] = v;
		}
	}
	void blo(int u,int v) {
		nb = lca(u,v);
		memset(inb,0,sizeof(inb));
		upd(u); upd(v);
		if(djs[u] != nb) bk[u] = v;
		if(djs[v] != nb) bk[v] = u;
		for(int tu = 1; tu <= V; tu++)
			if(inb[djs[tu]]) {
				djs[tu] = nb;
				if(!inq[tu]){
					qe.push(tu);
					inq[tu] = 1;
				}
			}
	}
	void flow() {
		memset(inq,false,sizeof(inq));
		memset(bk,0,sizeof(bk));
		for(int i = 1; i <= V;i++)
			djs[i] = i;

		while(qe.size()) qe.pop();
		qe.push(st);
		inq[st] = 1;
		ed = 0;
		while(qe.size()) {
			int u = qe.front(); qe.pop();
			for(int v = 1; v <= V; v++)
				if(el[u][v] && (djs[u] != djs[v]) && (pr[u] != v)) {
					if((v == st) || ((pr[v] > 0) && bk[pr[v]] > 0))
						blo(u,v);
					else if(bk[v] == 0) {
						bk[v] = u;
						if(pr[v] > 0) {
							if(!inq[pr[v]]) qe.push(pr[v]);
						} else {
							ed = v;
							return;
						}
					}
				}
		}
	}
	void aug() {
		int u,v,w;
		u = ed;
		while(u > 0) {
			v = bk[u];
			w = pr[v];
			pr[v] = u;
			pr[u] = v;
			u = w;
		}
	}
	int solve() {
		memset(pr,0,sizeof(pr));
		for(int u = 1; u <= V; u++)
			if(pr[u] == 0) {
				st = u;
				flow();
				if(ed > 0) {
					aug();
					ans ++;
				}
			}
		return ans;
	}
};

int main() {
	gp.init(V);
	for(int i=0; i<E; i++) {
		int u, v;
		cin >> u >> v;
		gp.edge(u, v);
	}
	cout << gp.solve() << endl;
}

