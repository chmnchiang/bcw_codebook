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

typedef pair<int,int> pii;
typedef long long ll;
const int MX = 100005;
struct Event {
	int id;
	ll t,k;
	friend ostream& operator << (ostream &s, Event he) {
		return s << "[" << he.id << "," << he.t << "," << he.k << "]";
	}
};

int N;
ll ipt[MX],ipk[MX],T[MX],K[MX];
vector<pii> E[MX];
vector<Event> vec[MX];
ll cost,curt;
vector<pii> ans;
map<pii,ll> edge;

bool comp(Event a, Event b) {
	return a.t * b.k < b.t * a.k;
}
void DFS(int u, int f) {
	T[u] = ipt[u];
	K[u] = ipk[u];
	vec[u].PB({u,T[u],K[u]});
	for (auto it:E[u]) {
		int v = it.F;
		ll w = it.S;
		if (v == f) continue;
		DFS(v,u);
		T[u] += T[v] + 2*w;
		K[u] += K[v];
		vec[u].PB({v,T[v]+2*w,K[v]});
	}
	sort(ALL(vec[u]), comp);
}
void go(int u, int f) {
	for (auto it:vec[u]) {
		if (it.id == u) {
			curt += ipt[u];
			cost += curt * ipk[u];
			ans.PB({0,u});
		} else {
			int v = it.id;
			curt += edge[pii(u,v)];
			ans.PB({1,v});
			go(v,u);
		}
	}
	ans.PB({1,f});
	curt += edge[pii(u,f)];
}
int main() {
	IOS;
	FILEIO("beetles");
	cin >> N;
	REP1(i,1,N) cin >> ipt[i];
	REP1(i,1,N) cin >> ipk[i];
	REP1(i,1,N-1) {
		int u,v,w;
		cin >> u >> v >> w;
		E[u].PB({v,w});
		E[v].PB({u,w});
		edge[pii(u,v)] = edge[pii(v,u)] = w;
	}
	DFS(1,1);
	cost = curt = 0;
	go(1,1);
	cout << cost << endl;
	ans.pop_back();
	for (auto it:ans) {
		if (it.F == 0) {
			cout << "P " << it.S << "\n";
		} else {
			cout << "M " << it.S << "\n";
		}
	}


	return 0;
}

