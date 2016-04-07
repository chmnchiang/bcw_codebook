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

const int MAXN = 42;

typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = MAXN*2 + 10;
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
//		cout<<u<<" => "<<v<<" ADD F "<<f<<" C "<<c<<endl;
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

int N, A, B;
string arr[MAXN];
int ccnt1[MAXN], ccnt2[MAXN];
int cdcnt1[MAXN], cdcnt2[MAXN];

int calc()
{
	for(int i=0; i<N; i++)
	{
		ccnt1[i] = ccnt2[i] = cdcnt1[i] = cdcnt2[i] = 0;
	}
	int totc = 0;
	int totd = 0;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(arr[i][j] == 'C')
			{
				ccnt1[i]++;
				cdcnt1[i]++;
				ccnt2[j]++;
				cdcnt2[j]++;
				totc++;
			}
			if(arr[i][j] == '.')
			{
				cdcnt1[i]++;
				cdcnt2[j]++;
				totd++;
			}
		}
	}

	int V = 2*N+2;
	int S = V-2;
	int T = V-1;

	int ans = -1;
	for(int lim=0; lim<=N; lim++)
	{
		flow.init(V, S, T);

		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				if(arr[i][j] == '.')
				{
					flow.add_edge(N+j, i, 1, 1);
				}
			}
		}

		int need_flow = 0;
		for(int i=0; i<N; i++)
		{
			need_flow += cdcnt1[i];
			flow.add_edge(S, N+i, cdcnt2[i], 0);
			flow.add_edge(i, T, cdcnt1[i], 0);
		}

		for(int i=0; i<N; i++)
			flow.add_edge(N+i, i, lim, 0);

		pll res = flow.flow();
		int f = res.F, c = res.S;
//		cout<<"LIM = "<<lim<<" F = "<<f<<" , C = "<<c<<endl;
		if(f == need_flow)
		{
			int add = totd - c;
			int total_comp = totc + add;
//			cout<<"ADD "<<add<<" TOTAL_COMP "<<total_comp<<endl;
			if(lim * B <= A * total_comp)
				ans = max(ans, add);
		}

	}
	return ans;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N>>A>>B && N)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>arr[i];

		int ans = calc();
		cout<<"Case "<<t<<": ";
		if(ans == -1) cout<<"impossible"<<endl;
		else cout<<ans<<endl;
	}

	return 0;
}

