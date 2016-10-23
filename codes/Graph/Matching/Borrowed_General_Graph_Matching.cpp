struct GenMatch { // 1-base
	static const int MAXN = 514;
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
		for(int i = 0; i <= V; i++) {
			for(int j = 0; j <= V; j++) el[i][j] = 0;
			pr[i] = bk[i] = djs[i] = 0;
			inq[i] = inp[i] = inb[i] = 0;
		}
		ans = 0;
	}
	void add_edge(int u, int v) {
		el[u][v] = el[v][u] = 1;
	}
	int lca(int u,int v) {
		for(int i = 0; i <= V; i++) inp[i] = 0;
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
		for (int i=0; i<=V; i++) inb[i] = 0;
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
		for(int i = 1; i <= V; i++) {
			inq[i] = 0;
			bk[i] = 0;
			djs[i] = i;
		}

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
		for(int i = 0; i <= V; i++) pr[i] = 0;
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
}G;

int main() {
	G.init(V);
	for(int i=0; i<E; i++) {
		int u, v;
		cin >> u >> v;
		G.add_edge(u, v);
	}
	cout << G.solve() << endl;
}

