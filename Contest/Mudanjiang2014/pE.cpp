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

const int MX = 555;
vector<vector<int>> ans[MX];
//int ans[MX][MX][MX];


void pre() {
	for (int i=0; i<MX; i++) {
		int n = i+1;
		ans[i].resize(n);
		for (int j=0; j<n; j++)
			ans[i][j].resize(n);
	}
	ans[1][0][0] = 1;

	ans[2][0][0] = 1; ans[2][0][1] = 4;
	ans[2][1][0] = 2; ans[2][1][1] = 3;

	ans[3][0][0] = 1; ans[3][0][1] = 2; ans[3][0][2] = 9;
	ans[3][1][0] = 4; ans[3][1][1] = 3; ans[3][1][2] = 8;
	ans[3][2][0] = 5; ans[3][2][1] = 6; ans[3][2][2] = 7;

	for (int n=4; n<=512; n++) {
		if (n&1) {
			for (int x=0; x<n; x++) {
				ans[n][x][0] = x*2+1;
				ans[n][x][1] = x*2+2;
				if (x & 1) {
					swap(ans[n][x][0], ans[n][x][1]);
				}
			}

			int n2 = n*2;
			for (int y=0; y<n-2; y++) {
				ans[n][n-2][y+2] = n2+y*2+1;
				ans[n][n-1][y+2] = n2+y*2+2;
				if (!(y & 1)) {
					swap(ans[n][n-2][y+2], ans[n][n-1][y+2]);
				}
			}
		} else {
			for (int x=0; x<n; x++) {
				ans[n][x][0] = x*2+1;
				ans[n][x][1] = x*2+2;
				if ((x & 1)) {
					swap(ans[n][x][0], ans[n][x][1]);
				}
			}
			swap(ans[n][n-1][0], ans[n][n-2][1]);

			int n2 = n*2;
			for (int y=0; y<n-2; y++) {
				ans[n][n-2][y+2] = n2+y*2+1;
				ans[n][n-1][y+2] = n2+y*2+2;
				if ((y & 1)) {
					swap(ans[n][n-2][y+2], ans[n][n-1][y+2]);
				}
			}
		}

		for (int i=0; i<n-2; i++) {
			for (int j=0; j<n-2; j++) {
				int ti = j, tj = -i+n-1;
				ans[n][ti][tj] = (n-2)*(n-2)+1 - ans[n-2][i][j] + n*4-4;
			}
		}

	}
}



int main() {
    IOS;

	pre();

	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				cout << ans[N][i][j] << " \n"[j==N-1];
			}
		}
	}

    return 0;
}
