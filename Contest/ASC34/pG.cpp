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

const int MX = 8300;

int nMem;
int N, H, tag[MX], st[MX], term[MX], E[MX][2], merged[MX];
bitset<MX> dp[MX], done[MX];
vector<int> S[MX];

int go(int x, int y) {
	if (x >= N || y >= N) return 1;
	if (tag[x] != tag[y]) return 0;
	if (done[x][y]) return dp[x][y];

	done[x][y] = 1;
	int lx = x * 2 + 1;
	int rx = x * 2 + 2;
	int ly = y * 2 + 1;
	int ry = y * 2 + 2;
	if (go(lx, ly) && go(rx, ry)) {
		dp[x][y] = 1;
	}

	return dp[x][y];
}

int main() {
	nMem = 0;
	IOS;
	FILEIO("learning");
	cin >> H;
	N = (1<<(H+1)) - 1;
	for (int i=0; i<N; i++) {
		string str;
		cin >> str;
		if (str[0] == '+') tag[i] = 2;
		else tag[i] = 1;
		merged[i] = 0;
	}
	for (int i=0; i<N; i++) {
		if (merged[i]) continue;
		st[i] = ++nMem;
		if (tag[i] == 2) term[nMem] = 1;
		S[nMem].PB(i);
		for (int j=i+1; j<N; j++) {
			if (!merged[j] && go(i,j)) {
				merged[j] = 1;
				st[j] = nMem;
				S[nMem].PB(j);
			}
		}
	}

	for (int i=0; i<N; i++) {
		int s = st[i];
		if (!E[s][0] && i*2+1 < N) {
			E[s][0] = st[i*2+1];
		}
		if (!E[s][1] && i*2+2 < N) {
			E[s][1] = st[i*2+2];
		}
	}
	for (int s=1; s<=nMem; s++) {
		if (!E[s][0]) E[s][0] = s;
		if (!E[s][1]) E[s][1] = s;
	}

	cout << nMem << " " << st[0] << endl;
	vector<int> vec;
	for (int i=1; i<=nMem; i++) {
		if (term[i]) vec.PB(i);
	}
	cout << SZ(vec);
	for (auto v:vec)
		cout << " " << v;
	cout << endl;
	for (int i=1; i<=nMem; i++)
		cout << E[i][0] << " " << E[i][1] << "\n";

	return 0;
}
