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

typedef long long i64;
typedef pair<int, int> pii;
i64 const M = 1000000009;
const int MX = 3010101;

int N, R;
int B;
vector<pii> rel[2];
vector<pii> must;
i64 fact[MX];
bool vt[MX];

i64 fpow(i64 a, int b) {
	if (b == 0) return 1;
	i64 ret = fpow(a, b/2);
	ret = (ret * ret) % M;
	if (b&1) ret = (ret * a) % M;
	return ret;
}

i64 inv(i64 a) {
	return fpow(a, M-2);
}

void pre() {
	fact[0] = 1;
	for (int i=1; i<MX; i++) {
		fact[i] = (fact[i-1] * i) % M;
	}
}

int dfs(int a) {
	vt[a] = true;
	int ret = 0;
	for (auto p: must) {
		int u = p.F, v = p.S;
		if (v == a) swap(u, v);
		if (u != a) continue;
		if (vt[v]) continue;
		ret += dfs(v);
	}
	return ret + 1;
}

i64 calc() {
	for (auto p: must) {
		vt[p.F] = false;
		vt[p.S] = false;
	}
	int c[5] = {0, 0, 0, 0, 0};

	for (auto p: must) {
		int u = p.F;
		if (not vt[u]) {
			int t = min(dfs(u), 4);
			c[t] ++;
		}
	}


	if (c[4] > 0) return 0;

	c[1] = N*3 - c[3]*3 - c[2]*2;

	if (c[2] > c[1]) return 0;
	
	i64 ret = fact[c[1]];
	ret = (ret * inv(fact[c[1]-c[2]])) % M;
	int c1 = c[1] - c[2];
	ret = (ret * fact[c1]) % M;
	ret = (ret * inv(fpow(6, c1/3))) % M;
	ret = (ret * inv(fact[c1/3])) % M;

	return ret;
}

int main() {
	pre();
	IOS;
	cin >> N >> R;

	for (int i=0; i<R; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		rel[c].PB(MP(a, b));
	}
	B = rel[1].size();
	i64 ans = 0;
	for (int i=0; i<(1<<B); i++) {
		//cout << i << endl;
		int pc = __builtin_popcount(i);

		must.clear();
		for (auto p: rel[0]) must.PB(p);

		for (int j=0; j<B; j++) {
			if ((1<<j) & i) {
				must.PB(rel[1][j]);
			}
		}
		i64 a = calc();
		//cout << "A = " << a << endl;

		if (pc & 1) ans = (ans + M - a) % M;
		else ans = (ans + a) % M;
	}
	cout << ans << endl;
	return 0;
}

