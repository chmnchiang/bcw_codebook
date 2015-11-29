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
const int MXN = 20005;
const int INF = 1029384756;

struct Edge{ 
	int v, c, b;
};
struct set_t {
	int addC, addB;
	set<pii> st;
	void clear() {
		addC = addB = 0;
		st.clear();
		st.insert({0,0});
	}
	void insert(pii x) {
		x.F -= addC;
		x.S -= addB;
		auto iter = st.lower_bound(x);
		if (iter != st.begin()) {
			iter--;
			if (iter->S > x.S) return;
		}
//		cout << "INSERTING " << x.F << " " << x.S << endl;
		st.insert(x);
		while (true) {
			iter = st.lower_bound(x);
			iter++;
			if (iter == st.end()) break;
			if (iter->S <= x.S) st.erase(iter);
			else break;
		}

	}
	int size() { return st.size(); }
	int query(int c) {
		c -= addC;
		auto iter = st.lower_bound({c+1,-INF});
//		cout << "ITER END" << endl;
		if (iter == st.begin()) return 0;
		iter--;
//		cout << iter->F << " " << iter->S << endl;
		return iter->S + addB;
	}
	vector<pii> getALL() {
		vector<pii> ret;
		for (auto it : st) {
			ret.PB({it.F+addC, it.S+addB});
		}
		return ret;
	}
}st[MXN];

int N, stID[MXN], ans, C;
vector<Edge> E[MXN];

int merge(int a, int b) {
//	cout << "MERGE " << a << " " << b << endl;
	if (st[a].size() < st[b].size()) swap(a, b);
	vector<pii> vec = st[b].getALL();
	for (auto it : vec) {
//		cout << it << endl;
		if (it.F > C) continue;
		int remC = C - it.F;
		int tmp = st[a].query(remC);
		ans = max(ans, tmp + it.S);
	}
//	cout << "END QUERY" << endl;
	for (auto it : vec) {
		st[a].insert(it);
	}
	return a;
}

void DFS(int u, int f) {
//	cout << u << " " << endl;
	int id = stID[u];
	for (auto it : E[u]) {
		int v = it.v;
		if (v == f) continue;
//		cout << u << " " << v << endl;
		DFS(v, u);
		int vid = stID[v];
		st[vid].addC += it.c;
		st[vid].addB += it.b;
		id = merge(id, vid);
	}
	ans = max(ans, st[id].query(C));
	stID[u] = id;
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> N;
		for (int i=1; i<=N; i++) {
			E[i].clear();
			st[i].clear();
			stID[i] = i;
		}
		for (int i=1, u, v, c, b; i<=N-1; i++) {
			cin >> u >> v >> c >> b;
			E[u].PB({v,c,b});
			E[v].PB({u,c,b});
		}
		cin >> C;

		ans = 0;
		DFS(1, 1);
		cout << ans << "\n";
	}

	return 0;
}

