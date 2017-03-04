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
const int MXN = 8005;
const int INF = 1029384756;

struct Edge {
	int u,v,w;
	pii p,q;
} edge[MXN];


int M;
int N,ans,dis[MXN],done[MXN];
vector<pii> E[MXN];

void input() {
	cin>>M;
	REP(i,M) {
		cin>>edge[i].p.F>>edge[i].p.S;
		cin>>edge[i].q.F>>edge[i].q.S;
		cin>>edge[i].w;
	}
}
void calc(int st, int ed, int base) {
	REP(i,N) {
		dis[i] = INF;
		done[i] = 0;
	}
	priority_queue<pii> pq;
	dis[st] = base;
	pq.push({-dis[st],st});
	while (!pq.empty()) {
		int u = pq.top().S;
		pq.pop();
		if (done[u]) continue;
		done[u] = 1;
		if (dis[u] >= ans) break;
		for (auto it:E[u]) {
			int v = it.F;
			int w = it.S;
			if (u == st and v == ed) continue;
			if (done[v]) continue;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push({-dis[v],v});
			}
		}
		if (done[ed]) break;
	}
	if (done[ed]) ans = min(ans, dis[ed]);
}
void solve() {
	vector<pii> node;
	REP(i,M) {
		node.PB(edge[i].p);
		node.PB(edge[i].q);
	}
	sort(ALL(node));
	node.resize(unique(ALL(node))-begin(node));
	N = SZ(node);
	REP(i,N) E[i].clear();
	REP(i,M) {
		int &u = edge[i].u;
		int &v = edge[i].v;
		u = lower_bound(ALL(node), edge[i].p) - begin(node);
		v = lower_bound(ALL(node), edge[i].q) - begin(node);
		E[u].PB({v,edge[i].w});
		E[v].PB({u,edge[i].w});
	}

	ans = INF;
	REP(i,M) {
		calc(edge[i].u, edge[i].v, edge[i].w);
	}
	if (ans == INF) ans = 0;
}
int main() {
	IOS;
	int nT;
	cin>>nT;
	REP1(cas,1,nT) {
		input();
		solve();
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}

	return 0;
}

