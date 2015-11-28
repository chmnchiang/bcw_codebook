/*
 * Given a Tree and the power of every node.
 * Each Node can protect the nodes whose distance <= cover[i] with it
 * output the number of each node that it can protect.
 */
const int MXN = 100005;

int cover[MXN], ans[MXN];
int N, ok[MXN];
int fr,bk,que[MXN],vst[MXN],dis[MXN],fa[MXN],sz[MXN];
vector<int> E[MXN];

int bit[MXN];
int lb(int a){ return a & -a; }
void reset_bit(int st){
	for (int i = st+1; i < MXN; i+=lb(i))
		bit[i] = 0;
}
void update(int st){
	for (int i = st+1; i < MXN; i+=lb(i))
		bit[i]++;
}
int query(int st, int ret = 0){
	for (int i = st+1; i > 0; i-=lb(i))
		ret += bit[i];
	return ret;
}

void BFS(int st){
	fr = bk = 0;
	que[bk++] = st;
	vst[st] = 1;
	dis[st] = 0;
	while (fr < bk){
		int u = que[fr++];
		for (auto v : E[u]){
			if (!ok[v] || vst[v]) continue;
			vst[v] = 1;
			dis[v] = dis[u] + 1;
			fa[v] = u;
			que[bk++] = v;
		}
	}
	for (int i=0; i<bk; i++)
		vst[que[i]] = 0;
}
int find_centroid(int st){
	int ret=-1, cnt=MXN+100;
	BFS(st);
	for (int i = bk-1; i>=0; i--){
		int u = que[i], mx = 0;
		sz[u] = 1;
		for (auto v : E[u]){
			if (!ok[v] || v == fa[u]) continue;
			sz[u] += sz[v];
			mx = max(mx, sz[v]);
		}
		mx = max(mx, bk-sz[u]);
		if (mx < cnt){
			ret = u;
			cnt = mx;
		}
	}
	return ret;
}

void solve(int u){
	int root = find_centroid(u);
	ok[root] = 0;
	for (auto v : E[root])
		if (ok[v]) solve(v);
	
	for (auto v : E[root]){
		if (!ok[v]) continue;
		BFS(v);
		for (int i=0; i<bk; i++){
			dis[que[i]]++;
			update(dis[que[i]]);
		}
		for (int i=0; i<bk; i++){
			int it = que[i];
			ans[it] -= query(cover[it] - dis[it]);
		}
		for (int i=0; i<bk; i++)
			reset_bit(dis[que[i]]);
	}
	BFS(root);
	for (int i=0; i<bk; i++) update(dis[que[i]]);
	for (int i=0; i<bk; i++){
		int v = que[i];
		ans[v] += query(cover[v] - dis[v]);
	}
	for (int i=0; i<bk ;i++) reset_bit(dis[que[i]]);
	
	ok[root] = 1;
}

int main(int argc, char** argv){
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%d", &cover[i]);
		cover[i] = min(cover[i], N);
	}
	for (int i=0,u,v; i<N-1; i++){
		scanf("%d%d", &u, &v);
		u--; v--;
		E[u].PB(v);
		E[v].PB(u);
	}
	fill(ok,ok+N,1);
	FZ(vst); FZ(ans); FZ(bit);
	solve(0);
	for (int i=0; i<N; i++)
		printf("%d\n", ans[i]);
	return 0;
}
