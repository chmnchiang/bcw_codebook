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

typedef pair<int, int> pii;
const pii dir[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const pii fil[4] = {{-1, 1}, {1, 1}, {1, -1}, {1, 1}};
pii operator + (const pii p1, const pii p2) {
	return {p1.F + p2.F, p1.S + p2.S};
}

pii operator * (const pii p1, const pii p2) {
	return {p1.F * p2.F, p1.S * p2.S};
}

/*
template<typename T, typename U>
tuple<T&, U&> operator , (T &t, U &u) {
	return tie(t, u);
}*/

typedef vector<pii> vpii;

set<vpii> visit;
int N, M, W;
bool wall[5][5][5][5];
vector<pii> holes;
int hmp[5][5];

bool inr(pii p) {
	int x, y;
	tie(x, y) = p;
	return x >= 0 and x < N and y >= 0 and y < N;
}

bool canWalk(pii p1, pii p2) {
	return not wall[p1.F][p1.S][p2.F][p2.S];
}

pair<vector<pii>, bool> walk(vector<pii> vec, int di) {
	bool fall[30] = {};
	vector<int> left;
	for (int i=0; i<M; i++) {
		if (vec[i] == holes[i]) fall[i] = true;
		else left.PB(i);
	}

	auto cmp = [&](int i1, int i2) {
		pii p1 = vec[i1];
		pii p2 = vec[i2];
		p1 = p1 * fil[di];
		p2 = p2 * fil[di];
		return p1 < p2;
	};

	pair<vector<pii>, bool> ERR = {vector<pii>(), true};
	
	sort(ALL(left), cmp);
	//cout << left << endl;

	pii d = dir[di];
	for (auto i: left) {
		pii p = vec[i];

		//cout << i << ' ' << p << endl;
		while (true) {
			pii nxt = p + d;
			//cout << nxt << endl;
			if (not inr(nxt)) break;
			if (not canWalk(p, nxt)) break;
			int x, y; tie(x, y) = nxt;
			int h = hmp[x][y];
			//cout << "H = " << h << endl;
			if (h != -1 and !fall[h]) {
				if (h != i) return ERR;
				else {
					p = nxt;
					fall[i] = true;
					break;
				}
			}

			bool hit = false;
			for (auto j: left) {
				if (i == j) break;
				if (nxt == vec[j] and !fall[j]) {
					hit = true;
					break;
				}
			}
			if (hit) break;

			p = nxt;
		}

		vec[i] = p;
	}
	return {vec, false};
}

int solve() {
	visit.clear();
	FZ(wall);
	FMO(hmp);

	vector<pii> start(M);

	for (int i=0; i<M; i++) {
		int x, y;
		cin >> x >> y;
		start[i] = {x, y};
	}

	holes.resize(M);
	for (int i=0; i<M; i++) {
		int x, y; cin >> x >> y;
		holes[i] = {x, y};
		hmp[x][y] = i;
	}

	for (int i=0; i<W; i++) {
		int a, b, c, d; cin >> a >> b >> c >> d;
		wall[a][b][c][d] = 1;
		wall[c][d][a][b] = 1;
	}
	queue<pair<vector<pii>, int>> qe;
	qe.push({start, 0});

	while (qe.size()) {
		vector<pii> v;
		int dis;
		tie(v, dis) = qe.front();
		qe.pop();

		for (int i=0; i<4; i++) {
			auto x = walk(v, i);
			if (x.S) continue;
			if (x.F == holes) return dis+1;
			if (visit.count(x.F)) continue;

			qe.push({x.F, dis+1});
			visit.insert(x.F);
		}
	}

	return -1;
}

int main() {
    IOS;

	
	/*
	FMO(hmp);
	hmp[0][0] = 0;
	hmp[0][3] = 1;
	hmp[3][0] = 2;
	hmp[3][3] = 3;
	//wall[1][1][1][2] = wall[1][2][1][1] = true;
	tie(N, M, W) = make_tuple(4, 4, 1);
	holes = {{0, 0}, {0, 3}, {3, 0}, {3, 3}};
	vector<pii> vec = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
	cout << vec << endl;
	cout << walk(vec, 0) << endl;
	cout << walk(vec, 1) << endl;
	cout << walk(vec, 2) << endl;
	cout << walk(vec, 3) << endl;
	cout << vec << endl;
	return 0;
	*/

	int cas = 0;

	while (true) {
		cin >> N >> M >> W;
		if (not N and not M and not W) {
			return 0;
		}

		int t = solve();
		cas++;
		if (t == -1) 
			cout << "Case " << cas << ": " << "impossible" << endl;
		else
			cout << "Case " << cas << ": " << t << " moves" << endl;
		cout << endl;
	}

    return 0;
}

