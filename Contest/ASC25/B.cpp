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
using ld = double;
struct pdd : pair<double, double> {
	using pair<double, double>::pair;
	pdd operator + (const pdd &he) const { return {F+he.F, S+he.S}; }
	pdd operator - (const pdd &he) const { return {F-he.F, S-he.S}; }
	double operator * (const pdd &he) const { return F*he.F+S*he.S; }
	pdd operator * (double f) const { return {F*f, S*f}; }
};
pdd operator * (double f, const pdd &p) { return {p.F*f, p.S*f}; }

inline double abs(pdd p) {
	return hypot(p.F, p.S);
}

const double EPS = 1e-12;
vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
	//if (abs(r1-r2) < EPS and abs(o1-o2) < EPS) return {};
	ld d2 = (o1 - o2) * (o1 - o2);
	ld d = sqrtl(d2);
	if (d < abs(r1-r2)) return {}; 
	if (d > r1+r2) return {};
	pdd u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
	double A = sqrtl((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
	pdd v = A / (2*d2) * pdd(o1.S-o2.S, -o1.F+o2.F);
	return {u+v, u-v};
}


const double PI = acosl(-1);

int N;
vector<pdd> ip;
using Circle = pair<pdd, double>;

inline double arg(pdd p) {
	return atan2l(p.S, p.F);
}

double zz(double x, double y) {
	if (x > y) x -= 2*PI;
	double t = y - x;
	while (t > PI) t = 2*PI - t;
	return t;
}

double check2(pdd p) {
	for (auto q: ip) {
		auto d = p - q;
		if (abs(d) < 1 - EPS) return 0;
	}

	vector<double> ar(N);
	for (int i=0; i<N; i++)
		ar[i] = arg(ip[i] - p);
	sort(ALL(ar));
	//cout << ar << endl;
	double ans = 1e9;
	for (int i=0; i<N; i++) {
		int j = (i+1)%N;
	//	cout << ar[i] << ' ' << ar[j] << ' ' << zz(ar[i], ar[j]) << endl;
		ans = min(ans, zz(ar[i], ar[j]));
	}
	return ans;
}

bool check(pdd p, double m) {
	/*
	if (abs(p) < 0.5) {
		cout << "p = " << p << endl;
	}*/
	for (auto q: ip) {
		auto d = p - q;
		if (abs(d) < 1 - EPS) return false;
	}

	vector<double> ar(N);
	for (int i=0; i<N; i++)
		ar[i] = arg(ip[i] - p);
	sort(ALL(ar));
	//cout << ar << endl;
	for (int i=0; i<N; i++) {
		int j = (i+1)%N;
		//cout << zz(ar[i], ar[j]) << endl;
		if (zz(ar[i], ar[j]) < m - EPS) return false;
	}
	return true;
}

pdd ans;

bool test(double m) {

	vector<Circle> cirs;
	
	double mm = PI - m;
	//cout << "mm = " << mm << endl;
	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			auto p = ip[i], q = ip[j];

			pdd d = p - q;
			double l = abs(d);
			d = {-d.S, d.F};
			d = d * (1.0 / abs(d));
			pdd mp = (p+q)*0.5;
			double ll = l/2.0/tanl(mm);
			d = d*ll;
			double r = l/2.0/sinl(mm);

			cirs.PB({mp+d, r});
			cirs.PB({mp-d, r});
		}
		cirs.PB({ip[i], 1});
	}
	//cout << cirs << endl;
	//return 0;
	int C = SZ(cirs);
	for (int i=0; i<C; i++) {
		for (int j=i+1; j<C; j++) {
			auto c1 = cirs[i], c2 = cirs[j];
			auto intp = interCircle(c1.F, c1.S, c2.F, c2.S);
//			cout << c1 << ' ' << c2 << endl;
			//cout << intp << endl;
			for (auto p: intp) {
				if (std::isnan(p.F)) continue;
				if (check(p, m)) {
					ans = p;
//					cout << m << ' ' << ans << endl;
					return true;
				}
			}
		}
	}
	return false;

}

//vector<pii> _ip;


int main() {
	FILEIO("astronomy");
	IOS;
	cin >> N;
//	_ip.resize(N);
//	for (int i=0; i<N; i++) cin>>_ip[i].F>>_ip[i].S;
	cout << fixed << setprecision(10);
	ip.resize(N);
	for (int i=0; i<N; i++) cin>>ip[i].F>>ip[i].S;


	double l = 0, r = PI;
	for (int _=0; _<50; _++) {
		double md = (l+r)/2;
		if (test(md)) {
			l = md;
		} else {
			r = md;
		}
	}
	double md = (l+r)/2;
	test(md);
	cout << ans.F << ' ' << ans.S << endl;
//	cout << check2(ans) << endl;
	return 0;
}
