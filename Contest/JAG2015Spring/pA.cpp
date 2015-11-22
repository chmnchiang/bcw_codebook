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

const int MXN = 100005;

struct {
	int sz;
	struct {
		int offset;
		map<int,int> mp;
		int query(int val) {
			val -= offset;
			if (!mp.count(val)) return 0;
			return mp[val];
		}
		void insert(int val, int c) {
			if (val >= 0) {
				val -= offset;
				mp[val] += c;
			}
		}
		void add() {
			offset++;
		}
		void sub() {
			offset--;
			if (mp.size()){
				auto it = mp.begin();
				if (it->F + offset < 0) {
					mp.erase(it);
				}
			}
		}
		void print() {
			for (auto it : mp) {
				if (it.S) {
					printf("%d : %d\n", it.F + offset, it.S);
				}
			}
		}
	}p, s;

}path[MXN];

int N, resID[MXN];
long long ans;
vector<int> E[MXN];
char str[MXN];

long long calc(int u, int v) {
	long long ret = 0;
	if (path[u].sz > path[v].sz) swap(u, v);
	for (auto it : path[u].p.mp) {
		int qval = it.F + path[u].p.offset;
		ret += 1ll * it.S * path[v].s.query(qval);
	}
	for (auto it : path[u].s.mp) {
		int qval = it.F + path[u].s.offset;
		ret += 1ll * it.S * path[v].p.query(qval);
	}
	return ret;
}
int merge(int u, int v) {
	if (path[u].sz > path[v].sz) swap(u, v);
	path[v].sz += path[u].sz;
	for (auto it : path[u].p.mp) {
		int val = it.F + path[u].p.offset;
		path[v].p.insert(val, it.S);
	}
	for (auto it : path[u].s.mp) {
		int val = it.F + path[u].s.offset;
		path[v].s.insert(val, it.S);
	}
	return v;
}

void DFS(int u, int f) {
	int &id = resID[u];
	for (auto v : E[u]) {
		if (v == f) continue;
		DFS(v, u);
		ans += calc(id, resID[v]);
		if (str[u] == '(') {
			path[resID[v]].p.add();
			path[resID[v]].s.sub();
		} else {
			path[resID[v]].p.sub();
			path[resID[v]].s.add();
		}
		id = merge(id, resID[v]);
	}
}

int main() {
	IOS;
	cin >> N;
	cin >> str;
	for (int i=0; i<N; i++) {
		resID[i] = i;
		if (str[i] == '(') {
			path[i].p.insert(1, 1);
		} else {
			path[i].s.insert(1, 1);
		}
		path[i].sz = 1;
	}
	for (int i=1, u, v; i<N; i++) {
		cin >> u >> v;
		u--; v--;
		E[u].PB(v);
		E[v].PB(u);
	}
	DFS(0, 0);
	cout << ans << endl;

	return 0;
}

