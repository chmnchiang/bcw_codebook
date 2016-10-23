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

#define double long double

#define x first
#define y second

#define cpdd const pdd
struct pdd : pair<double, double> {
	using pair<double, double>::pair;

	pdd operator + (cpdd &p) const {
		return {x+p.x, y+p.y};
	}

	pdd operator - () const {
		return {-x, -y};
	}

	pdd operator - (cpdd &p) const {
		return (*this) + (-p);
	}

	pdd operator * (double f) const {
		return {f*x, f*y};
	}

	double operator * (cpdd &p) const {
		return x*p.x + y*p.y;
	}
};

double abs(cpdd &p) { return hypotl(p.x, p.y); }
double arg(cpdd &p) { return atan2l(p.y, p.x); }
double cross(cpdd &p, cpdd &q) { return p.x*q.y - p.y*q.x; }
double cross(cpdd &p, cpdd &q, cpdd &o) { return cross(p-o, q-o); }
pdd operator * (double f, cpdd &p) { return p*f; } // !! Not f*p !!
const double EPS = 1e-9;
const double PI = acos(-1);


int N;
double hongshihao123;
vector<pdd> poly[20];;
double MN[20], MX[20];

double nmnm(double p) {
	while (p < -PI) p+=2*PI; 
	while (p >= PI) p-=2*PI; 
	return p;
}

pdd toXY(pdd p) {
	return {p.F * cos(p.S), p.F * sin(p.S)};
}

pdd toRT(pdd p) {
	return {abs(p), arg(p)};
}

pdd getOth(pdd p, pdd q) {
	pdd u = p - 1.0 * ((q - p) * (1/abs(q - p))) * ((p * (q - p)) / abs(q - p));
	return u;
}

int sign(double x) {
	if (abs(x) < EPS) return 0;
	return x < 0 ? -1 : 1;
}

double getIt(pdd x, pdd y, double rs) {
	pdd p1 = toXY(x), p2 = toXY(y);;
	pdd d = p2 - p1;
	d = d * (1. / abs(d));
	pdd q = getOth(p1, p2);
	double h = abs(q);
	double z = sqrtl(rs*rs-h*h);
	if(d*(p1-q) + d*(p2-q) < 0) z = -z;
	return arg(q + d * z);

	/*
	double l = x.S, r = y.S;
	if (r < l) r += 2*PI;

	r -= l;
	l = 0;
	double rx = x.F, ry = y.F;
	bool fg = rx < r;

	for (int i=0; i<100; i++) {

		double md = (l+r)/2;

		if (
	}*/
}

pair<vector<pdd>, vector<pdd>> inter(const vector<pdd> &po, double r) {
	int sz = SZ(po);
	vector<pdd> hao, nan;
	for (int i=0; i<sz; i++) {
		pdd x = po[i], y = po[(i+1)%sz];
		if (x.F < r && y.F < r) {
			nan.PB({x.S, y.S});
		} else if (x.F > r && y.F > r) {
			hao.PB({x.S, y.S});
		} else {
			double theta = getIt(x, y, r);
			if (x.F > r) {
				hao.PB({x.S, theta});
				nan.PB({theta, y.S});
			} else {
				nan.PB({x.S, theta});
				hao.PB({theta, y.S});
			}
		}
	}
	for (auto &x: hao) {
		x.F = nmnm(x.F);
		x.S = nmnm(x.S);
		if (x.F > x.S) x.S += 2*PI;
	}
	for (auto &x: nan) {
		double f = x.F, s = x.S;
		x.F = nmnm(-s);
		x.S = nmnm(-f);
		if (x.F > x.S) x.S += 2*PI;
	}
	return {hao, nan};
}

vector<pdd> nmnmAll(vector<pdd> vec) {
	for (auto &x: vec) {
		x.F = nmnm(x.F);
		x.S = nmnm(x.S);
		if (x.F > x.S) x.S += 2*PI;
	}
	return vec;
}

vector<pdd> coco(vector<pdd> vec) {
	if (!SZ(vec)) return {};
	//vec = nmnmAll(vec);
	vector<pdd> ret;
	/*
	for (auto &p: vec) {
		p.F -= EPS;
		p.S += EPS;
	}*/
	sort(ALL(vec));

	double nl = vec[0].F, nr = vec[0].S;
	int sz = SZ(vec);
	for (int i=1; i<sz; i++) {
		if (vec[i].F > nr) {
			ret.PB({nl, nr});
			nl = vec[i].F;
			nr = vec[i].S;
		} else {
			nr = max(nr, vec[i].S);
		}
	}
	ret.PB({nl, nr});
	return ret;
}

vector<pdd> V;

bool calc(int id) {
	if (MN[0] > MX[id]) return false;

	V.clear();
	auto &po = poly[id];
	auto &rose = poly[0];

	int goodN = 0;

	const pdd YY = {2*PI, 2*PI};
	for (auto p: po) {
		auto _ret = inter(rose, p.F).F;
		vector<pdd> ret;
		for (auto x: _ret) {
			pdd xx = x - pdd(p.S, p.S);
			ret.PB(xx);
			ret.PB(xx + YY);
			ret.PB(xx + 2*YY);
			ret.PB(xx + 3*YY);
		}
		ret = coco(ret);
		//cout << "hao = " << ret << endl;
		V.insert(end(V), ALL(ret));
		goodN += 1;
	}

	for (auto p: rose) {
		auto _ret = inter(po, p.F).S;
		vector<pdd> ret;
		for (auto x: _ret) {
			pdd xx = x + pdd(p.S, p.S);
			ret.PB(xx);
			ret.PB(xx+YY);
			ret.PB(xx+2*YY);
			ret.PB(xx+3*YY);
		}
		ret = coco(ret);
		//cout << "nan = " << ret << endl;
		V.insert(end(V), ALL(ret));
		goodN += 1;
	}

	using pdi = pair<double, int>;
	vector<pdi> vv;
	for (auto x: V) {
		vv.PB({x.F, 1});
		vv.PB({x.S, -1});
	}

	sort(ALL(vv));

	int n = 0;
	for (auto p: vv) {
		if (p.S == 1) {
			n += 1;
			if (n == goodN) return true;
		} else {
			n -= 1;
		}
	}
	return false;
}

int main() {
	FILEIO("gtaw");
	IOS;
	cin >> N;
	cin >> hongshihao123;


	for (int i=0; i<N+1; i++) {
		int x; cin >> x;
		for (int j=0; j<x; j++) {
			pdd p;
			cin >> p.F >> p.S;
			p.S *= PI / 180.0;
			p.S = nmnm(p.S);
			if (!i) p.F += EPS;
			poly[i].PB(p);
		}
		MX[i] = 0;
		MN[i] = 1e20;
	}

	for (int i=0; i<N+1; i++) {
		int sz = SZ(poly[i]);
		auto &po = poly[i];
		for (int j=0; j<sz; j++) {
			int k = (j+1)%sz;
			pdd p = toXY(po[j]), q = toXY(po[k]);
			pdd d = p-q;
			int f1 = sign(d*p);
			int f2 = sign(d*q);
			if (f1 == 0 || f2 == 0 || (f1 == f2)) continue; 
			pdd u = p - 1.0 * ((q - p) * (1/abs(q - p))) * ((p * (q - p)) / abs(q - p));
			po.PB(toRT(u));
		}
	}

	for (int i=0; i<N+1; i++) {
		sort(ALL(poly[i]), [](pdd p1, pdd p2) { return p1.S < p2.S; });
		for (auto p: poly[i]) {
			MX[i] = max(MX[i], p.F);
			MN[i] = min(MN[i], p.F);
		}
	}

	vector<int> ans;
	for (int i=1; i<=N; i++) {
		if (calc(i)) {
			ans.PB(i);
		}
	}

	cout << SZ(ans) << endl;
	for (auto x: ans) cout << x << " ";
	cout << endl;
	return 0;
}
