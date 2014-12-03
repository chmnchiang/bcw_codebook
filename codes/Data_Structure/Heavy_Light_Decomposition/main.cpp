int N, ip[MX];
int fa[MX],at[MX],belong[MX];
int fr,bk,sz[MX],que[MX];
vector<int> E[MX];

struct Chain{
	int n;
	vector<int> vec;
	vector<int> tree;

	void init(){
		n = vec.size();
		for (int i=0; i<n; i++)
			at[vec[i]] = i;
		tree.resize(4*n);
	}
	void build_tree(int l, int r, int id){
	}
	// Segment Tree
}chain[MX];

void DFS(int u){
	Chain &c = chain[belong[u]];
	c.init();
	for (int i=0; i<c.n; i++){
		u = c.vec[i];
		for (auto v : E[u]){
			if (fa[u] == v || (i && v == c.vec[i-1])) continue;
			DFS(v);
		}
	}
	c.build_tree(0,c.n-1,0);
}
void build_chain(){
	fr=bk=0; que[bk++] = 1; fa[1]=0;
	while (fr < bk){
		int u=que[fr++];
		for (auto v : E[u]){
			if (v == fa[u]) continue;
			que[bk++] = v;
			fa[v] = u;
		}
	}
	for (int i=bk-1,u,pos; i>=0; i--){
		u = que[i]; sz[u] = 1; pos = 0;
		for (auto v : E[u]){
			if (v == fa[u]) continue;
			sz[u] += sz[v];
			if (sz[v] > sz[pos]) pos=v;
		}
		if (pos == 0) belong[u] = u;
		else belong[u] = belong[pos];
		chain[belong[u]].vec.PB(u);
	}
	DFS(1);
}
vector<int> get_path(int u){
	vector<int> res;
	while (u){
		res.PB(belong[u]);
		u = fa[chain[belong[u]].vec.back()];
	}
	return res;
}
int jump_chain(int a){
	if (a == 0) return a;
	return fa[chain[belong[a]].vec.back()];
}
pair<int,int> findLCA(int u, int v){
	// at chain res.second
	// jump from u if res.first = 1 ( u ->* res.second )
	// jump from v if res.first = 2 ( v ->* res.second )
	vector<int> vec1,vec2;
	vec1 = get_path(u);
	vec2 = get_path(v);
	int a=u, b=v;
	for (auto v1 : vec1){
		for (auto v2 : vec2){
			if (v1 == v2)
				return sz[a] >= sz[b] ? MP(1,a) : MP(2,b);
			b = jump_chain(b);
		}
		a = jump_chain(a);
	}
	return MP(0,0);
}
int main(int argc, char** argv){
	scanf("%d", &N);
	for (int i=1; i<=N; i++)
		scanf("%d", &ip[i]);
	for (int i=0; i<N-1; i++){
		int u,v;
		scanf("%d%d", &u, &v);
		E[u].PB(v);
		E[v].PB(u);
	}
	build_chain();

	return 0;
}
