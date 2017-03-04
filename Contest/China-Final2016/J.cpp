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

typedef long long ll;

const int MAXN = 32;

typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = 3333;
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
}flow;

int N, M, E;
ll sr[MAXN][MAXN], sc[MAXN][MAXN];
bool ess[MAXN][MAXN];

ll calc()
{
	int V = 2*N*M+2;
	int S = V-2, T = V-1;
	flow.init(V, S, T);

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			int vo = i*2*M + j*2;
			int vi = vo + 1;
			flow.add_edge(S, vo, 1, 0);
			flow.add_edge(vi, T, 1, 0);
			if(!ess[i][j])
				flow.add_edge(vo, vi, 1, 0);

			if((i+j)%2 == 0)
			{
				if(j>0)
					flow.add_edge(vo, vi-2, 1, -sc[i][j-1]);
				if(j<M-1)
					flow.add_edge(vo, vi+2, 1, -sc[i][j]);
			}
			else
			{
				if(i>0)
					flow.add_edge(vo, vi-2*M, 1, -sr[i-1][j]);
				if(i<N-1)
					flow.add_edge(vo, vi+2*M, 1, -sr[i][j]);
			}
		}
	}

	pll res = flow.flow();
	if(res.F != N*M) return -1;
	return -res.S;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M;
		for(int i=0; i<N; i++)
			for(int j=0; j<M-1; j++)
				cin>>sc[i][j];
		for(int i=0; i<N-1; i++)
			for(int j=0; j<M; j++)
				cin>>sr[i][j];

		for(int i=0; i<N; i++)
			for(int j=0; j<M; j++)
				ess[i][j] = false;

		cin>>E;
		for(int i=0; i<E; i++)
		{
			int x, y;
			cin>>x>>y;
			ess[x-1][y-1] = true;
		}

		ll ans = calc();
		cout<<"Case #"<<t<<": ";
		if(ans == -1) cout<<"Impossible";
		else cout<<ans;
		cout<<endl;
	}

	return 0;
}

