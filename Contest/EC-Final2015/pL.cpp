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

#define int long long
const int MX = 1111;
using Data=array<int, 3>;
int R, C;
int ip[MX][MX];
vector<Data> op;

vector<int> fac(int v) {
	vector<int> res;
	for (int i=1; i*i<=v; i++) {
		if (v%i) continue;
		int j = v/i;
		res.PB(i);
		if (i != j) res.PB(j);
	}
	return res;
}

bool check(int x, int y) {
	for (int i=0; i<R; i++)
		for (int j=0; j<C; j++) {
			int t = (x+i) * (y+j);
			if (ip[i][j] != -1 and t != ip[i][j]) return false;
		}
	return true;
}

bool calc() {
	int t = SZ(op);
	if (t == 0) return true;
	if (t == 1) {
		auto dt = op[0];
		int x = dt[0], y = dt[1];

		auto v = fac(dt[2]);
		for (auto f: v) {
			int ff = dt[2]/f;

			if (f >= x+1 and ff >= y+1) return true;
		}
		return false;
	}

	auto d1 = op[0], d2 = op[1];
	int a = d2[0] - d1[0];
	int b = d2[1] - d1[1];
	int c = d2[2]-d1[2]-a*b;
	auto v = fac(d1[2]);
	for (auto f: v) {
		int ff = d1[2]/f;

		if ((b*f+a*ff == c) and f >= d1[0]+1 and ff >= d1[1]+1) 
			if (check(f-d1[0], ff-d1[1])) return true;
	}
	return false;
}

int32_t main() {
	IOS;

	int T; cin>>T;
	for (int cas=1; cas<=T; cas++) {
		cin>>R>>C;
		op.clear();
		op.reserve(R*C);
		for (int i=0; i<R; i++)
			for (int j=0; j<C; j++) {
				string t; cin>>t;
				int v;
				if (t == "?") v = -1;
				else v = atoi(t.c_str());
				ip[i][j] = v;
				if (v != -1)
					op.PB({i, j, v});
			}

		cout << "Case #" << cas << ": " << (calc() ? "Yes" : "No") << endl;
	}

	return 0;
}

