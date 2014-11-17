class Node{
public:
	int pri,num,cnt,lc,rc;
	Node () : pri(-1), num(0), cnt(0), lc(0), rc(0) {}
	Node (int _num){
		pri = (rand()<<15) + rand();
		num = _num;
		cnt = 1;
		lc = rc = 0;
	}
}tree[MX];

int nMem;

int get_rand(){
	return (rand()<<15) + rand();
}
int get_node(){
	tree[nMem] = Node();
	if (nMem >= MX) while(1);
	return nMem++;
}
void upd_node(int rt){
	if (!rt) return ;
	int lc=tree[rt].lc;
	int rc=tree[rt].rc;
	tree[rt].cnt = tree[lc].cnt + tree[rc].cnt + 1;
}
int merge(int a, int b){
	if (!a) return b;
	if (!b) return a;
	int res=0;
	if (tree[a].pri > tree[b].pri){
		res = a; //get_node();
		tree[res] = tree[a];
		tree[res].rc = merge(tree[res].rc,b);
	} else {
		res = b; //get_node();
		tree[res] = tree[b];
		tree[res].lc = merge(a,tree[res].lc);
	}
	upd_node(res);
	return res;
}
pair<int,int> split(int a, int k){
	if (k == 0) return _MP(0,a);
	if (k == tree[a].cnt) return _MP(a,0);
	int lc=tree[a].lc, rc=tree[a].rc;
	pair<int,int> res;
	int np=a; //get_node();
	//tree[np] = tree[a];
	if (tree[lc].cnt >= k){
		res = split(lc,k);
		tree[np].lc = res._S;
		res._S = np;
	} else {
		res = split(rc,k-tree[lc].cnt-1);
		tree[np].rc = res._F;
		res._F = np;
	}
	upd_node(res._F);
	upd_node(res._S);
	return res;
}
