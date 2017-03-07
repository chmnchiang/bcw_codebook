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

const int MXN = 305;

struct Scc{
	int n, nScc, vst[MXN], bln[MXN], edge[MXN][MXN], hao123[MXN], dp[MXN][MXN], is[MXN];
	vector<int> E[MXN], rE[MXN], vec;
	vector<int> E2[MXN];
	void init(int _n){
		n = _n;
		for (int i=1; i<=n; i++){
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
	void solve(){
		nScc = 0;
		vec.clear();
		for (int i=1; i<=n; i++) vst[i] = 0;
		for (int i=1; i<=n; i++)
			if (!vst[i]) DFS(i);
		reverse(vec.begin(),vec.end());
		for (int i=1; i<=n; i++) vst[i] = 0;
		for (auto v : vec){
			if (!vst[v]){
				nScc++;
				rDFS(v);
			}
		}
	}
	vector<pii> output() {
		vector<pii> res;

		REP1(i,1,n) hao123[bln[i]] = i;

		REP1(i,1,nScc) {
			vector<int> vvv;
			REP1(j,1,n) if (bln[j] == i) vvv.PB(j);
//			cout<<i<<" : "<<vvv<<endl;
		}

		REP1(i,1,n) {
			for (auto j:E[i]) {
				if (bln[i] != bln[j]) {
					edge[bln[i]][bln[j]] = dp[bln[i]][bln[j]] = 1;
				}
			}
		}
/*
		REP1(i,1,nScc) {
			REP1(j,1,nScc) {
				if (edge[i][j]) dp[i][j] = 1;
				cout<<edge[i][j]<<" ";
			}
			cout<<endl;
		}
*/
		for (int i=nScc; i>=1; i--) {
			REP1(j,1,nScc) {
				if (dp[i][j]) continue;
				REP1(k,1,nScc) {
					if (edge[i][k] and dp[k][j]) {
						dp[i][j] = 1;
					}
				}
			}
		}
/*
		REP1(i,1,nScc) {
			REP1(j,1,nScc) {
				if (edge[i][j]) dp[i][j] = 1;
				cout<<dp[i][j]<<" ";
			}
			cout<<endl;
		}
*/
		for (int i=nScc; i>=1; i--) {
			vector<int> vvv;
			for (int j=nScc; j>=1; j--) {
				if (dp[j][i]) vvv.PB(j);
			}
			FZ(is);
			int sz = SZ(vvv);
//			cout<<i<<" "<<vvv<<endl;
			REP(j,sz) {
				int add = 1;
				REP(k,j) {
					if (dp[vvv[j]][vvv[k]]) {
						add = 0;
					}
				}
				if (add) {
					res.PB({hao123[vvv[j]], hao123[i]});
				}
			}
		}

		REP1(i,1,nScc) {
			vector<int> cyc;
			REP1(j,1,n) {
				if (bln[j] == i) cyc.PB(j);
			}
			int sz = SZ(cyc);
			if (sz > 1) {
				cyc.PB(cyc[0]);
				REP(j,sz) res.PB({cyc[j],cyc[j+1]});
			}
		}
		return res;
	}
} gp;

int main() {
	IOS;
	int N,M;
	cin>>N>>M;
	gp.init(N);
	REP(_,M) {
		int u,v;
		cin>>u>>v;
		gp.add_edge(u,v);
	}
	gp.solve();
	vector<pii> e = gp.output();

	cout<<N<<" "<<SZ(e)<<endl;
	for (auto &it:e) {
		cout<<it.F<<" "<<it.S<<endl;
	}


	return 0;
}

