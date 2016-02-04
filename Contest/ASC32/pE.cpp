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


const int MX = 333;
vector<int> el[MX];

int mem[MX][MX][2];
bool vt[MX][MX][2];
int dp(int con, int yee, int left) {
	if (con + yee == 1) return 0;

	if (vt[con][yee][left]) return mem[con][yee][left];

	bool yes = 0;
	vt[con][yee][left] = true;
	if (con >= 2) {
		yes |= not dp(con-1, yee, !left);
	}
	if (yee >= 2)
		yes |= not dp(con+1, yee-2, left);
	if (con and yee)
		yes |= not dp(con-1, yee, !left);
	if (left)
		yes |= not dp(con, yee, !left);

	return (mem[con][yee][left] = yes);
}

bool visit[MX];

int dfs(int u) {
	visit[u] = true;
	int t = 0;
	for (auto v: el[u]) {
		if (not visit[v]) 
			t += dfs(v);
	}
	return t + 1;
}

int main() {
	IOS;
	FILEIO("points");

	int V, E;
	cin >> V >> E;
	for (int i=0; i<E; i++) {
		int a, b;
		cin >> a >> b;
		el[a].PB(b);
		el[b].PB(a);
	}

	int con = 0, yee = 0, left = 0;
	for (int i=1; i<=V; i++) {
		if (not visit[i])  {
			int t = dfs(i);
			if (t & 1) yee += 1;
			else con ++;

			int m = t % 4;
			if (m == 2 or m == 3)
				left ++;
		}
	}

	left = (left + E) % 2;

	if (con + yee <= 1) {
		cout << "Betty" << endl;
	} else {
		bool res = dp(con, yee, left);
		cout << (res ? "Andrew" : "Betty") << endl;
	}

    return 0;
}

