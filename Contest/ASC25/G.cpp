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


typedef array<int,3> Coord;
typedef bitset<128> BT;
ostream& operator << (ostream &s, Coord a) {
	return s << "(" << a[0] << "," << a[1] << "," << a[2] <<")";
}
struct KeyHasher {
	size_t operator()(const BT& k) const {
		size_t x = 0;
		REP(i,128) x = x * 2 + k[i];
		return x;
	}
};
bool operator < (const BT &a, const BT &b) {
	REP(i,128) if (a[i] != b[i]) return a[i] < b[i];
	return false;
}


int A,B,C,idx[6][6][6];
Coord pt[128];
vector<Coord> dir;
vector<int> E[128];
int frm[128],to[128];
unordered_set<BT,KeyHasher> state[128];
BT fstate;
clock_t start_t;

void build_dir() {
	vector<int> vv{0,1,2};
	do {
		REP(i,2) REP(j,2) REP(k,2) {
			auto f = [](int a, int b) {
				if (a == 0) return b;
				else return -b;
			};
			dir.PB({f(i,vv[0]), f(j,vv[1]), f(k,vv[2])});
		}
	} while (next_permutation(ALL(vv)));
	sort(ALL(dir));
	dir.resize(unique(ALL(dir))-begin(dir));

}
void build_graph() {
	int pos = 0;
	REP1(i,1,A) REP1(j,1,B) REP1(k,1,C){
		idx[i][j][k] = ++pos;
		pt[pos] = {i,j,k};
	}

	REP1(i,1,A) REP1(j,1,B) REP1(k,1,C) {
		int u = idx[i][j][k];
		for (auto d:dir) {
			int a = i + d[0];
			int b = j + d[1];
			int c = k + d[2];
			if (a < 1 or a > A or b < 1 or b > B or c < 1 or c > C) continue;
			int v = idx[a][b][c];
			E[u].PB(v);
		}
	}
}
void output() {
	cout << "YES" << endl;
	int x = 1;
	REP(_,A*B*C) {
		cout << pt[x][0] << " " << pt[x][1] << " " << pt[x][2] << endl;
		x = to[x];
	}
//	cout << 1.0*(clock() - start_t)/CLOCKS_PER_SEC << endl;
	exit(0);
}
void DFS(int u, BT &s) {
	if (1.0*(clock() - start_t)/CLOCKS_PER_SEC > 0.45) {
		cout << "NO" << endl;
		exit(0);
	}
//	cout << u << " " << s <<  endl;
	if (state[u].count(s)) return;
	state[u].insert(s);
	if (s == fstate) {
		output();
	}
	int deg = 0;
	for (auto v:E[u]) {
		if (!s[v]) {
			deg++;
			s[v] = 1;
			frm[v] = u;
			to[u] = v;
			DFS(v,s);
			frm[v] = to[u] = 0;
			s[v] = 0;
		}
	}
	if (!deg and SZ(E[u]) > 0 and !(SZ(E[u]) == 1 and E[u][0] == 1)) {
		int v = 0;
		int sz = SZ(E[u]);
		int c = 0;
		while (c < A*B*C) {
			v = rand() % sz;
			if (E[u][v] != 1) break;
			c++;
		}
		if (E[u][v] == 1) return;
		v = E[u][v];

		vector<int> vec;
		vector<pair<int*,int>> backup;
		vec.PB(v);
		int x = u;
		while (x != v) {
			vec.PB(x);
			x = frm[x];
		}

		for (auto i:vec) {
			backup.PB({&frm[i],frm[i]});
			backup.PB({&to[i],to[i]});
		}

		for (int i=0; i<SZ(vec)-1; i++) {
			int a = vec[i];
			int b = vec[i+1];
			frm[b] = a;
			to[a] = b;
		}

		DFS(vec.back(),s);

		for (auto it:backup) *it.F = it.S;
	}
}
int main() {
	start_t = clock();
	FILEIO("knight");
	IOS;
	build_dir();

	cin >> A >> B >> C;

	build_graph();
//	REP1(i,1,A*B*C) cout << i << " " << E[i] << endl;
	REP1(i,1,A*B*C) fstate[i] = 1;

	BT s;
	s[1] = 1;

	DFS(1,s);
	cout << "NO" << endl;

	return 0;
}
