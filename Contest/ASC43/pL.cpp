//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef long long LL;
const int MX = 150005;
const LL MOD = 1000000000039ll;
typedef pair<int,int> Edge;

struct Tree{
	int N,step;
	LL hash;
	vector<Edge> eg;
	vector<int> id,rid,leafCnt,fat,live;
	vector<LL> val;
	priority_queue<pair<int,int>,vector<pair<int,int>>> pq;

	void init(int _n){
		N = _n;
		eg.resize(N+1);
		id.resize(N+1);
		rid.resize(N+1);
		val.resize(N+1);
		live.resize(N+1);
		leafCnt.resize(N+1);
		fat.resize(N+1);
		for (int i=1; i<=N; i++)
			live[i] = 1;
		while (!pq.empty()) pq.pop();
		step = 0;
	}
	void build(){
		hash = DFS(1,1);
		calc_leaf(1,0);
	}

	LL mod(LL x){
		x %= MOD;
		if (x < 0) x += MOD;
		return x;
	}
	void pop(){
		assert(!pq.empty());
		int f = pq.top().S;
//		cout << "get " << f << endl;
		pq.pop();
		int lc = eg[f].F;
		int rc = eg[f].S;
//		cout << "delete " << lc << " " << rc << endl;
		live[lc] = live[rc] = 0;
		hash -= val[lc];
		hash -= val[rc];
		hash = mod(hash);
		int fa = fat[f];
		leafCnt[fa]++;
		if (leafCnt[fa] == 2)
			push(fa);
	}
	void push(int x){
		pq.push(MP(id[x],x));
	}
	void calc_leaf(int u, int fa){
		fat[u] = fa;
		leafCnt[u] = 0;
		if (eg[u].F){
			calc_leaf(eg[u].F, u);
			calc_leaf(eg[u].S, u);
		} else {
			leafCnt[fa]++;
			if (leafCnt[fa] == 2){
				push(fa);
			}
		}
	}
	LL DFS(int u, LL h){
		val[u] = mod(h*h);
//		cout << "val[" << u << "] = " << val[u] << endl;
		LL ret = mod(h*h);
		if (eg[u].F){
			ret += DFS(eg[u].F, mod(h*12721ll+14341));
			mod(ret);
			ret += DFS(eg[u].S, mod(h*13331ll+14341));
		}
		step++;
		id[u] = step;
		rid[step] = u;
		return mod(ret);
	}
	int DFS2(int u, Tree& ret){
		if (u == 0 || !live[u]) return 0;
		step++;
		int d = step;
		int lc = DFS2(eg[u].F,ret);
		int rc = DFS2(eg[u].S,ret);
		ret.eg[d].F = lc;
		ret.eg[d].S = rc;
		return d;
	}
	Tree get_tree(){
		int n = 0;
		for (int i=1; i<=N; i++)
			if (live[i]) n++;
		step = 0;
		Tree ret;
		ret.init(n);
		DFS2(1,ret);
		return ret;
	}
}treeA, treeB;

int N,M;

int main(){
	IOS;
	FILEIO("lca");
	while (cin >> N && N){
		treeA.init(N);
		for (int i=1; i<=N; i++){
			cin >> treeA.eg[i].F >> treeA.eg[i].S;
		}
		cin >> M;
		treeB.init(M);
		for (int i=1; i<=M; i++){
			cin >> treeB.eg[i].F >> treeB.eg[i].S;
		}
		if (N < M){
			swap(treeA,treeB);
		}
		treeA.build();
		treeB.build();
		while (N > M){
			treeA.pop();
			N -= 2;
		}
		while (treeA.hash != treeB.hash){
			treeA.pop();
			treeB.pop();
		}
		Tree ret = treeA.get_tree();
		cout << ret.N << "\n";
		for (int i=1; i<=ret.N; i++)
			cout << ret.eg[i].F << " " << ret.eg[i].S << "\n";
//		cout << endl;
	}
	return 0;
}

