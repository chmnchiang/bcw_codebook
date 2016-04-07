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

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); ((i) += ((a)<(b) ? 1 : -1)))

const int MX = 333333;
int V, E;
vector<int> el[MX];


int dfn[MX], low[MX], did;
bool isc[MX];
void dfs(int u, int fa=-1) {
	dfn[u] = low[u] = ++did;
	int cnt = 0;
	for (auto v: el[u]) {
		if (v == fa) continue;

		if (!dfn[v]) {
			cnt++;
			dfs(v, u);
			low[u] = min(low[u], low[v]);
      if (low[v] >= dfn[u] && u != 1) isc[u] = 1;
    } else low[u] = min(low[u], dfn[v]);
	}

	if (u == 1) {
		if (cnt > 1) isc[u] = 1;
		return;
	}
/*
	for (auto v: el[u]) {
		if (v == fa) continue;
		if (low[v] >= dfn[u]) {
			isc[u] = 1;
			return;
		}
	}  */
}

set<int> st;
bool vt[MX];
int dfs2(int u) {
	if (isc[u]) {
		if (SZ(st) < 2)
			st.insert(u);
		return 0;
	}

	vt[u] = 1;
	int s = 1;
	for (auto v: el[u]) {
		if (vt[v]) continue;
		s += dfs2(v);
	}
	return s;
}

void deinit() {
	loop (i, 0, V+3) el[i].clear();
	fill(vt, vt+V+3, 0);
	fill(isc, isc+V+3, 0);
	fill(dfn, dfn+V+3, 0);
	fill(low, low+V+3, 0);
	st.clear();

	did=0;
}

int main() {
	IOS;

	int cas=0;
	while (true) {

		cin >> E;
		if (!E) break;
		V = 0;
		loop (i, 0, E) {
			int u, v; cin >> u >> v;
			assert(u <= MX);
			assert(v <= MX);
			V = max(V, max(u, v));
			el[u].PB(v);
			el[v].PB(u);
		}

		loop (i, 1, V+1) {
			assert(SZ(el[i]));
		}


		did=0;
		dfs(1);
		//loop (i, 1, V+1) if(isc[i]) cout << i << ' '; cout << endl;

		int a1=0;
		long long a2 = 1;

		loop (i,1,V+1) {
			if (isc[i] or vt[i]) continue;
			st.clear();
			int t = dfs2(i);

			if (SZ(st) == 1) {
				a1++;
				a2 *= t;
			}
		}

		if (!a1) {
			a1 = 2;
			a2 = 1LL * V * (V-1) / 2;
		}
		

		cas++;
		cout << "Case " << cas << ": " << a1 << ' ' << a2 << endl;

		deinit();
	}

	return 0;
}
