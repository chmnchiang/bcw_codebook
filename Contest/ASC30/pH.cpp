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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

const int MX = 205;

int N,M,ans;
bitset<MX> can[MX];
vector<int> E[MX];

void build() {
	ans = 0;
	REP1(i,1,N) can[i].reset();
	for (int i=N; i>=1; i--) {
		for (auto v:E[i]) {
			can[i] |= can[v];
			can[i][v] = 1;
		}
		ans += can[i].count();
	}
}

int main() {
	IOS;
	FILEIO("settling");
	cin >> N >> M;
	REP1(i,1,M) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
	}
	build();
	cout << ans << "\n";
	int Q;
	cin >> Q;
	while (Q--) {
		string cmd;
		int u,v;
		cin >> cmd >> u >> v;
		if (cmd == "?") {
			if (can[u][v]) cout << "YES\n";
			else cout << "NO\n";
		} else if (cmd == "+") {
			E[u].PB(v);
			build();
			cout << ans << "\n";
		} else {
			REP(i,SZ(E[u])) {
				if (E[u][i] == v) {
					swap(E[u][i], E[u].back());
					E[u].pop_back();
					break;
				}
			}
			build();
			cout << ans << "\n";
		}
	}

    return 0;
}
