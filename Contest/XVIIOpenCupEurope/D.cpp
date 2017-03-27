#pragma GCC optimize ("O2")
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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
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


const char R = 'R';
const char D = 'D';
int dp[7][7];
vector<int> disc[7][7];

void out(int x, int y, char c, int t) {
	cout << x << ' ' << y << ' ' << c << ' ' << t << '\n';

	int nx = x, ny = y;
	if (c == R) {
		ny++;
	} else nx++;


	vector<int> vec;
	for (int i=0; i<t; i++) vec.PB(disc[x][y].back()), disc[x][y].pop_back();
	reverse(ALL(vec));

	for (auto i: vec) disc[nx][ny].PB(i);
}

void move(int x, int y, int a, int b) {
	while (x < a) {
		out(x, y, D, 1);
		x++;
	}

	while (y < b) {
		out(x, y, R, 1);
		y++;
	}
}

using pii = pair<int, int>;
void go(int x, int y) {
	if (x == 6 and y == 6) return;

	auto &cur = disc[x][y];
	if (cur.empty()) return;
	if (x == 6 and y == 5) {
		if (SZ(cur) == 1) {
			out(x, y, R, 1);
		} else {
		 	if (cur[0] > cur[1]) out(x, y, R, 2);
			else {
				out(x, y, R, 1);
				out(x, y, R, 1);
			}
		}
		return;
	}
	if (x == 5 and y == 6) {
		if (SZ(cur) == 1) {
			out(x, y, D, 1);
		} else {
		 	if (cur[0] > cur[1]) out(x, y, D, 2);
			else {
				out(x, y, D, 1);
				out(x, y, D, 1);
			}
		}
		return;
	}

	int n = SZ(cur);
	vector<pii> hao(n);
	for (int i=0; i<n; i++) {
		hao[i] = {cur[i], i};
	}
	sort(ALL(hao));
	reverse(ALL(hao));

	int id = 0;

	for (int i=6; i>=x; i--) {
		for (int j=6; j>=y; j--) {
			if (id > n) break;

			int t = dp[i][j];
			while (t and id < n) {
				hao[id++].F = i*100 + j;
				t--;
			}
		}
	}
	
	sort(ALL(hao), [](pii p1, pii p2) { return p1.S < p2.S; });

	for (int i=n-1; i>=0; i--) {
		int a = hao[i].F/100, b = hao[i].F%100;
		move(x, y, a, b);
	}


	for (int i=6; i>=x; i--) {
		for (int j=6; j>=y; j--) {
			go(i, j);
		}

	}

}

int main() {
	IOS;
	for (int i=6; i>=1; i--) {
		for (int j=6; j>=1; j--) {
			if (i == 6 and j == 6) {
				dp[i][j] = 1; continue;
			}
			dp[i][j] = 0;
			for (int x=i; x<=6; x++)
				for (int y=j; y<=6; y++) dp[i][j] += dp[x][y];
			if ((i == 6 and j == 5) or (i == 5 and j == 6)) dp[i][j] = 2;
		}
	}

	int N;
	cin >> N;

	for (int i=0; i<N; i++) {
		int x; cin >> x;
		disc[1][1].PB(x);
	}

	go(1, 1);


	return 0;
}

