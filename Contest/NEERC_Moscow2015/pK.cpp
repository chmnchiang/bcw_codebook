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

const int MXN = 200005;

int N, M, vst[MXN], deg[MXN];
vector<int> E[MXN], ans;

int main() {
	IOS;
	cin >> N >> M;
	for (int i=0, u, v; i<M; i++) {
		cin >> u >> v;
		E[v].PB(u);
		deg[u]++;
	}
	set<int> pq;
	for (int i=1; i<=N; i++) {
		if (!deg[i]) pq.insert(i);
	}
	while (!pq.empty()) {
		int u = *pq.rbegin();
		ans.PB(u);
		pq.erase(u);
		for (auto v : E[u]) {
			deg[v]--;
			if (!deg[v]) pq.insert(v);
		}
	}
	reverse(ALL(ans));
	for (int i=0; i<N; i++) {
		cout << ans[i] << " \n"[i==N-1];
	}

    return 0;
}

