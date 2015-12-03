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

typedef long long LL;

const int MXN = 514;
const int INF = 1029384756;
const LL H = 13331;
const LL MOD = 1010101333;

struct Edge {
	int u, v;
	vector<int> nxt;
}eg[MXN];

struct State {
	int id, dis;
	vector<int> vec;
};

int N, M, K, extra;
int dis[MXN];
set<LL> app;
queue<State> que;

LL getHash(const vector<int> &vec) {
	LL h = 0;
	for (auto v : vec) {
		h = (h*H+v) % MOD;
	}
	return h;
}
void push(const vector<int> &vec, int eid, int d) {
	LL h = getHash(vec);
	if (app.count(h)) return;
	app.insert(h);
	que.push({eid, d, vec});
}
bool canWalk(const vector<int> &vec, int x) {
	int len = SZ(vec);
	for (int i=1; i<=K; i++) {
		if (vec[len-i] == x) return false;
	}
	return true;
}
vector<int> walk(vector<int> vec, int x) {
	vector<int> res = vec;
	for (int i=0; i<SZ(res)-1; i++)
		res[i] = res[i+1];
	res[SZ(res)-1] = x;
	return res;
}

int main() {
	IOS;
	cin >> N >> M >> K;
	extra = K * 25;
	K = (K-1) / 40;
	for (int i=1; i<=M; i++) {
		cin >> eg[i].u >> eg[i].v;
		int c;
		cin >> c;
		while (c--) {
			int x;
			cin >> x;
			eg[i].nxt.PB(x);
		}
	}
	for (int i=1; i<=N; i++) {
		dis[i] = INF;
	}
	dis[1] = 0;
//	cout << "N, K = " << N << " " << K << endl;
	vector<int> state;
	for (int i=0; i<12; i++) state.PB(0);
	state.back() = 1;
	for (int i=1; i<=M; i++) {
		if (eg[i].u == 1) {
//			cout << walk(state, eg[i].v) << endl;
			push(walk(state, eg[i].v), i, 1);
			dis[eg[i].v] = 1;
		}
	}
	
	while (!que.empty()) {
		if (dis[N] != INF) break;
		auto cur = que.front(); que.pop();
		int cid = cur.id;
		vector<int> vec = cur.vec;
//		cout << vec << endl;
		for (auto eid : eg[cid].nxt) {
//			cout << "check " << eid << " " << eg[eid].u << " " << eg[eid].v << endl;
			int v = eg[eid].v;
			if (canWalk(vec, v)) {
				dis[v] = min(dis[v], cur.dis+1);
				push(walk(vec, v), eid, cur.dis+1);
			}
		}
	}
	LL ans = 1LL * dis[N]*1000 + extra;
	if (dis[N] == INF) cout << "No chance\n";
	else cout << ans << "\n";

    return 0;
}

