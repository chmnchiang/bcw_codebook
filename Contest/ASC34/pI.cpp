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
// Let's Fight!

const int MX = 212121;
int N;
vector<int> el[MX];

int tdp[MX][3];
int dp[MX][2];

void dfs(int u, int fa) {
	for (auto v: el[u]) {
		if (v == fa) continue;
		dfs(v, u);
	}

	auto t = tdp[u];
	t[0] = t[1] = t[2] = 0;
	for (auto v: el[u]) {
		if (v == fa) continue;

		int temp[3] = {};
		for (int i=0; i<3; i++) {
			temp[i] = max(temp[i], t[i] + dp[v][0]);
		}
		for (int i=0; i<2; i++) {
			temp[i+1] = max(temp[i+1], t[i] + dp[v][1]+1);
		}
		for (int i=0; i<3; i++) {
			t[i] = temp[i];
		}
	}

	
	dp[u][0] = max(max(tdp[u][0], tdp[u][1]), tdp[u][2]);
	dp[u][1] = max(tdp[u][0], tdp[u][1]);
}

int main() {
	IOS;
	FILEIO("tour");
	cin >> N;
	for (int i=0; i<N-1; i++) {
		int a, b;
		cin >> a >> b;
		el[a].PB(b);
		el[b].PB(a);
	}
	
	dfs(1, -1);
	cout << N - dp[1][0] << endl;

    return 0;
}
