#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MX = 1000005;

struct Segment {
	int a, l, r;
};

struct BIT {
	int bit[MX];
	void init() {
		FZ(bit);
	}
	int lb(int a) { return a & -a; }
	void add(int x, int v) {
		for (int i=x; i<MX; i+=lb(i))
			bit[i] += v;
	}
	int query(int x) {
		int ret = 0;
		for (int i=x; i>0; i-=lb(i))
			ret += bit[i];
		return ret;
	}
}bit;

int N, app[MX];
Segment seg[MX];

void input() {
	cin >> N;
	for (int i=1; i<=N; i++) {
		cin >> seg[i].a >> seg[i].l >> seg[i].r;
	}
}

bool comp(Segment a, Segment b) {
	if (a.r == b.r) return a.l < b.l;
	return a.r < b.r;
}

void solve() {
	FZ(app);
	bit.init();
	int ans = 0;
	for (int i=1; i<=N; i++) {
		int x = seg[i].a;
		if (!app[x]) {
			bit.add(x, 1);
			app[x] = 1;
			ans++;
		}
	}
	sort(seg+1, seg+1+N, comp);
	for (int i=1; i<=N; i++) {
		int c = bit.query(seg[i].r) - bit.query(seg[i].l-1);
		if (!c || (c == 1 && seg[i].l <= seg[i].a && seg[i].a <= seg[i].r)) {
			bit.add(seg[i].r, 1);
			ans++;
		}
	}
	cout << ans << "\n";
}

int main() {
	int nT;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		input();
		cout << "Case #" << t << ": ";
		solve();
	}

    return 0;
}

