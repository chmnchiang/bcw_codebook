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

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i)+= ((a) > (b) ? -1 : 1))

double D[4];
double R[4];

struct Point : pair<double, double> {
  typedef double T;
  
  Point() : pair<T, T>() {}
  Point(double _x, double _y) : pair<T, T>(_x, _y) {}

#define x first
#define y second
  Point operator + (const Point &b) const{
    return Point(x+b.x, y+b.y);
  }
  Point operator - (const Point &b) const{
    return Point(x-b.x, y-b.y);
  }
  T operator * (const Point &b) const{
    return x*b.x + y*b.y;
  }
  T operator % (const Point &b) const{
    return x*b.y - y*b.x;
  }
  Point operator * (T b) const{
    return Point(x*b, y*b);
  }
  T abs(){
    return sqrt(abs2());
  }
  T abs2(){
    return x*x + y*y;
  }
};


using pdd = Point;

pdd operator * (double v, const pdd &p) {
	return p*v;
}

pdd rad(pdd o, double r, double th) {
	return o + r * pdd(cos(th), sin(th));
}

const double EPS = 1e-10;
bool inter(pdd o1, double r1, pdd o2, double r2) {
	double d = (o1 - o2).abs();
	return d < r1 + r2 - EPS;
}

double minR;

bool bad;
double getTh(double r, double r1, double r2) {
	bad = false;
	double z1 = (r-r1), z2 = (r-r2), z3 = (r1+r2);
	if ( (z1*z1+z2*z2-z3*z3) / (2.0 * z1 * z2) < -1.0) {
		bad = 1;
		return 0.0;
	}
	
	return acos( (z1*z1+z2*z2-z3*z3) / (2.0 * z1 * z2));
}

bool calc4(double r) {
	double th[4] = {};
	loop (i, 1, 4) {
		int j=i-1;
		th[i] = getTh(r, R[j], R[i]);
		if (bad) return false;
		th[i] += th[j];
//		cerr << th[i] << endl;
	}

	pdd pts[4];
	loop (i, 0, 4) {
		pts[i] = rad({0, 0}, r-R[i], th[i]);
//		cerr << pts[i] << endl;
	}

	loop (i, 0, 4) {
		loop (j, i+1, 4) {
			if (inter(pts[i], R[i], pts[j], R[j])) return false;
		}
	}
	return true;
}

double calc4() {
	double l=minR+1e-5, r=R[0]+R[1]+R[2]+R[3];

	loop (_, 0, 50) {
		double md = (l+r)/2;
		
		/*
		md = 241440000;
//		cerr << "md = " << md << endl;
//		cerr << "ans = " << calc4(md) << endl;
		return md;
		*/
		
		if (calc4(md)) r=md;
		else l=md;
	}
	return l;
}

const double PI = acos(-1);

double calc2() {
	double th[4] = {};
	double r = (R[0] + R[3])+1e-10;
	if (r < R[1] or r < R[2]) return 1e9;
	th[1] = getTh(r, R[0], R[1]);
	th[2] = -getTh(r, R[0], R[2]);
	th[3] = PI;

	pdd pts[4];
	loop (i, 0, 4) {
		pts[i] = rad({0, 0}, r-R[i], th[i]);
	}

	loop (i, 0, 4) {
		loop (j, i+1, 4) {
			if (inter(pts[i], R[i], pts[j], R[j])) return 1e9;
		}
	}
	return r;
}

int calc() {
	double ans = 1e9;
	int per[4] = {0, 1, 2, 3};
	minR = max(D[0], max(D[1], max(D[3], D[2])));
	do {
		loop(i, 0, 4) R[i] = D[per[i]];
		ans = min(ans, min(calc2(), calc4()));
		//cout << calc2() << endl;
	} while (next_permutation(per, per+4));
	return round(ans+1e-12);
}

int main() {
	IOS;

	int cas=0;
	while (1) {

		int t;
		cin >> t;
		if (!t) break;
		D[0] = t;
		loop (i, 1, 4) cin >> D[i];

//		cout << calc4(10000) << endl;
//		return 0;

		cas++;
		cout << "Case " << cas << ": " << calc() << endl;
	}

	return 0;
}


