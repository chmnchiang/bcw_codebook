#include <bits/stdc++.h>
using namespace std;

const int MX = 312;
typedef pair<int, int> pii;
typedef pair<pii, int> p3i;
int N;
string s;
map<char, pii> dir;
map<p3i, int> walk;
char mp[MX][MX];
const int MM = 10234567;
pii seq[MM];
int kmp[MM];

int answer(int l, int r) {
	int q = -1;
	kmp[l] = q;
	for (int i=l+1; i<r; i++) {
		int ii = i - l;
		while (q != -1 and seq[l+q+1] != seq[i]) {
			q = kmp[l+q];
		}
		if (seq[l+q+1] == seq[i])
			q ++;
		
		kmp[i] = q;
	}

	int len = r - l;
	int ans = r - l;
	int j = kmp[r-1];
	while (j != -1) {
		int jj = j + 1;
		int jjj = (len - jj);
		if (len % jjj == 0) {
			ans = min(ans, jjj);
		}
		j = kmp[l+j];
	}
	return ans;
}

int main() {


	ios_base::sync_with_stdio(0);

	dir['>'] = {0, 1};
	dir['^'] = {-1, 0};
	dir['<'] = {0, -1};
	dir['v'] = {1, 0};

	cin >> N;
	cin >> s;

	for (int i=0; i<N; i++) {
		cin >> mp[i];
	}

	int si, sj;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
				if (mp[i][j] == 'R') {
			si = i; sj = j; break;
				}
		}
	}

	int len = s.length(), now = 0;
	auto inr = [&] (int x, int y) -> bool {
		if (x < 0 or x >= N) return false;
		if (y < 0 or y >= N) return false;
		return true;
	};
	int cnt = 0;
	int hal = 0;
	while(true) {
		int dx, dy;
		tie(dx, dy) = dir[s[now]];
		int nx, ny;
		tie(nx, ny) = pii{si+dx, sj+dy};
		if (not inr(nx, ny) or mp[nx][ny] == '#') {
			hal ++;
		} else {
			si = nx;
			sj = ny;
			cnt ++;
			hal = 0;
			p3i ns = {{si, sj}, now};
			if (walk.count(ns)) {
				int t = walk[ns];
				cout << answer(t, cnt) << endl;
				return 0;
			}
			walk[ns] = cnt;
			seq[cnt] = {si, sj};
		}
		if (hal >= len) {
			cout << 1 << endl;
			return 0;
		}
		now ++;
		if (now >= len) now -= len;
	}
	

	return 0;
}

