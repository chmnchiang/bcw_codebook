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
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
typedef long long ll;
typedef pair<long long, double> pll;
struct CostFlow {
	static const int MXN = 205;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r;
		long long f;
		double c;
	};
	int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
	long long fl;
	double dis[MXN], cost;
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
		fl = cost = 0;
	}
	void add_edge(int u, int v, long long f, double c) {
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
					double w = E[u][i].c;
					if (E[u][i].f > 0 && dis[v] > dis[u] + w + 1E-6) {
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

const int MXN = 222;

struct Edge {
	int x,y;
	double c;
}eg[MXN*MXN];

int N,M,E,a[MXN],b[MXN];

int main() {
	increase_stack_size();
	int cas = 1;
	while (true) {
		scanf("%d%d", &N, &M);
		if (not N and not M) break;
		REP(i,N) {
			scanf("%d", &a[i]);
		}
		REP(i,M) {
			scanf("%d", &b[i]);
		}
		E = 0;
		REP(i,N) {
			REP(j,M) {
				double c;
				scanf("%lf", &c);
				if (c >= -0.001) {
//					int t = c * 100 + 0.1;
					eg[E++] = {i,j,c};
				}
			}
		}

		int V = N + M + 2, S = N + M, T = N + M + 1;
		flow.init(V, S, T);
		REP(i,N) {
			flow.add_edge(S, i, a[i], 0);
		}
		REP(j,M) {
			flow.add_edge(N+j, T, b[j], 0);
		}
		REP(ii,E) {
			int i = eg[ii].x;
			int j = eg[ii].y;
			double c = eg[ii].c;
			flow.add_edge(i, N+j, 1029384756, c);
		}
		pll res = flow.flow();
		double a1 = res.S;

		flow.init(V, S, T);
		REP(i,N) {
			flow.add_edge(S, i, a[i], 0);
		}
		REP(j,M) {
			flow.add_edge(N+j, T, b[j], 0);
		}
		REP(ii,E) {
			int i = eg[ii].x;
			int j = eg[ii].y;
			double c = eg[ii].c;
			flow.add_edge(i, N+j, 1029384756, -c);
		}
		res = flow.flow();
		double a2 = -res.S;

//		printf("Problem %d: %lld.%02lld to %lld.%02lld\n", cas, a1/100, a1%100, a2/100, a2%100);
		printf("Problem %d: %.02f to %.02f\n", cas, a1, a2);
		cas++;
	}

    return 0;
}

