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

template<typename T, size_t N>
ostream& operator <<(ostream &s, const array<T, N> &c) {
    s<<"( ";
    for (auto it : c) s << it << " ";
    s<<")";
    return s;
}
// Let's Fight!
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

using pii = pair<int, int>;
const pii dir[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int MX = 3333;
map<char, int> dirMap;

struct lisan {
	vector<int> v;

	void push_back(int x) {
		v.PB(x);
	}

	void make() {
		sort(ALL(v));
		v.resize(unique(ALL(v)) - v.begin());
	}

	int size() {
		return SZ(v);
	}

	int operator () (int a) {
		return lower_bound(ALL(v), a) - v.begin();
	}
}lx, ly;

using p3i = array<int, 3>;
vector<p3i> ip;
set<int> sx[MX], sy[MX];
int N;
int nt[4][MX], ot[4][MX];
int pdir[MX][MX];

const int BAD = -1;

namespace helper {
int nxt(set<int> &s, int v) {
	auto it = s.upper_bound(v);
	if (it == s.end()) return BAD;
	return *s.upper_bound(v);
}
int prv(set<int> &s, int v) {
	auto it = s.lower_bound(v);
	if (it == s.begin()) return BAD;
	return *(--it);
}
int getID(int x, int y) {
	//cout << x << ' ' << y << endl;
	if (x == BAD or y == BAD) return -1;
	int id = lower_bound(ALL(ip), p3i{x, y, 0}) - ip.begin();
	return id;
}
}

void build() {
	using namespace helper;
	for (int i=0; i<N; i++) {
		int x = ip[i][0], y = ip[i][1];
		sx[x].insert(y);
		sy[y].insert(x);
		pdir[x][y] = ip[i][2];
	}

	for (int i=0; i<N; i++) {
		int x = ip[i][0], y = ip[i][1];
		int px = prv(sy[y], x),
			py = prv(sx[x], y),
			nx = nxt(sy[y], x),
			ny = nxt(sx[x], y);
		
		ot[0][i] = getID(nx, y);
		ot[1][i] = getID(x, ny);
		ot[2][i] = getID(px, y);
		ot[3][i] = getID(x, py);
	}
}



void remove(int id) {
	int nx = nt[0][id],
		ny = nt[1][id],
		px = nt[2][id],
		py = nt[3][id];

	if (nx != -1) {
		nt[2][nx] = px;
	}
	if (ny != -1) {
		nt[3][ny] = py;
	}

	if (px != -1) {
		nt[0][px] = nx;
	}
	if (py != -1) {
		nt[1][py] = ny;
	}
}

int calc(int st) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<4; j++) {
			nt[j][i] = ot[j][i];
		}
	}


	int nid = st;
	int ret = 0;
	while (nid != -1) {
		ret ++;
		int ndir = ip[nid][2];
		int xid = nt[ndir][nid];
		remove(nid);
		nid = xid;
	}
	return ret;
}

int main() {
	IOS;
	dirMap['>'] = 0;
	dirMap['v'] = 1;
	dirMap['<'] = 2;
	dirMap['^'] = 3;

	cin>>N;
	ip.resize(N);
	loop(i, 0, N) {
		int x, y;
		string s;
		cin>>x>>y>>s;
		int d = dirMap[s[0]];
		ip[i] = p3i{x, y, d};
		lx.PB(x);
		ly.PB(y);
	}
	lx.make();
	ly.make();
	for (int i=0; i<N; i++) {
		ip[i][0] = lx(ip[i][0]);
		ip[i][1] = ly(ip[i][1]);
	}
	sort(ALL(ip));
	//cout << ip << endl;

	build();

	int ans = 0;
	for (int i=0; i<N; i++) {
		ans = max(ans, calc(i));
		//cout << calc(i) << endl;
	}
	cout << ans << endl;


	return 0;
}

