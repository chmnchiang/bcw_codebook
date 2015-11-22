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

typedef unsigned long long ll;
const int MXN = 100005;

int N, fa[MXN], sz[MXN];
vector<int> E[MXN];
ll A[MXN], f[MXN];

ll C(ll n) {
	return n * (n-1) / 2;
}

void DFS(int u, int father) {
	fa[u] = father;
	sz[u] = 1;
	for (auto v : E[u]) {
		if (v == father) continue;
		DFS(v, u);
		sz[u] += sz[v];
	}

	ll alpha = 0;
	for (auto v: E[u]) 
	{
		if (v == father) continue;
		alpha += C(sz[v]);
	}

	ll sumc = 0;
	A[u] = f[u] = 0;
	for (auto v: E[u])
	{
		if (v == father) continue;
		A[u] += A[v];
		A[u] += C(sz[v]) * C(sz[u]-sz[v]);
		A[u] -= C(sz[v]) * sumc;
		A[u] += f[v] * (sz[u]-sz[v]);
		sumc += C(sz[v]);
		f[u] += f[v];
		f[u] += sz[v] * (alpha - C(sz[v]));
	}
	f[u] += alpha;
}

int main() {
	IOS;
	cin >> N;
	for (int i=2, u, v; i<=N; i++) {
		cin >> u >> v;
		u--; v--;
		E[u].PB(v);
		E[v].PB(u);
	}
	DFS(0,0);

	ll ans = A[0];
	cout<<ans<<endl;

	return 0;
}

