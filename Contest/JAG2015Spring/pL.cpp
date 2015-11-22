#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) x.begin(), x.end()
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MX = 23;
int H, W;
char mp[MX][MX];
int mem[MX][MX][MX][MX];

int dp(int a, int b, int c, int d) {
	if (a == c or b == d) return 0;
	if (mem[a][b][c][d] != -1) return mem[a][b][c][d];

	vector<int> v;
	for (int i=a; i<c; i++) {
		for (int j=b; j<d; j++) {
			if (mp[i][j] == 'X') continue;
			int a1 = dp(a, b, i, j);
			int a2 = dp(i+1, b, c, j);
			int a3 = dp(a, j+1, i, d);
			int a4 = dp(i+1, j+1, c, d);
			v.PB(a1^a2^a3^a4);
		}
	}

	if (not v.size()) return mem[a][b][c][d] = 0;

	sort(ALL(v));
	v.resize(unique(ALL(v)) - v.begin());

	int sz = v.size();
	for (int i=0; i<sz; i++) {
		if (v[i] != i) return mem[a][b][c][d] = i;
	}
	return mem[a][b][c][d] = sz;
}

int main() {
	memset(mem, -1, sizeof(mem));

	scanf("%d%d", &H, &W);
	for (int i=0; i<H; i++) {
		scanf("%s", mp[i]);
	}

	cout << (dp(0, 0, H, W) == 0 ? "Second" : "First") << endl;
	return 0;
}

