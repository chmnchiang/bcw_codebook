const int MX = 100005;
const int INF = 1029384756;

int N,fa[MX],faW[MX],sz[MX],belong[MX],color[MX],at[MX];
int fr,bk,que[MX];
vector<PII> E[MX];
multiset<int> D[MX];
multiset<int> ans;

struct Chain{
	int n;
	vector<int> V;
	struct Node{
		int mxL, mxR, mx;
	};
	Node *tree;
	int *d;

	void init(){
		n = V.size();
		for (int i=0; i<n; i++)
			at[V[i]] = i;
		d = new int[n];
		for (int i=1; i<n; i++)
			d[i] = d[i-1] + faW[V[i-1]];
		tree = new Node[4*n];
	}
	int max3(int a, int b, int c){
		return max(a,max(b,c));
	}
	void pushUp(int L, int R, int id){
		int M = (L+R)/2;
		int lc = id*2+1;
		int rc = id*2+2;
		tree[id].mxL = max3(-INF, tree[lc].mxL, d[M+1]-d[L]+tree[rc].mxL);
		tree[id].mxR = max3(-INF, tree[rc].mxR, d[R]-d[M]+tree[lc].mxR);
		tree[id].mx = max3(tree[lc].mx, tree[rc].mx, tree[lc].mxR + d[M+1]-d[M] + tree[rc].mxL);
	}
	void build_tree(int L, int R, int id){
		if (L == R){
			multiset<int>::reverse_iterator ptr=D[V[L]].rbegin();
			tree[id].mxL = tree[id].mxR = tree[id].mx = *ptr;
			ptr++;
			tree[id].mx = max(-INF,tree[id].mx+(*ptr));
			return ;
		}
		int M = (L+R)/2;
		build_tree(L,M,id*2+1);
		build_tree(M+1,R,id*2+2);
		pushUp(L,R,id);
	}
	void update_tree(int L, int R, int fn, int id){
		if (L == R){
			multiset<int>::reverse_iterator ptr=D[V[L]].rbegin();
			tree[id].mxL = tree[id].mxR = tree[id].mx = *ptr;
			ptr++;
			tree[id].mx = max(-INF,tree[id].mx+(*ptr));
			return ;
		}
		int M=(L+R)/2;
		if (fn <= M) update_tree(L,M,fn,id*2+1);
		else update_tree(M+1,R,fn,id*2+2);
		pushUp(L,R,id);
	}
	int update(int x){
		int u=V.back();
		int p=fa[u];
		if (p) D[p].erase(D[p].find(faW[u]+tree[0].mxR));
		ans.erase(ans.find(tree[0].mx));
		update_tree(0,n-1,at[x],0);
		ans.insert(tree[0].mx);
		if (p) D[p].insert(faW[u]+tree[0].mxR);
		return p;
	}

}chain[MX];

void DFS(int u){
	Chain &c = chain[belong[u]];
	c.init();
	for (int i=0,v; i<c.n; i++){
		u = c.V[i];
		FOR(it,E[u]){
			v = it->F;
			if (fa[u] == v || (i && v == c.V[i-1])) continue;
			DFS(v);
			D[u].insert(chain[belong[v]].tree[0].mxR+it->S);
		}
		D[u].insert(-INF);
		D[u].insert(-INF);
		D[u].insert(0);
	}
	c.build_tree(0,c.n-1,0);
	ans.insert(c.tree[0].mx);
}
int main(int argc, char** argv){
	scanf("%d", &N);
	for (int i=0,u,v,w; i<N-1; i++){
		scanf("%d%d%d", &u, &v, &w);
		E[u].PB(MP(v,w));
		E[v].PB(MP(u,w));
	}
	fr=bk=0;	que[bk++] = 1;
	while (fr < bk){
		int u=que[fr++],v;
		FOR(it,E[u]){
			v = it->F;
			if (v == fa[u]) continue;
			que[bk++] = v;
			fa[v] = u;
			faW[v] = it->S;
		}
	}
	for (int i=bk-1,u,v,pos; i>=0; i--){
		u = que[i];
		sz[u] = 1;
		pos = 0;
		FOR(it,E[u]){
			v = it->F;
			if (v == fa[u]) continue;
			sz[u] += sz[v];
			if (sz[v] > sz[pos])
				pos=v;
		}
		if (pos == 0) belong[u] = u;
		else belong[u] = belong[pos];
		chain[belong[u]].V.PB(u);
	}
	DFS(1);
	int nq;
	scanf("%d", &nq);
	char cmd[10];
	while (nq--){
		scanf("%s", cmd);
		if (cmd[0] == 'C'){
			int x;
			scanf("%d", &x);
			if (color[x]){
				D[x].insert(0);
			} else {
				D[x].erase(D[x].find(0));
			}
			color[x] ^= 1;
			while (x){
				x = chain[belong[x]].update(x);
			}
		} else {
			if (*ans.rbegin() != -INF){
				printf("%d\n", max(0,*ans.rbegin()));
			} else {
				puts("They have disappeared.");
			}
		}
	}
	return 0;
}
