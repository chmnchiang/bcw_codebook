#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

struct ed {
	int u, v, c, id;
	bool operator < (const ed &e) const {
		return c < e.c;
	}
};
typedef pair<int, int> pii;
const int MX = 555;
const int ME = 55555;
int V, E;
vector<ed> edges;
int djs[MX];
vector<ed> el[MX];
bool good[ME];

int ffa(int a) {
	return (djs[a] == a ? a : (djs[a] = ffa(djs[a])));
}
stack<pii> st;
bool dfs(int v, int fa, int tar, int c) {
	if (v == tar) {
		while (st.size()) {
			int cn, id;
			tie(cn, id) = st.top(); st.pop();
			if (c <= cn) {
				good[id] = 0;
			}
		}
		return true;
	}

	for (auto x: el[v]) {
		int u = x.v;
		if (u == fa) continue;
		st.push({x.c, x.id});
		if (dfs(u, v, tar, c)) return true;
		st.pop();
	}
	return false;
}

int main() {
	IOS;
	cin >> V >> E;
	for (int i=0; i<=V; i++) {
		djs[i] = i;
	}
	for (int i=0; i<E; i++) {
		int a, b, c; cin >> a >> b >> c;
		edges.PB({a, b, c, i});
	}
	sort(ALL(edges));

	for (int i=0; i<E; i++) {
		int u = edges[i].u, v = edges[i].v;
		int id = edges[i].id;
		if (ffa(u) != ffa(v)) {
			djs[ffa(u)] = ffa(v);
			good[id] = true;
			el[u].PB({u, v, edges[i].c, id});
			el[v].PB({v, u, edges[i].c, id});
		}
	}

	for (int i=0; i<E; i++) {
		int u = edges[i].u, v = edges[i].v;
		int id = edges[i].id;
		if (not good[id]) {
		//cout << u << ' ' << v << endl;
			dfs(u, -1, v, edges[i].c);
		}
	}

	int a1 = 0, a2 = 0;
	for (int i=0; i<E; i++) {
		if (good[edges[i].id]) {
			a1 ++;
			a2 += edges[i].c;
		}
	}
	cout << a1 << ' ' << a2 << endl;

    return 0;
}

