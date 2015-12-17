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

int main() {
	FILEIO("gridbaglayout");
	IOS;

	const int MX = 1001;
	static int mp[MX][MX];
	static int fs[MX][MX];
	int H, W, K;
	cin >> H >> W >> K;

	typedef pair<int, int> pii;
	typedef pair<pii, pii> rect;

	vector<rect> grids(K+1);

//	W = H = 0;
	int mH = 0, mW = 0;

	for (int i=1; i<=K; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		grids[i] = {{a, b}, {c, d}};
		fs[a][b] = i;
		//W = max(W, d+1);
		mW = max(mW, d+1);
		mH = max(mH, c+1);
	}

	vector<pii> ans;
	int rm = K;

	int nx, ny; nx = ny = 0;
	auto ex = []() { cout << "Impossible" << endl; exit(0); };
	if (mH != H or mW != W)
		ex();
	auto nex = [&](int x, int y) -> pii {
		while (x < H) {
			if (not mp[x][y]) return {x, y};
			y ++;
			if (y >= W) {
				y = 0;
				x ++;
			}
		}
		return {x, y};
	};
	int ls = -1;
	bool fzz = false;
	while (rm) {
		if (not fs[nx][ny]) {
			ex();
		}
		rm --;

		int id = fs[nx][ny];
		ls = id;
		auto r = grids[id];
		int h = r.S.F - r.F.F + 1;
		int w = r.S.S - r.F.S + 1;
		for (int i=r.F.F; i<=r.S.F; i++) {
			for (int j=r.F.S; j<=r.S.S; j++) {
				mp[i][j] = id;
			}
		}
		if (r.S.S == W-1) {
			ans.PB({h, -1});
			ny += w;
			if (ny >= W) {
				nx ++;
				ny = 0;
			}
			if (r.F.S == W-1)
				fzz = true;
			tie(nx, ny) = nex(nx, ny);
		} else {
			ans.PB({h, w});
			while (ny < W and mp[nx][ny]) {
				ny ++;
			}
			if (ny >= W and rm) {
				ex();
			}
		}
		//cout << nx << ' '<< ny << endl;
	}

	if (rm) {
		ex();
	}


	if (ans.back().S == -1) {
		ans.back().S = grids[ls].S.S - grids[ls].F.S + 1;
	} else if (not fzz) {
		ex();
	}

	cout << "Panel container = new Panel(new GridBagLayout());\n"
		"GridBagConstraints gbc = new GridBagConstraints();\n";
	for (auto p: ans) {
		cout << "gbc.gridheight = " << p.F << ";\n";
		if (p.S == -1) 
			cout << "gbc.gridwidth = GridBagConstraints.REMAINDER;\n";
		else
			cout << "gbc.gridwidth = " << p.S << ";\n";
		cout << "container.add(new Component(), gbc);\n";
	}


    return 0;
}
