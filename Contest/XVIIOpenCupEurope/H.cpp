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


using pii = pair<int, int>;

const int MAXN = 1024;
const int MAX = MAXN*MAXN;
const int LOG = 22;
const int INF = 1029384756;

struct DisjoinSet {
	int fa[MAX];
	void init() {
		REP(i,MAX) fa[i] = i;
	}
	int f(int x) { return fa[x] == x ? x : fa[x]=f(fa[x]); }
	void uni(int x, int y) {
		fa[f(y)] = f(x);
	}
} djs;

#define right right1111111
#define left left11111111
#define index index3333333

int N;
int sum[MAXN][MAXN];
int index[MAXN][MAXN],value[MAXN][MAXN];

int fa[LOG][MAX],vst[MAX],dep[MAX],alpha[LOG][MAX];
char mp[MAXN][MAXN];
vector<pii> E[MAX];
vector<pii> EDGE[MAXN];

inline int get_sum(int x1, int y1, int x2, int y2) {
	if (x1 <= 0 or y1 <= 0 or x2 > N or y2 > N) return 1;
	return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}
void build_value() {
	REP1(i,1,N) REP1(j,1,N) {
		sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		sum[i][j] += (mp[i][j] == '#');
	}

	REP1(i,1,N) REP1(j,1,N) {
		value[i][j] = 0;
		if (mp[i][j] == '#') continue;
		int l = 0, r = N;
		while (l < r) {
			int m = (l + r) / 2;
			if (get_sum(i-m,j-m,i+m,j+m) > 0) r = m;
			else l = m+1;
		}
		value[i][j] = 2*(l-1) + 1;
	}

	/*
	REP1(i,1,N) {
		REP1(j,1,N) cout<<value[i][j]<<" ";
		cout<<endl;
	}
	*/

}
void DFS(int u, int f, int d) {
	fa[0][u] = f;
	dep[u] = d;
	vst[u] = 1;
	for (auto it:E[u]) {
		int v = it.F;
		if (v == f) continue;
		DFS(v, u, d+1);
		alpha[0][v] = it.S;
	}
}
int goup(int u, int k) {
	REP(i,LOG) {
		if (k & (1<<i)) {
			u = fa[i][u];
			k -= 1<<i;
			if (!k) break;
		}
	}
	return u;
}
int getLCA(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int dif = dep[v] - dep[u];
	v = goup(v, dif);
	if (u == v) return u;

	for (int i=LOG-1; i>=0; i--) {
		if (fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	}
	return fa[0][u];
}
int get_ans(int p, int u) {
	int res = INF;
	int dif = dep[u] - dep[p];
	REP(i,LOG) {
		if (dif & (1<<i)) {
			res = min(res, alpha[i][u]);
			u = fa[i][u];
		}
	}
	return res;
}
int query(int u, int v) {
	if (djs.f(u) != djs.f(v)) return 0;
	int res = INF;
	int lca = getLCA(u,v);
	//cout<<get_ans(lca,u)<<" "<<get_ans(lca,v)<<endl;
	res = min(res, get_ans(lca, u));
	res = min(res, get_ans(lca, v));
	return res;
}
int main() {
	IOS;
	cin>>N;
	REP1(i,1,N) {
		cin>>&mp[i][1];
	}
	build_value();
	int ppp = 0;
	REP1(i,1,N) {
		REP1(j,1,N) {
			index[i][j] = ++ppp;
		}
	}


	static int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
	REP1(i,1,N) REP1(j,1,N) {
		REP(d,4) {
			int x = i + dir[d][0];
			int y = j + dir[d][1];
			if (x < 1 or x > N or y < 1 or y > N) continue;
			int w = min(value[i][j], value[x][y]);
			if (w == 0) continue;
			int u = index[i][j];
			int v = index[x][y];
			EDGE[w].PB(pii(u,v));
		}
	}

	djs.init();
	for (int w=MAXN-1; w>=0; w--) {
		for (auto it:EDGE[w]) {
			int u = it.F;
			int v = it.S;
			if (djs.f(u) != djs.f(v)) {
				djs.uni(u,v);
				E[u].PB({v,w});
				E[v].PB({u,w});
				//cout<<"EDGE "<<u<<" "<<v<<" "<<w<<endl;
			}
		}
	}

	int V = N*N;
	REP1(i,1,V) {
		if (!vst[i]) {
			DFS(i,i,0);
		}
	}

	REP1(i,1,LOG-1) {
		REP1(j,1,V) {
			fa[i][j] = fa[i-1][fa[i-1][j]];
			alpha[i][j] = min(alpha[i-1][j], alpha[i-1][fa[i-1][j]]);
		}
	}

	int Q;
	cin>>Q;
	REP(_,Q) {
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		int u = index[x1][y1];
		int v = index[x2][y2];
		int res;
		//cout<<"QUERY " << pii(x1,y1) << " " << pii(x2,y2)<<endl;
		if (x1 == x2 and y1 == y2) {
			res = value[x1][y1];
		} else {
			res = query(u, v);
		}
		cout<<res<<"\n";
	}


	return 0;
}

