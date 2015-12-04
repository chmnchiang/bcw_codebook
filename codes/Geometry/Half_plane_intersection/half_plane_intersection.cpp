#include<bits/stdc++.h>

using namespace std;

#define PB push_back
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define F first
#define S second
#define x first
#define y second
#define IOS ios::sync_with_stdio(0);cin.tie(0)

const double EPS = 1E-9;

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

typedef pair<point, point> Line;

point interPnt(Line l1, Line l2, bool &res){
    point p1, p2, q1, q2;
    tie(p1, p2) = l1;
    tie(q1, q2) = l2;
	double f1 = (p2 - p1).cross(q1 - p1);
	double f2 = (p2 - p1).cross(p1 - q2);
	double f = (f1 + f2);

    if(fabs(f) < EPS) {
        res = false;
        return {0, 0};
    }

    res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}

bool isin(Line l0, Line l1, Line l2) {
    // Check inter(l1, l2) in l0
    bool res;
    point p = interPnt(l1, l2, res);
    return (l0.S - l0.F).cross(p - l0.F) > 1e-9;
}

/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F).cross(p - l.F) > 0
 */
vector<Line> halfPlaneInter(vector<Line> lines) {
    int sz = lines.size();
    vector<double> ata(sz), ord(sz);
    for (int i=0; i<sz; i++) {
        ord[i] = i;
        point d = lines[i].S - lines[i].F;
        ata[i] = atan2(d.y, d.x);
    }
    sort(ALL(ord), [&](int i, int j) {
        return ata[i] < ata[j];
    });
    vector<Line> fin;
    for (int i=0; i<sz; i++) {
        if (i and fabs(ata[ord[i]] - ata[ord[i-1]]) < EPS) {
            Line li = lines[ord[i]];
            Line lj = lines[ord[i-1]];
            if ((li.S - li.F).cross(lj.S - li.F) >= 0)
                continue;
            else 
                fin.back() = li;
        } else {
            fin.PB(lines[ord[i]]);
        }
    }
    
    deque<Line> dq;
    for (int i=0; i<SZ(fin); i++) {
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
