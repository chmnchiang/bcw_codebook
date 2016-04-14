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

const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int dmp[2][4] = {{3, 2, 1, 0}, {1, 0, 3, 2}};
int R, C, M, N;

struct Li {
	vector<int> vl;
	void push_back(int a) { vl.PB(a); }
	void make() {
		sort(ALL(vl));
		vl.resize(unique(ALL(vl)) - vl.begin());
	}
	int operator () (int a) { return lower_bound(ALL(vl), a) - vl.begin(); }
	int size() { return SZ(vl); }
}lx, ly;
using pii=pair<int,int>;

const int MX = 422222;
vector<pii> ip[2];
int nX, nY;
vector<pii> X[MX], Y[MX];

const int BAD = -1;
const int INF = 1029384756;

int next(const vector<pii> &vec, int t) {
	auto res = upper_bound(ALL(vec), pii{t, INF});
	if (res == vec.end()) return BAD;
	return res - vec.begin();
}
int prev(const vector<pii> &vec, int t) {
	auto res = upper_bound(ALL(vec), pii{t, -INF});
	if (res == vec.begin()) return BAD;
	return res - vec.begin() - 1;
}

void walk(pii &p, int &d) {
	int x, y; tie(x, y) = p;
	
	const vector<pii> &vec = (d%2 ? X[p.F] : Y[p.S]);
	int val = (d%2 ? y : x);
	int id = (d<2 ? next(vec, val) : prev(vec, val));
	if (id == BAD) {
		if (d == 0) p.F = nX-1;
		else if (d == 1) p.S = nY-1;
		else if (d == 2) p.F = 0;
		else p.S = 0;
		d = 4;
		return;
	}
	auto np = vec[id];
	if (d%2==0) {
		p.F = np.F;
		d = dmp[np.S][d];
	} else {
		p.S = np.F;
		d = dmp[np.S][d];
	}
}

vector<pii> SX[MX], SY[MX];
vector<pii> TX[MX], TY[MX];

inline int lb(int a) { return a&(-a); }

struct BIT {
	int v[MX];

	void init() {
		FZ(v);
	}

	void add(int a, int val) {
		a += 2;
		for (int t=a; t<MX; t+=lb(t)) v[t] += val;
	}
	int qry(int a) {
		a += 2;
		int res = 0;
		for (int t=a; t; t-=lb(t)) res += v[t];
		return res;
	}
} bit;

void deinit() {
	bit.init();
	for (int i=0; i<nX; i++) SX[i].clear();
	for (int i=0; i<nX; i++) TX[i].clear();
	for (int i=0; i<nY; i++) SY[i].clear();
	for (int i=0; i<nY; i++) TY[i].clear();
	lx = Li();
	ly = Li();
	for (int i=0; i<M+N+3; i++) X[i].clear();
	for (int i=0; i<M+N+3; i++) Y[i].clear();
	ip[0].clear();
	ip[1].clear();

}


void calc() {
	for (auto p: ip[0]) {
		int x, y; tie(x, y) = p;
		X[x].PB({y, 0});
		Y[y].PB({x, 0});
	}
	for (auto p: ip[1]) {
		int x, y; tie(x, y) = p;
		X[x].PB({y, 1});
		Y[y].PB({x, 1});
	}
	for (int i=0; i<nX; i++) {
		sort(ALL(X[i]));
	}
	for (int i=0; i<nY; i++) {
		sort(ALL(Y[i]));
	}

	pii now = {2, 0};
	int d = 1;
	//cout << now << endl;
	while (d != 4) {
		int a, b; tie(a, b) = now;
		walk(now, d);
		//cout << now << endl;
#define d dddd
		int c, d; tie(c, d) = now;
		if (a == c) {
			if (b > d) swap(b, d);
			if (d - b < 2) continue;
			SY[b+1].PB({a, 1});
			SY[d-1].PB({a, -1});
		} else {
			if (a > c) swap(a, c);
			if (c - a < 2) continue;
			SX[a+1].PB({b, 1});
			SX[c-1].PB({b, -1});
		}
#undef d
	}

	//for (int i=0; i<nY; i++) cout << SY[i] << endl;

	if (now.F == nX-3 and now.S == nY-1) {
		cout << 0 << endl;
		return;
	}

	now = {nX-3, nY-1};
	d = 3;
	while (d != 4) {
		int a, b; tie(a, b) = now;
		walk(now, d);
		//cout << now << endl;
#define d dddd
		int c, d; tie(c, d) = now;
		if (a == c) {
			if (b > d) swap(b, d);
			if (d-b < 2) continue;
			TX[a].PB({b+1, d-1});
		} else {
			if (a > c) swap(a, c);
			if (c-a < 2) continue;
			TY[b].PB({a+1, c-1});
		}
#undef d
	}


	long long ans = 0;
	pii ba = {INF, INF};
	
	set<int> st;
	for (int i=0; i<nX; i++) {
		for (auto p: SX[i]) {
			int t = p.S;
			if (t == 1) {
				st.insert(p.F);
				bit.add(p.F, 1);
			} else {
			}
		}

		for (auto p: TX[i]) {
			auto it = st.lower_bound(p.F);
			if (it == st.end()) continue;
			if (*it > p.S) continue;

			ba = min(ba, {i, *it});
			ans += bit.qry(p.S) - bit.qry(p.F - 1);
		}

		for (auto p: SX[i]) {
			int t = p.S;
			if (t == 1) {
			} else {
				st.erase(p.F);
				bit.add(p.F, -1);
			}
		}
	}

	for (int i=0; i<nY; i++) {
		for (auto p: SY[i]) {
			int t = p.S;
			if (t == 1) {
				st.insert(p.F);
				bit.add(p.F, 1);
			} else {
			}
		}

		for (auto p: TY[i]) {
			//cout << p << endl;
			auto it = st.lower_bound(p.F);
			if (it == st.end()) continue;
			if (*it > p.S) continue;

			ba = min(ba, {*it, i});
			ans += bit.qry(p.S) - bit.qry(p.F - 1);
		}

		for (auto p: SY[i]) {
			int t = p.S;
			if (t == 1) {
			} else {
				st.erase(p.F);
				bit.add(p.F, -1);
			}
		}
	}
	if (!ans) cout << "impossible" << endl;
	else cout << ans << ' ' << lx.vl[ba.F] << ' ' << ly.vl[ba.S] << endl; 
}

int main() {
	IOS;

	int cas = 0;
	while (cin>>R>>C>>M>>N) {
		for (int i=0; i<M; i++) {
			int x, y; cin>>x>>y;
			ip[0].PB({x, y});
			lx.PB(x);
			ly.PB(y);
		}
		for (int i=0; i<N; i++) {
			int x, y; cin>>x>>y;
			ip[1].PB({x, y});
			lx.PB(x);
			ly.PB(y);
		}
		lx.PB(-1);
		lx.PB(0);
		lx.PB(1);
		lx.PB(R);
		lx.PB(R+1);
		lx.PB(R+2);

		ly.PB(-1);
		ly.PB(0);
		ly.PB(1);
		ly.PB(C);
		ly.PB(C+1);
		ly.PB(C+2);

		lx.make(); ly.make();

		for (auto &p: ip[0]) {
			p = {lx(p.F), ly(p.S)};
		}
		for (auto &p: ip[1]) {
			p = {lx(p.F), ly(p.S)};
		}
		nX = SZ(lx); nY = SZ(ly);

		cas++;
		cout << "Case " << cas << ": ";
		calc();
		deinit();
	}

	return 0;
}

