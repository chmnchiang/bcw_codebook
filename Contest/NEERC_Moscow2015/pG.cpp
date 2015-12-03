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

typedef pair<int,int> pii;
const int MXN = 200005;
const double sq2 = sqrt(2);

struct Lisan {
	vector<int> seq;
	void init() { seq.clear(); }
	void add(int x) { seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq)) - begin(seq));
	}
	int query(int x) { // 1-base
		return lower_bound(ALL(seq), x) - begin(seq) + 1;
	}
}lisan;

struct BIT {
	int n;
	pair<double, int> bit[MXN];
	void init(int _n) {
		n = _n;
		for (int i=0; i<=n; i++)
			bit[i] = {1e-9, -1};
	}
	int lb(int x) { return x & -x; }
	void update(int st, double v, int id) {
		pair<double, int> x(v, id);
		for (int i=st; i>0; i-=lb(i))
			bit[i] = max(bit[i], x);
	}
	pair<double, int> query(int st) {
		pair<double, int> res = {-1e9, -1};
		for (int i=st; i<=n; i+=lb(i))
			res = max(res, bit[i]);
		return res;
	}
}bit;

struct Point {
	int x, y, id;
}ip[MXN];

bool operator < (const Point &a, const Point &b) {
	return tie(a.x, a.y) < tie(b.x, b.y);
}

int N;
double cost;
pii ans;

void rotate() {
	for (int i=0; i<N; i++) {
		int x = ip[i].x;
		int y = ip[i].y;
		ip[i].x = -y;
		ip[i].y = x;
	}
}
void reflect() {
	for (int i=0; i<N; i++) {
		int x = ip[i].x;
		int y = ip[i].y;
		ip[i].x = y;
		ip[i].y = x;
	}
}

void solve() {
	sort(ip, ip+N);
	reverse(ip, ip+N);
	lisan.init();
	for (int i=0; i<N; i++) {
		lisan.add(ip[i].y - ip[i].x);
	}
	lisan.build();
	bit.init(SZ(lisan.seq));
	for (int i=0; i<N; i++) {
		int x = ip[i].x;
		int y = ip[i].y;
		int id = lisan.query(y-x);
//		cout << x << " " << y << endl;
		auto tmp = bit.query(id);
		double res = tmp.F;
		int id2 = tmp.S;
		double val = (sq2-1)*x+y;
		if (id2 != -1) {
			res -= val;
//			cout << "RESULT " << res << " " << id2 << endl;
//			cout << "VAL = " << val << endl;
			if (cost < res) {
				cost = res;
				ans = {ip[i].id, id2};
			}
		}
//		cout << "UPDATE " << id << " " << val << endl;
		bit.update(id, val, ip[i].id);
	}
}

int main() {
	IOS;
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> ip[i].x >> ip[i].y;
		ip[i].id = i+1;
	}
	cost = 0;
	ans = {0, 0};
	solve();
	for (int i=0; i<3; i++) {
		rotate();
		solve();
	}
	reflect();
	solve();
	for (int i=0; i<3; i++) {
		rotate();
		solve();
	}
	cout << ans.F << " " << ans.S << endl;


	return 0;
}

