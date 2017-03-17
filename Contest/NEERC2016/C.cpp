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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<int,int> umap_t;

#define tree _tttttt_Tt_1231239784hao12333333


const int MAXN = 50005;
const int MAX = 1000005;

struct Command {
	string s;
	int a,b,c;
};

int N,vst[MAXN],ins[MAXN];
int ncc;
vector<int> stk,hao123[MAXN];
vector<vector<int>> cycle;
vector<int> done;
vector<Command> ans;
umap_t E[MAXN];

void add_edge(int u, int v) {
	E[u][v] = 1;
	E[v][u] = 1;
}
void del_edge(int u, int v) {
	E[u].erase(v);
	E[v].erase(u);
}
void DFS(int u, int f) {
	stk.PB(u);
	ins[u] = 1;
	vst[u] = 1;
	for (auto it:E[u]) {
		int v = it.F;
		if (v == f) continue;
		if (vst[v]) {
			if (ins[v]) {
				vector<int> vec;
				for (int i=SZ(stk)-1; i>=0; i--) {
					vec.PB(stk[i]);
					if (stk[i] == v) {
						break;
					}
				}
				for (auto i:vec) hao123[i].PB(SZ(cycle));

				cycle.PB(vec);
			}
		} else {
			DFS(v, u);
		}
	}
	ins[u] = 0;
	stk.pop_back();
}
void R(int a, int b, int c) {
	ans.PB({"r",a,b,c});
}
void C(int a, int b, int c) {
	ans.PB({"c",a,b,c});
}
void J(int a, int b) {
	ans.PB({"j",a,b});
}
void solve(int u) {

	vector<int> cid;
	vector<int> vec;
	for (auto it:hao123[u]) {
		if (done[it]) continue;
		cid.PB(it);
		done[it] = 1;
		int sz = SZ(cycle[it]);

		int at = -1;
		REP(i,sz) if (cycle[it][i] == u) at = i;
		assert(at != -1);
		rotate(begin(cycle[it]), begin(cycle[it])+at, end(cycle[it]));
		assert(cycle[it][0] == u);
//		cout<<cycle[it]<<endl;

		cycle[it].PB(cycle[it][0]);

		REP(i,sz) {
			del_edge(cycle[it][i], cycle[it][i+1]);
		}
		
		cycle[it].pop_back();
		REP1(i,1,sz-1) vec.PB(cycle[it][i]);
	}

	vector<int> tree;
	vector<int> vvv;
	for (auto it:E[u]) {
		int v = it.F;
		tree.PB(v);
		vvv.PB(v);
	}
	for (auto v:vvv)
		del_edge(u,v);

	for (auto it:tree) solve(it);
	for (auto it:vec) solve(it);

	for (auto v:tree) {
		R(v,1,3);
		J(u,v);
		C(u,1,3);
		R(v,3,2);
	}

	for (auto cc:cid) {
		auto &v = cycle[cc];

		int k = SZ(v);
		R(v[1], 1, 3);
		J(u, v[1]);
		C(u, 1, 3);
		for (int i=2; i<k; i++) {
			R(v[i], 1, 4);
			J(u, v[i]);
			C(u, 3, 4);
			R(u, 3, 2);
			R(u, 4, 3);
		}
		C(u, 1, 3);
		R(u, 3, 2);
	}

}
int main() {
	FILEIO("cactus");
	IOS;
	int kk;
	cin>>N>>kk;
	REP(_,kk) {
		int m;
		cin>>m;
		int u;
		cin>>u;
		REP(__,m-1) {
			int v;
			cin>>v;
			add_edge(u,v);
			u = v;
		}
	}
	DFS(1,1);

	ncc = SZ(cycle);
	done.resize(ncc);
	fill(ALL(done),0);

	solve(1);

	cout<<SZ(ans)<<endl;
	for (auto it:ans) {
		cout<<it.s<<" ";
		if (it.s == "r" or it.s == "c") cout<<it.a<<" "<<it.b<<" "<<it.c<<"\n";
		else if (it.s == "j") cout<<it.a<<" "<<it.b<<"\n";
		else assert(false);
	}


	return 0;
}
/*

33
r 7 1 3
j 4 7
c 4 1 3
r 7 3 2
r 8 1 3
j 1 8
c 1 1 3
r 8 3 2
r 6 1 3
j 1 6
c 1 1 3
r 5 1 4
j 1 5
c 1 3 4
r 2 3 2
r 1 4 3
r 4 1 4
j 1 4
c 1 3 4
r 3 3 2
r 1 4 3
r 3 1 4
j 1 3
c 1 3 4
r 4 3 2
r 1 4 3
r 2 1 4
j 1 2
c 1 3 4
r 5 3 2
r 1 4 3
c 1 1 3
r 1 3 2


   */
