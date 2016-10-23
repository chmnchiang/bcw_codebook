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


#define int long long
typedef pair<int,int> pii;
const int MXN = 100005;
const int INF = 1LL<<60;

struct Item {
	int p,v,d;
	bool operator < (const Item &he) const {
		return d > he.d;
	}
};


int N,K,L;
pii dis[MXN][2]; // (distance , people)
vector<pii> E[MXN];
pii edge[MXN];
int length[MXN];
priority_queue<Item> pq;


bool update(Item a) {
	if (dis[a.v][0].F > a.d) {
		dis[a.v][1] = dis[a.v][0];
		dis[a.v][0] = {a.d,a.p};
		return true;
	} else if (dis[a.v][1].F > a.d and dis[a.v][0].S != a.p) {
		dis[a.v][1] = {a.d,a.p};
		return true;
	}
	return false;
}
int32_t main() {
	IOS;
	cin >> N >> K >> L;
	REP1(i,1,N) {
		int v;
		cin >> v;
		pq.push({i,v,0});
	}
	REP1(i,1,L) {
		int a,b,c;
		cin >> a >> b >> c;
		E[a].PB({b,c});
		E[b].PB({a,c});
		edge[i] = {a,b};
		length[i] = c;
	}
	REP1(i,1,K) {
		dis[i][0] = dis[i][1] = {INF,INF};
	}
	while (!pq.empty()) {
		Item item = pq.top(); pq.pop();
		if (update(item)) {
			int u = item.v;
			for (auto it:E[u]) {
				Item c = item;
				c.v = it.F;
				c.d += it.S;
				pq.push(c);
			}
		}
	}

	int ans = INF;
	REP1(i,1,K) {
		if (dis[i][0].F != INF and dis[i][1].F != INF) {
			ans = min(ans, (dis[i][0].F + dis[i][1].F) * 60 / 10);
		}
		//cout << i << " : " << dis[i][0] << " " << dis[i][1] << endl;
	}

	REP1(i,1,L) {
		int u = edge[i].F;
		int v = edge[i].S;
		REP(j,2) REP(k,2) {
			if (dis[u][j].F == INF) continue;
			if (dis[v][k].F == INF) continue;
			if (dis[u][j].S == dis[v][k].S) continue;
			ans = min(ans, (dis[u][j].F+dis[v][k].F+length[i])*60/20);
		}

	}

	cout << ans << endl;

	return 0;
}
