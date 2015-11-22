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

const int MXN = 100005;

struct DisjointSet {
	int n, fa[MXN];
	void init(int _n) {
		n = _n;
		for (int i=0; i<=n; i++)
			fa[i] = i;
	}
	int f(int x){ return x == fa[x] ? x : fa[x] = f(fa[x]); }
	void uni(int x, int y) {
		if (!f(x)) return ;
		if (!f(y)) return ;
		fa[f(x)] = f(y);
	}
}djs;

struct Query {
	string cmd;
	int x, y;
}qry[MXN];

int nT, N, Q, fa[MXN], bye[MXN];
vector<int> E[MXN];

void input() {
	cin >> N >> Q;
	for (int i=0; i<=N; i++) {
		bye[i] = 0;
		E[i].clear();
	}
	for (int i=1; i<=N; i++) {
		cin >> fa[i];
		E[fa[i]].PB(i);
	}
	for (int i=1; i<=Q; i++) {
		cin >> qry[i].cmd;
		if (qry[i].cmd == "Q") {
			cin >> qry[i].x >> qry[i].y;
		} else {
			cin >> qry[i].x;
			bye[qry[i].x]++;
		}
	}
}

void solve(int t) {
	djs.init(N);
	for (int i=1; i<=N; i++) {
		if (bye[i] == 0 && fa[i] != 0) {
			djs.uni(i, fa[i]);
		}
	}
	cout << "Case #" << t << ":\n";
	vector<int> ans;;
	for (int i=Q; i>=1; i--) {
		int x = qry[i].x;
		int y = qry[i].y;
		if (qry[i].cmd == "Q") {
			if (djs.f(x) == djs.f(y)) {
				ans.PB(1);
			} else {
				ans.PB(0);
			}
		} else {
			bye[x]--;
			if (!bye[x]) {
				djs.uni(x, fa[x]);
			}
		}
	}
	reverse(ALL(ans));
	for (auto it : ans) {
		if (it) cout << "YES\n";
		else cout << "NO\n";
	}
}

int main() {
	IOS;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		input();
		solve(t);
	}

    return 0;
}

