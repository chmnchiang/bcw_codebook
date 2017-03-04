#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

using pii = pair<int,int>;

const int MXN = 100005;
const int MEM = 14330005;
const int INF = 1029384756;

struct DisjointSet {
	int ts;
	vector<pii> fa[MXN],sz[MXN];

	void init() {
		REP(i,MXN) {
			fa[i].resize(1);
			sz[i].resize(1);
			fa[i][0] = {0,i};
			sz[i][0] = {0,1};
		}
		ts = 0;
	}
	int f(int x) {
		int ff = fa[x].back().S;
		return x == ff ? x : f(ff);
	}
	int f(int x, int t) {
		int ff = (--upper_bound(ALL(fa[x]),pii(t,INF)))->S;
		return x == ff ? x : f(ff,t);
	}

	int uni(int x, int y) {
		x = f(x);
		y = f(y);
		if (x == y) return ts;
		int szx = sz[x].back().S;
		int szy = sz[y].back().S;
		if (szx < szy) swap(x,y);
		ts++;
		fa[y].PB({ts,x});
		sz[x].PB({ts,szx+szy});
		return ts;
	}
} djs;

struct Node {
	int cnt,color,lc,rc;
	Node () : cnt(0), color(-1), lc(0), rc(0) {}
};

struct Edge {
	int u,v,w;
} edge[2*MXN];

int N,M,color[MXN];
int curRt;
int nodeMem;
vector<pii> weightTs;
vector<pii> rt[MXN];
Node node[MEM];

void init() {
	djs.init();
	nodeMem = 1;
	weightTs.clear();
}
int get_node() {
	assert(nodeMem < MEM);
	node[nodeMem] = Node();
	return nodeMem++;
}
void init_tree(int l, int r, int id) {
	if (l == r) {
		node[id].cnt = 0;
		node[id].color = l;
		return;
	}
	int &lc = node[id].lc;
	int &rc = node[id].rc;
	int m = (l+r)/2;

	lc = get_node();
	rc = get_node();

	init_tree(l,m,lc);
	init_tree(m+1,r,rc);
}
int update(int l, int r, int fn, int v, int id) {
	int x = get_node();
	node[x] = node[id];
	if (l == r) {
		node[x].cnt += v;
		return x;
	}
	int &lc = node[x].lc;
	int &rc = node[x].rc;
	int m = (l+r)/2;

	if (fn <= m) {
		lc = update(l,m,fn,v,lc);
	} else {
		rc = update(m+1,r,fn,v,rc);
	}

	if (node[lc].cnt >= node[rc].cnt) {
		node[x].cnt = node[lc].cnt;
		node[x].color = node[lc].color;
	} else {
		node[x].cnt = node[rc].cnt;
		node[x].color = node[rc].color;
	}

	return x;
}
void travel(int l, int r, int id) {
	if (node[id].cnt == 0) return;
	if (l == r) {
		cout<<pii(node[id].color,node[id].cnt)<<" ";
		return;
	}
	int m=(l+r)/2;
	travel(l,m,node[id].lc);
	travel(m+1,r,node[id].rc);
}
void query(int l, int r, int id, vector<pii> &vec) {
	if (node[id].cnt == 0) return;
	if (l == r) {
		vec.PB({node[id].cnt,node[id].color});
		return;
	}
	int &lc = node[id].lc;
	int &rc = node[id].rc;
	int m = (l+r)/2;
	query(l,m,lc,vec);
	query(m+1,r,rc,vec);
}
void input() {
	cin>>N>>M;
	REP1(i,1,N) cin>>color[i];
	REP1(i,1,M) cin>>edge[i].u>>edge[i].v>>edge[i].w;
	sort(edge+1,edge+1+M,[](Edge a, Edge b) { return a.w<b.w; });
}
void solve() {
	curRt = get_node();
	init_tree(1,N,curRt);
	REP1(i,1,N) {
		rt[i].clear();
		rt[i].PB({0,update(1,N,color[i],1,curRt)});
	}
	weightTs.PB({0,0});
	REP1(i,1,M) {
		int u = edge[i].u;
		int v = edge[i].v;
		u = djs.f(u);
		v = djs.f(v);
		if (u == v) continue;
		int ts = djs.uni(u,v);
		vector<pii> vec;
		if (djs.f(u) != u) swap(u, v);
		assert(djs.f(u) == u);
		query(1,N,rt[v].back().S,vec);

//		cout<<"UNION " << edge[i].u << " " << edge[i].v << " " << edge[i].w << endl;
//		cout<<vec<<endl;

		int r = rt[u].back().S;
		for (auto it:vec) {
			int cnt = it.F;
			int col = it.S;
			r = update(1,N,col,cnt,r);
		}
		
//		cout << "TS: " << ts << endl;
//		travel(1,N,r);
//		cout<<endl;


		rt[u].PB({ts,r});

		weightTs.PB({edge[i].w,ts});
	}
	weightTs.PB({edge[M].w,djs.ts});

//	cout<<weightTs<<endl;

	int last = 0;
	int Q;
	cin>>Q;

	REP1(q,1,Q) {
		int x,w;
		cin>>x>>w;
		x ^= last;
		w ^= last;
//		cout<<"QUERY " << x << " " << w << endl;
		assert(1 <= x and x <= N);
		int ts = (--upper_bound(ALL(weightTs),pii(w,INF)))->S;
//		cout<<"TS = "<<ts<<endl;
		int f = djs.f(x,ts);
//		cout<<"f = "<<f<<endl;
		int r = (--upper_bound(ALL(rt[f]),pii(ts,INF)))->S;
//		cout<<"r = "<<r<<endl;
		int ans = node[r].color;
		cout<<ans<<"\n";
		last = ans;
	}
	cerr<<"MEM = "<<nodeMem<<endl;
}
int main() {
	IOS;
	int nT;
	cin>>nT;
	REP1(t,1,nT) {
		init();
		input();
		cout<<"Case #"<<t<<":"<<endl;
		solve();
	}

	return 0;
}

