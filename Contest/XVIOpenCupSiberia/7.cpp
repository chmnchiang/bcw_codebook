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



const int MAXN = 10101;
const int INF = 10101;

typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = 30;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r;
		long long f, c;
	};
	int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
	long long dis[MXN], fl, cost;
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
		fl = cost = 0;
	}
	void add_edge(int u, int v, long long f, long long c) {
//		cout<<" ADD EDGE "<<u<<" "<<v<<" "<<f<<" "<<c<<endl;
		E[u].PB({v, SZ(E[v])  , f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, -c});
	}
	pll flow() {
		while (true) {
			for (int i=0; i<n; i++) {
				dis[i] = INF;
        inq[i] = 0;
			}
			dis[s] = 0;
			queue<int> que;
			que.push(s);
			while (!que.empty()) {
				int u = que.front(); que.pop();
				inq[u] = 0;
				for (int i=0; i<SZ(E[u]); i++) {
					int v = E[u][i].v;
					long long w = E[u][i].c;
					if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
						prv[v] = u; prvL[v] = i;
						dis[v] = dis[u] + w;
						if (!inq[v]) {
							inq[v] = 1;
							que.push(v);
						}
					}
				}
			}
			if (dis[t] == INF) break;
			long long tf = INF;
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				tf = min(tf, E[u][l].f);
			}
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				E[u][l].f -= tf;
				E[v][E[u][l].r].f += tf;
			}
			cost += tf * dis[t];
			fl += tf;
		}
		return {fl, cost};
	}
} flow;

int N, M, K, V;
int vote[MAXN];
vector<int> edge[MAXN];
int cst[MAXN][4];
vector<int> clr[MAXN][4];
int ans[MAXN];

void dfs(int v)
{
	//cout<<"DFS "<<v<<" CHILD "<<edge[v]<<endl;
	if(v < N)
	{
		for(int i=0; i<=K; i++)
			cst[v][i] = (vote[v] != i);
		return;
	}

	for(auto c: edge[v])
		dfs(c);

	int Z = SZ(edge[v]);

	for(int i=1; i<=K; i++)
	{
		cst[v][i] = INF;
		for(int f=1; f<=Z; f++)
		{
			int VV = Z + K + 4;
			int S = VV-3, TT = VV-2, T = VV-1;

			flow.init(VV, S, T);
			for(int j=0; j<Z; j++)
				flow.add_edge(S, j, 1, 0);
			for(int j=0; j<Z; j++)
				for(int k=0; k<=K; k++)
					flow.add_edge(j, Z+k, 1, cst[edge[v][j]][k]);
			flow.add_edge(Z, TT, Z, 0);
			for(int j=1; j<=K; j++)
			{
				if(j == i)
					flow.add_edge(Z+j, T, f, 0);
				else
					flow.add_edge(Z+j, TT, f-1, 0);
			}
			flow.add_edge(TT, T, Z-f, 0);

			pll res = flow.flow();
			if(res.F != Z) continue;

			int c = res.S;
			if(c < cst[v][i])
			{
				cst[v][i] = c;
				clr[v][i].clear();
				for(int j=0; j<Z; j++)
					for(auto e: flow.E[j])
						if(e.v != S and e.f == 0)
							clr[v][i].PB(e.v-Z);
			}
		}
	}

	cst[v][0] = INF;
	for(int i=1; i<=K; i++)
	{
		for(int ii=i+1; ii<=K; ii++)
		{
			for(int f=0; 2*f<=Z; f++)
			{
				int VV = Z + K + 4;
				int S = VV-3, TT = VV-2, T = VV-1;

				flow.init(VV, S, T);
				for(int j=0; j<Z; j++)
					flow.add_edge(S, j, 1, 0);
				for(int j=0; j<Z; j++)
					for(int k=0; k<=K; k++)
						flow.add_edge(j, Z+k, 1, cst[edge[v][j]][k]);
				flow.add_edge(Z, TT, Z, 0);
				for(int j=1; j<=K; j++)
				{
					if(j == i or j == ii)
						flow.add_edge(Z+j, T, f, 0);
					else
						flow.add_edge(Z+j, TT, f, 0);
				}
				flow.add_edge(TT, T, Z-2*f, 0);

				pll res = flow.flow();
				if(res.F != Z) continue;

				int c = res.S;
				if(c < cst[v][0])
				{
					cst[v][0] = c;
					clr[v][0].clear();
					for(int j=0; j<Z; j++)
						for(auto e: flow.E[j])
							if(e.v != S and e.f == 0)
								clr[v][0].PB(e.v-Z);
				}
			}
		}
	}
	
	//for(int i=0; i<=K; i++)
	//	cout<<"CLR "<<v<<" "<<i<<" : "<<cst[v][i]<<" / "<<clr[v][i]<<endl;
}

void get_ans(int v, int c)
{
	ans[v] = c;
	int Z = SZ(edge[v]);
	for(int i=0; i<Z; i++)
		get_ans(edge[v][i], clr[v][c][i]);
}

int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;

	cin>>N>>M>>K;
	V = N+M;
	for(int i=0; i<N; i++)
		cin>>vote[i];
	for(int i=0; i<M; i++)
	{
		int s, x;
		cin>>s;
		for(int j=0; j<s; j++)
		{
			cin>>x;
			if(x > 0)
				edge[N+i].PB(x-1);
			else
				edge[N+i].PB(N-x-1);
		}
	}

	dfs(N);
	get_ans(N, 1);
	
	vector<pii> vans;

	for(int i=0; i<N; i++)
		if(vote[i] != ans[i])
			vans.PB({i+1, ans[i]});

	int A = SZ(vans);
	cout<<A<<endl;
	for(auto p: vans)
		cout<<p.F<<" "<<p.S<<"\n";

	return 0;
}

