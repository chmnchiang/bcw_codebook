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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

typedef pair<int,int> pii;
typedef long long ll;
const int MXN = 100005;
const ll INF = 1LL<<60;

struct DisjointSet {
	int fa[MXN];
	void init() { REP(i,MXN) fa[i] = i; }
	int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
	void uni(int x, int y) { fa[f(y)] = f(x); }
}djs;


int N,M,C[MXN];
ll P[MXN];
vector<int> E[MXN];
vector<int> con[MXN];

bool comp(int a, int b) { return C[a] < C[b]; }

struct Graph {
	int n;
	ll mx[MXN];
	vector<int> E[MXN];
	void init(int _n) {
		n = _n;
		REP1(i,0,n+1) {
			E[i].clear();
		}
	}
	void add_edge(int u, int v) {
		E[u].PB(v);
	}
	ll solve() {
		vector<int> per;
		REP1(i,1,N) {
			per.PB(i);
			P[i] = -INF;
			mx[i] = -INF;
		}
		sort(ALL(per),comp);
		REP(ii,N) {
			int jj = ii;
			while (jj < N and C[per[jj]] == C[per[ii]]) jj++;
			jj--;
			REP1(i,ii,jj) {
				int u = per[i];
				int a = djs.f(u);
				for (auto v:E[u]) {
					assert(P[v] > 0);
					P[a] = max(P[a], P[v]);
				}
				P[a] = max(P[a],0LL);
			}
			REP1(i,ii,jj) {
				int u = per[i];
				if (u == djs.f(u)) P[u]++;
			}
			REP1(i,ii,jj) {
				int u = per[i];
				P[u] = P[djs.f(u)];
			}
			
			ii = jj;
		}

		ll res = 0;
		REP1(i,1,N) res += P[i];
		return res;
	}
}G;

int main() {
	IOS;
	while (cin >> N) {
		djs.init();
		REP1(i,1,N) {
			cin >> C[i];
			E[i].clear();
		}
		cin >> M;
		REP(_,M) {
			int u,v;
			cin >> u >> v;
			E[u].PB(v);
			E[v].PB(u);
		}

		G.init(N);
		REP1(i,1,N) {
			vector<int> vec;
			vec = E[i];
			vec.PB(i);
			sort(ALL(vec),comp);
			REP(j,SZ(vec)-1) {
				int a = vec[j];
				int b = vec[j+1];
				if (C[a] < C[b]) {
					G.add_edge(b,a);
				} else {
					assert(C[a] == C[b]);
					djs.uni(a,b);
				}
			}
		}
		ll ans = G.solve();
		cout << ans << endl;
	}

	return 0;
}


