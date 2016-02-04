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


typedef pair<int, int> pii;

const int MAXN = 514;

typedef pair<long long, long long> pll;
struct Graph {
	int n, vst[MAXN];
	vector<int> E[MAXN], tmp;
	void init() {
		n = 0;
		for (int i=0; i<MAXN; i++) {
			E[i].clear();
			vst[i] = 0;
		}
	}
	void add_edge(int u, int v) {
		n = max(n, u+1);
		n = max(n, v+1);
		E[u].PB(v);
		E[v].PB(u);
	}
	void DFS(int v) {
		tmp.PB(v);
		vst[v] = 1;
		for (auto u:E[v]) {
			if (vst[u]) continue;
			DFS(u);
		}
	}
	vector<vector<int>> solve() {
		vector<vector<int>> res;
		for (int i=0; i<n; i++) {
			if (!vst[i] && SZ(E[i]) == 1) {
				tmp.clear();
				DFS(i);
				res.PB(tmp);
			}
		}
		for (int i=0; i<n; i++) {
			if (!vst[i] && SZ(E[i]) == 2) {
				tmp.clear();
				DFS(i);
				res.PB(tmp);
			}
		}
		return res;
	}
}G;
struct CostFlow {
	static const int MXN = MAXN+10;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r, tag;
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
		E[u].PB({v, SZ(E[v])  , 1, f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, 0, -c});
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

int N;
pii pt[MAXN];
map<pii, int> mp;
vector<int> vup, vdown;
int ans[MAXN];

void addge(pii a, pii b)
{
	if(!mp.count(a) || !mp.count(b)) return;
	int v = mp[a], u = mp[b];
	flow.add_edge(v, u, 1, 0);
}
void check_edge(pii a) {
	if (!mp.count(a)) return;
	int v = mp[a];
	for (auto it:flow.E[v]) {
		if (it.tag && it.f == 0) {
			G.add_edge(v, it.v);
		}
	}
}

bool con_word_number()
{
	for(int i=0; i<N; i++)
		mp[pt[i]] = i;

	int SS = N, TT = N+1, S = N+2, T = N+3, VV = N+4;
	flow.init(VV, SS, TT);
	flow.add_edge(SS, S, 1024, 0);
	flow.add_edge(T, TT, 1024, 0);
	flow.add_edge(S, T, 1024, 0);

	for(int i=0; i<N; i++)
	{
		int x = pt[i].F, y = pt[i].S;
		if(x%2 == 0)
		{
			vup.PB(i);
			flow.add_edge(S, i, 1, 0);
			flow.add_edge(S, i, 1, -1);
			addge(pt[i], {x-1, y});
			addge(pt[i], {x+1, y});
			addge(pt[i], {x+1, y-1});
		}
		else
		{
			vdown.PB(i);
			flow.add_edge(i, T, 1, 0);
			flow.add_edge(i, T, 1, -1);
			addge({x-1, y}, pt[i]);
			addge({x+1, y}, pt[i]);
			addge({x-1, y+1}, pt[i]);
		}
	}

	auto p = flow.flow();
	if(p.S != -N) return false;

	G.init();
	for (int i=0; i<N; i++) {
		int x = pt[i].F;
		if (x%2 == 0) {
			check_edge(pt[i]);
		}
	}
	auto vecvec = G.solve();

	int cur = 1;
	for(auto vec: vecvec)
	{
		int sz = vec.size();
		for(int i=0; i<sz; i+=2)
		{
			if(i == sz - 1)
				ans[vec[i]] = cur-1;
			else
			{
				ans[vec[i]] = ans[vec[i+1]] = cur;
				cur++;
			}
		}
	}

	return true;
}

int main() {
	IOS;
	FILEIO("tiling");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	bool res = con_word_number();

	if(!res)
		cout<<"No solution"<<endl;
	else
	{
		int k = 0;
		for(int i=0; i<N; i++)
			k = max(k, ans[i]);
		cout<<k<<endl;
		for(int i=0; i<N; i++)
			cout<<ans[i]<<(i==N-1 ? "\n" : " ");
	}

    return 0;
}

