// only one segment tree / 0-base
// should call init after input N
// getPathSeg return the segment in order u->v
// fa[root] = root

typedef pair<int,int> pii;

int N,fa[MXN],belong[MXN],dep[MXN],sz[MXN],que[MXN];
int step,line[MXN],stPt[MXN],edPt[MXN];
vector<int> E[MXN], chain[MXN];

void init() {
  REP(i,N) {
    E[i].clear();
    chain[i].clear();
  }
}
void DFS(int u){
	vector<int> &c = chain[belong[u]];
	for (int i=c.size()-1; i>=0; i--){
		int v = c[i];
		stPt[v] = step;
		line[step++] = v;
	}
	for (int i=0; i<(int)c.size(); i++){
		u = c[i];
		for (auto v : E[u]){
			if (fa[u] == v || (i && v == c[i-1])) continue;
			DFS(v);
		}
		edPt[u] = step-1;
	}
}
void build_chain(int st){
	int fr,bk;
	fr=bk=0; que[bk++]=st; fa[st]=st; dep[st]=0;
	while (fr < bk){
		int u=que[fr++];
		for (auto v : E[u]){
			if (v == fa[u]) continue;
			que[bk++] = v;
			dep[v] = dep[u]+1;
			fa[v] = u;
		}
	}
	for (int i=bk-1,u,pos; i>=0; i--){
		u = que[i]; sz[u] = 1; pos = -1;
		for (auto v : E[u]){
			if (v == fa[u]) continue;
			sz[u] += sz[v];
			if (pos==-1 || sz[v]>sz[pos]) pos=v;
		}
		if (pos == -1) belong[u] = u;
		else belong[u] = belong[pos];
		chain[belong[u]].PB(u);
	}
	step = 0;
	DFS(st);
}
int getLCA(int u, int v){
	while (belong[u] != belong[v]){
		int a = chain[belong[u]].back();
		int b = chain[belong[v]].back();
		if (dep[a] > dep[b]) u = fa[a];
		else v = fa[b];
	}
	return sz[u] >= sz[v] ? u : v;
}
vector<pii> getPathSeg(int u, int v){
	vector<pii> ret1,ret2;
	while (belong[u] != belong[v]){
		int a = chain[belong[u]].back();
		int b = chain[belong[v]].back();
		if (dep[a] > dep[b]){
			ret1.PB({stPt[a],stPt[u]});
			u = fa[a];
		} else {
			ret2.PB({stPt[b],stPt[v]});
			v = fa[b];
		}
	}
	if (dep[u] > dep[v]) swap(u,v);
	ret1.PB({stPt[u],stPt[v]});
	reverse(ret2.begin(), ret2.end());
	ret1.insert(ret1.end(),ret2.begin(),ret2.end());
	return ret1;
}
// Usage
void build(){
	build_chain(0); //change root
	init(0,step,0); //init segment tree
}
int get_answer(int u, int v){
	int ret = -2147483647;
	vector<pii> vec = getPathSeg(u,v);
	for (auto it : vec)
		; // check answer with segment [it.F, it.S]
	return ret;
}

