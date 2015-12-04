#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define F first
#define S second
#define SZ(x) ((int)(x).size())
#define ALL(x) x.begin(), x.end()
#define PB push_back
 
struct point : public pair<double, double> {

    point() {}
    point(double _x, double _y) : pair<double, double>(_x, _y) {
    }

    point operator + (const point he) const {
        return {x+he.x, y+he.y};
    }
    point operator - (const point he) const {
        return {x-he.x, y-he.y};
    }
    friend point operator * (const double c, const point &p) {
        return {c*p.x, c*p.y};
    }
    point operator * (const double c) const {
        return {c*x, c*y};
    }
    double operator * (const point he) const {
        return x*he.x + y*he.y;
    }
    double cross (const point &he) const {
        return x*he.y - y*he.x;
    }
    friend ostream& operator << (ostream& o, const point &p) {
        cout << "(" << p.x << ", " << p.y << ")";
        return o;
    }
};

#define Point point
typedef pair<point, point> Line;
 
const double eps = 1e-9;
 
int n;
vector<Point> p;
 
point interPnt(Line l1, Line l2){
    point p1, p2, q1, q2;
    tie(p1, p2) = l1;
    tie(q1, q2) = l2;
	double f1 = (p2 - p1).cross(q1 - p1);
	double f2 = (p2 - p1).cross(p1 - q2);
	double f = (f1 + f2);

	return (f2 / f) * q1 + (f1 / f) * q2;
}
 
vector<Line> build(const int &m) {
	vector<Line> ret;
	for (int i = 0; i < n; ++i) {
		ret.push_back({p[(i)%n], p[(i+m) % n]});
	}
	return ret;
}

bool isin(Line l0, Line l1, Line l2) {
    // Check inter(l1, l2) in l0
    bool res;
    point p = interPnt(l1, l2);
    return (l0.S - l0.F).cross(p - l0.F) > 1e-9;
}
 
 
vector<Line> halfPlaneInter(vector<Line> lines) {
    int sz = lines.size();
    vector<Line> fin = lines;
    deque<Line> dq;
    for (int i=0; i<sz; i++) {
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
            dq.pop_back();
        }
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[0], dq[1])) {
            dq.pop_front();
        }
        dq.push_back(fin[i]);
    }

    while (SZ(dq) >= 3 and
           not isin(dq[0], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
        dq.pop_back();
    }

    while (SZ(dq) >= 3 and
           not isin(dq[SZ(dq)-1], dq[0], dq[1])) {
        dq.pop_front();
    }
    vector<Line> res(SZ(dq));
    copy(ALL(dq), res.begin());
    return res;
}
 
int N;
vector<point> ip;
bool test(int a) {
    vector<Line> ln;
    for (int i=0; i<N; i++) {
        int j = (i+a+1)%N;
        ln.PB({ip[i], ip[j]});
    }
    auto res = halfPlaneInter(ln);
    return halfPlaneInter(ln).size() < 3;
}

int main(){
#ifdef ONLINE_JUDGE
    freopen("jungle.in", "r", stdin);
    freopen("jungle.out", "w", stdout);
#endif
    cin >> N;

    for (int i=0; i<N; i++) {
        double x, y; cin >> x >> y;
        ip.PB({x, y});
    }
    reverse(ALL(ip));

    int l = 0, r = (N+1)/2;
    while (l < r) {
        int md = (l+r)>>1;
        if (test(md)) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    cout << l << endl;
}

