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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;
typedef __int128_t lll;

static const int MAXN = 105;

struct CostFlow {
	struct Edge {
		int v, f, rev;
		long long c;
		Edge (int _v, int _f, long long _c, int _r) {
			v = _v;
			f = _f;
			c = _c;
			rev = _r;
		}
	};
	int n, s, t;
	int fr, bk, que[MAXN], inq[MAXN], pre[MAXN], preEg[MAXN];
	long long dis[MAXN];
	vector<Edge> E[MAXN];
	vector<long long> vec;
	void init(int _n, int _s, int _t) {
		n = _n;
		s = _s;
		t = _t;
		for (int i=0; i<n; i++) {
			E[i].clear();
		}
	}
	void add_edge(int u, int v, int f, long long c) {
		E[u].PB(Edge(v, f, c, E[v].size()));
		E[v].PB(Edge(u, 0, -c, E[u].size()-1));
	}
	vector<long long> solve() {
		vec.clear();
		while (true) {
			const long long INF = (1ll<<62) - 1;
			for (int i=0; i<n; i++) {
				inq[i] = 0;
				dis[i] = INF;
			}
			fr = bk = 0;
			dis[s] = 0;
			que[bk++] = s;
			inq[s] = 1;
			while (fr != bk) {
				int u = que[fr++];
				if (fr >= MAXN) fr -= MAXN;
				for (size_t i=0; i<E[u].size(); i++) {
					int f = E[u][i].f;
					if (f <= 0) continue;
					int v = E[u][i].v;
					long long c = E[u][i].c;
					if (dis[v] > dis[u] + c) {
						dis[v] = dis[u] + c;
						preEg[v] = i;
						pre[v] = u;
						if (!inq[v]) {
							inq[v] = 1;
							que[bk++] = v;
							if (bk >= MAXN) bk -= MAXN;
						}
					}
				}
				inq[u] = 0;
			}
			if (dis[t] == INF) break;
			int cur = t;
			int f = 1029384756;
			while (cur != s) {
				int u = pre[cur];
				int l = preEg[cur];
				f = min(f, E[u][l].f);
				cur = u;
			}
			cur = t;
			while (cur != s) {
				int u = pre[cur];
				int v = cur;
				int l = preEg[cur];
				E[u][l].f -= f;
				E[v][E[u][l].rev].f += f;
				cur = u;
			}
			for (int i=0; i<f; i++) {
				vec.PB(dis[t]);
			}
		}
		return vec;
	}

}flow;

int N, M, F, S, T;
ll C;

int main() {
	IOS;
	cin>>N>>M;
	cin>>S>>T;
	S--;
	T--;

	flow.init(N, S, T);
	for(int i=0; i<M; i++)
	{
		int a, b, u, c;
		cin>>a>>b>>u>>c;
		a--;
		b--;
		flow.add_edge(a, b, u, c);
	}
	
	auto vec = flow.solve();
	F = vec.size();
	C = 0;
	for(auto v: vec)
		C += v;

	lll up = -1, down = 1;
	ll zup = C*C;

	ll sumc = 0;
	for(int i=0; i<F; i++)
	{
		zup = min(zup, sumc * sumc + 1LL*(F-i)*(F-i));
		//cout<<"ZUP "<<zup<<endl;

		ll vdown = vec[i] * vec[i] + 1;
		ll vup = F - sumc * vec[i] - i;
		
		if(0 <= vup && vup <= vdown)
		{
			ll g = __gcd(vup, vdown);
			vdown /= g;
			vup /= g;

			lll cp = vdown * sumc + vup * vec[i];
			lll fp = vdown*(F-i) - vup;
			//assert(abs(cp) + abs(fp) <= 2000000000);
			lll ttt = cp * cp + fp * fp;
			lll ddd = vdown * vdown;
			lll ggg = __gcd(ttt, ddd);
			up = ttt / ggg;
			down = ddd / ggg;

			//cout<<up<<" / "<<down<<endl;
		}
		//cout<<"SUMC "<<sumc<<endl;
		//cout<<"XD : "<<i<<" + "<<vup<<" / "<<vdown<<endl;

		sumc += vec[i];
	}

	if(up == -1)
	{
		up = zup;
		down = 1;
	}

	cout<<(ll)up<<"/"<<(ll)down<<endl;	

	return 0;
}

