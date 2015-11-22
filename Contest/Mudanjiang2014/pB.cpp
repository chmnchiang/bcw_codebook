#include<bits/stdc++.h>
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

typedef pair<int,int> pii;
const int MX = 200005;

int N, dep[MX], fa[MX], tag[MX], vst[MX];
vector<int> E[MX], leaf;

void DFS(int u, int f, int d) {
	dep[u] = d;
	fa[u] = f;
	for (auto v : E[u]) {
		if (v == f) continue;
		DFS(v, u, d+1);
	}
}

int cen;
int farest;
int best, A, B;
int dp[MX];

int go(int u, int f) {
	int a, b;
	a = b = -1;
	for (auto v : E[u]) {
		if (v == f) continue;
		int t = go(v, u);
		if (t != -1) {
			t++;
			if (t > a) {
				b = a;
				a = t;
			} else if (t > b) {
				b = t;
			}
		}
	}
	if (tag[u]) a = max(a, 0);
	if (a != -1 && b != -1) {
		if (a + b > farest) {
			best = u;
			farest = a + b;
			A = a;
			B = b;
		}
	} else if (a != -1 && tag[u]) {
		if (a > farest) {
			best = u;
			farest = a;
			A = a;
			B = 0;
		}
	}
	dp[u] = a;
	return a;
}

bool checkOK(int len) {
	int choose = 1, d=0;
	for (auto it : leaf) {
		if (dep[it] > d) {
			choose = it;
			d = dep[it];
		}
	}
	if (d < len) {
		best = choose = 1;
		A = B = 0;
		return true;
	}
	int st = choose;
	for (int i=0; i<len; i++) {
		st = fa[st];
	}
	for (int i=1; i<=N; i++) {
		tag[i] = 1;
		vst[i] = 0;
	}
	cen = st;
	tag[st] = 0;
	vst[st] = 1;
	queue<int> que;
	if (vst[st] <= len)
		que.push(st);
	while (!que.empty()) {
		int u = que.front(); que.pop();
		for (auto v : E[u]) {
			if (vst[v]) continue;
			vst[v] = vst[u] + 1;
			tag[v] = 0;
			if (vst[v] <= len) que.push(v);
		}
	}
	farest = -1;
	go(1, 1);
/*
	cout << "LEN " << len << endl;
	cout << farest << endl;
	for (int i=1; i<=N; i++)
		cout << "#" << i << ": " << tag[i] << endl;
*/
	return (farest+1)/2 <= len;
}

pii getAns(int len) {
	checkOK(len);
	int x = (A-B) / 2;
	int u = best;
	while (x--) {
		A--;
		for (auto v : E[u]) {
			if (dp[v] == A) {
				u = v;
				break;
			}
		}
	}

	while (cen == u) {
		u = u%N+1;
	}

	return {cen, u};
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> N;
		leaf.clear();
		for (int i=1; i<=N; i++) E[i].clear();
		for (int i=0, u, v; i<N-1; i++) {
			cin >> u >> v;
			E[u].PB(v);
			E[v].PB(u);
		}
		DFS(1, 1, 0);
		for (int i=1; i<=N; i++) {
			if (SZ(E[i]) == 1) leaf.PB(i);
		}
		int l = 0, r = N;
		while (l < r) {
			int mid = (l + r) / 2;
			if (checkOK(mid)) r = mid;
			else l = mid+1;
		}
		pii ans = getAns(l);
		cout << l << " " << ans.F << " " << ans.S << endl;
	}

	return 0;
}

