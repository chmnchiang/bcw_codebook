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

typedef long long LL;

const int MXN = 100005;
const LL MOD = 21092013;

int trash;
int N;
LL ans[55], L[MXN], H[MXN], g[MXN][55];
int gcdTable[55][55];
vector<int> E[MXN];

inline int gcd(int a, int b) {
	return gcdTable[a][b];
}
void input() {
	trash = scanf("%d", &N);
	for (int i=1; i<=N; i++) E[i].clear();
	for (int i=0, u, v; i<N-1; i++) {
		trash = scanf("%d%d", &u, &v);
		E[u].PB(v);
		E[v].PB(u);
	}
	for (int i=1; i<=N; i++) {
		trash = scanf("%lld", &L[i]);
	}
	for (int i=1; i<=N; i++) {
		trash = scanf("%lld", &H[i]);
	}
}

inline void add(LL a[], LL b[]) {
	for (int i=1; i<=50; i++) {
		a[i] += b[i];
		if (a[i] >= MOD) a[i] -= MOD;
	}
}

void DFS(int u, int f) {
	LL tG[55] = {0};
	for (int k=L[u]; k<=H[u]; k++) {
		ans[k]++;
		tG[k]++;
	}
	for (auto v : E[u]) {
		if (v == f) continue;
		DFS(v, u);
		for (int k=1; k<=50; k++) {
			for (int i=1; i<=50; i++) {
				int gg = gcd(i, k);
				ans[gg] += g[v][i] * tG[k];
				ans[gg] %= MOD;
			}
		}
		for (int k=L[u]; k<=H[u]; k++) {
			for (int i=1; i<=50; i++) {
				int gg = gcd(i, k);
				tG[gg] += g[v][i];
				tG[gg] %= MOD;
			}
		}
	}
	for (int i=1; i<=50; i++)
		g[u][i] = tG[i];
}

void solve() {
	FZ(ans);
	FZ(g);
	DFS(1, 0);
	for (int i=1; i<=50; i++) {
		ans[i] %= MOD;
		printf("%d: %lld\n", i, ans[i]);
	}

}

int main() {
	for (int i=0; i<55; i++) {
		for (int j=0; j<55; j++) {
			gcdTable[i][j] = __gcd(i, j);
		}
	}
	int nT;
	trash = scanf("%d", &nT);
	for (int t=1; t<=nT; t++) {
		input();
		printf("Case %d:\n", t);
		solve();
	}

	return 0;
}

