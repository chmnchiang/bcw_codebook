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

typedef pair<int, int> pii;
const int MX = 2020;
int N, M;
vector<pii> el[MX];
vector<long long> ans;
int val[MX], best[MX], father[MX];
int len[MX];

void dfs(int v, int c=0, int fa=-1) {
	len[v] = c;
	best[v] = -1;
	father[v] = fa;
	for (auto p: el[v]) {
		int u = p.F, snc = p.S;
		if (u == fa) continue;
		dfs(u, snc, v);
		if (len[u] + c > len[v]) {
			len[v] = len[u]+c;
			best[v] = u;
		}
	}
	//cout << "best : " << v << ' ' << len[v] << endl;
}

bool us[MX];
void calc(int v) {
	memset(us, 0, sizeof(us));
	priority_queue<pii> pq;

	dfs(v);
	//cout << "len = " << len[v] << endl;
	for (auto p: el[v]) {
		int u = p.F;
		pq.push(MP(len[u], u));
	}

	while (pq.size()) {
		pii p = pq.top(); pq.pop();
		int u = p.S;

		if (us[u]) continue;

		//cout << v << " -> " << p.F << endl;
		ans.PB(1LL*p.F*val[v]);

		while (u != -1) {
			us[u] = true;
			for (auto p_: el[u]) {
				int w = p_.F;
				if (w == father[u] or w == best[u]) continue;
				if (us[w]) continue;
				pq.push(MP(len[w], w));
			}
			u = best[u];
		}

	}

}

int main() {
	IOS;
	cin >> N >> M;

	for (int i=0; i<N-1; i++) {
		int a, b, c;
		cin >> a >> b >> c; a--; b--;
		el[a].PB(MP(b, c));
		el[b].PB(MP(a, c));
	}

	for(int i=0; i<N; i++) cin >> val[i];

	for (int i=0; i<N; i++) {
		calc(i);
	}

	sort(ans.begin(), ans.end());
	reverse(ans.begin(), ans.end());

	M = min(M, (int)ans.size());
	long long a = 0;
	for (int i=0; i<M; i++) {
		a += ans[i];
	}
	cout << a << endl;
	return 0;
}

