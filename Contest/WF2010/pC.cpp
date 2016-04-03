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

typedef long long ll;
const int MXN = 2005;
struct Lisan {
	vector<int> seq;
	int operator [] (int i) { return seq[i]; }
	void init() {
		seq.clear();
	}
	void add(int x) { seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq)) - begin(seq));
	}
	int qry(int x) { return lower_bound(ALL(seq),x) - begin(seq); }
	int size() { return seq.size(); }
}lx,ly;
struct Wall {
	int x1,y1,x2,y2;
}wall[1024];

int N,M,W;
bitset<3005> fail[3005];

int main() {
	IOS;
	int cas = 0;
	while (cin >> M >> N >> W) {
		if (not N) break;
		lx.init();
		ly.init();
		REP(i,W) {
			cin >> wall[i].x1 >> wall[i].y1 >> wall[i].x2 >> wall[i].y2;
			if (wall[i].x1-1 >= 0) lx.add(wall[i].x1-1);
			lx.add(wall[i].x1);
			if (wall[i].x2+1 < N) lx.add(wall[i].x2+1);
			ly.add(wall[i].y1);
			if (wall[i].y1-1 >= 0) ly.add(wall[i].y1-1);
			if (wall[i].y1+1 < M) ly.add(wall[i].y1+1);
		}
		lx.add(0);
		lx.add(N-1);
		ly.add(0);
		ly.add(M-1);

//		REP(i,N) lx.add(i);
//		REP(i,M) ly.add(i);

		lx.build();
		ly.build();
		REP(i,lx.size()) REP(j,ly.size())
			fail[i][j] = 0;
		REP(i,W) {
			int x1 = lx.qry(wall[i].x1);
			int x2 = lx.qry(wall[i].x2+1)-1;
			int y = ly.qry(wall[i].y1);
//			cout << x1 << " " << x2 << " " << y << endl;
			REP1(x,x1,x2) fail[x][y] = 1;
		}
		/*
		REP(i,lx.size()) {
			REP(j,ly.size()) cout << fail[i][j] << " ";
			cout << endl;
		}
		cout << "===\n";
		*/
		ll ans = 0;
		for (int i=lx.size()-1; i>=0; i--) {
			for (int j=ly.size()-1; j>=0; j--) {
				if (!(i == lx.size()-1 and j == ly.size()-1) and !fail[i][j]) {
					int cnt = 0;
					if (i == lx.size()-1 or fail[i+1][j]) cnt++;
					if (j == ly.size()-1 or fail[i][j+1]) cnt++;
					if (cnt == 2) fail[i][j] = 1;
				}
				if (fail[i][j]) {
					ll x2 = (i == lx.size()-1) ? N : lx[i+1];
					ll x1 = lx[i];
					ll y2 = (j == ly.size()-1) ? M : ly[j+1];
					ll y1 = ly[j];
//					cout << "FAIL " << i << " " << j << ", ";
//					cout << "ADD " << make_pair(x1,y1) << " " << make_pair(x2-1,y2-1) << endl;
					ans += (x2 - x1) * (y2 - y1);
				}
			}
		}
		REP(i,W) ans -= wall[i].x2 - wall[i].x1 + 1;
		/*
		REP(i,lx.size()) {
			REP(j,ly.size()) cout << fail[i][j] << " ";
			cout << endl;
		}
		*/

		cas++;
		cout << "Case " << cas << ": " << ans << "\n";
	}

	return 0;
}

