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



const int MXN = 100005;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<int,int> umap_t;
#define tree tterererer1i23jiajsf8127u938uajksjfij12
using pii = pair<int,int>;

struct DAG {
	int n,cc,fst,vst[MXN];
	vector<int> E[MXN],topo;
	umap_t edge[MXN];
	void init(int tn) {
		n = tn;
		fst = 1;
		cc = 0;
		REP(i,n) {
			E[i].clear();
			edge[i].clear();
		}
	}
	void add_edge(int u, int v) {
		edge[u][v] = 1;
	}
	void DFS(int u) {
		vst[u] = 1;
		for (auto v:E[u]) 
			if (!vst[v]) DFS(v);
		topo.PB(u);
	}
	void build_edge() {
		if (!fst) return;
		REP(i,n) {
			for (auto it:edge[i])
				E[i].PB(it.F);
		}
		fst = 0;
	}
	vector<int> gen_topo(vector<int> permu = {}) {
		cc++;
		build_edge();
		topo.clear();
		REP(i,n) {
			vst[i] = 0;
		//	random_shuffle(ALL(E[i]));
		}
		for (auto i:permu) {
			if (!vst[i]) DFS(i);
		}
		REP(i,n) {
			if (vst[i]) continue;
			DFS(i);
		}
		reverse(ALL(topo));
		return topo;
	}
	int can(int st, int ed) {
		build_edge();
		if (st == ed) return 1;
		REP(i,n) vst[i] = 0;
		queue<int> que;
		que.push(st);
		vst[st] = 1;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (auto v:E[u]) {
				if (vst[v]) continue;
				if (v == ed) return 1;
				que.push(v);
				vst[v] = 1;
			}
		}
		return 0;
	}
} dag;
struct Scc {
	int n, nScc, vst[MXN], bln[MXN];
	vector<int> E[MXN], rE[MXN], vec;
	void init(int _n){
		n = _n;
		for (int i=0; i<n; i++){
			E[i].clear();
			rE[i].clear();
		}
	}
	void add_edge(int u, int v){
		E[u].PB(v);
		rE[v].PB(u);
	}
	void DFS(int u){
		vst[u]=1;
		for (auto v : E[u])
			if (!vst[v]) DFS(v);
		vec.PB(u);
	}
	void rDFS(int u){
		vst[u] = 1;
		bln[u] = nScc;
		for (auto v : rE[u])
			if (!vst[v]) rDFS(v);
	}
	void solve() {
		nScc = 0;
		vec.clear();
		for (int i=0; i<n; i++) vst[i] = 0;
		for (int i=0; i<n; i++)
			if (!vst[i]) DFS(i);
		reverse(vec.begin(),vec.end());
		for (int i=0; i<n; i++) vst[i] = 0;
		for (auto v : vec){
			if (!vst[v]){
				rDFS(v);
				nScc++;
			}
		}
	}
} gp;

int N,at[MXN];
vector<pii> qry;
vector<pii> edge;

void output(vector<pii> vec) {
	cout<<"YES"<<endl;
	cout<<SZ(vec)<<endl;
	for (auto it:vec) {
		cout<<it.F+1<<" "<<it.S+1<<"\n";
	}
	exit(0);
}
int main() {
#ifndef BCW
	freopen("input.txt", "r", stdin); \
		freopen("output.txt", "w", stdout);
#endif
	IOS;
	cin>>N;
	gp.init(N);
	int kk;
	cin>>kk;

	REP(_,kk) {
		int u,v;
		cin>>u>>v;
		u--;
		v--;
		gp.add_edge(u,v);
		edge.PB({u,v});
	}
	gp.solve();

	cin>>kk;
	qry.resize(kk);
	REP(i,kk) {
		cin>>qry[i].F>>qry[i].S;
		qry[i].F--;
		qry[i].S--;
		int u = qry[i].F;
		int v = qry[i].S;
		if (gp.bln[u] == gp.bln[v]) {
			cout<<"NO"<<endl;
			return 0;
		}
		qry[i] = {gp.bln[u],gp.bln[v]};
	}
	sort(ALL(qry));
	qry.resize(unique(ALL(qry))-begin(qry));

	int V = gp.nScc;
	dag.init(V);
	for (auto it:edge) {
		int u = it.F;
		int v = it.S;
		if (gp.bln[u] != gp.bln[v])
			dag.add_edge(gp.bln[u], gp.bln[v]);
	}

	REP(_,200) {
		vector<pii> rem;

		vector<int> permu;
		for (auto it:qry) permu.PB(it.F);
		random_shuffle(ALL(permu));
		vector<int> topo = dag.gen_topo(permu);
//		cout<<"TOPO "<<topo<<endl;
		REP(i,V) {
			at[topo[i]] = i;
		}
		for (auto it:qry) {
			int u = it.F;
			int v = it.S;
			if (at[u] > at[v]) continue;
			rem.PB(it);
		}
		qry = rem;
//		cout<<qry<<endl;
	}

	random_shuffle(ALL(qry));
	for (auto it:qry) {
		int u = it.F;
		int v = it.S;
		if (dag.can(u,v)) {
			cout<<"NO"<<endl;
			return 0;
		}
	}
	output(edge);

	return 0;
}

