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

#define x first
#define y second
#define double long double

typedef pair<double, double> pdd;

const double EPS = 1E-12;

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

const int MAXN = 111;

int N;
point pt[MAXN];

double th[333], tth[333], h[333];

double calc()
{
	double area = 0;
	for(int i=0; i<N; i++)
		area += pt[i].cross(pt[(i+1)%N]);
	if(area < 0)
		reverse(pt, pt+N);

	vector<point> vpt;
	for(int i=0; i<N; i++)
		vpt.PB(pt[i]);

	vector<Line> vln;
	for(int i=0; i<N; i++)
	{
		int j = (i+1) % N;
		vln.PB({vpt[i], vpt[j]});
	}

	double ans = 0;
	double nowh = 0;
	while(vln.size() >= 3)
	{
		int S = vln.size();
		for(int i=0; i<S; i++)
		{
			int j = (i+1) % S;
			point p1 = vln[i].y - vln[i].x;
			point p2 = vln[j].y - vln[j].x;
			th[i] = acos((p1*p2) / (sqrt(p1*p1) * sqrt(p2*p2))) / 2;
			tth[i] = tan(th[i]);
		}

		bool q = false;
		for(int i=0; i<S; i++)
		{
			int j = (i+1) % S;
			int k = (i+S-1) % S;
			bool tz;
			point p1 = interPnt(vln[i], vln[j], tz);
			if(!tz) q = true;
			point p2 = interPnt(vln[i], vln[k], tz);
			if(!tz) q = true;
			point p = p1 - p2;
			double len = sqrt(p*p);
			h[i] = len / (tth[i] + tth[k]);
		}
		if(q) break;

		int idx = -1;
		for(int i=0; i<S; i++)
		{
			if(idx == -1 || h[i] < h[idx])
				idx = i;
		}

		double hmin = h[idx];
		double dh = hmin - nowh;
		for(int i=0; i<S; i++)
		{
			ans += dh / cos(th[i]);
		}

		int any = 0;
		for(int i=0; i<S; i++)
			if(h[i] > hmin + EPS)
				any++;
		if(any < 2) break;
		if(any == 2)
		{
			for(int i=0; i<S; i++)
			{
				int k = (i+S-1) % S;
				double hh = h[i] - hmin;
				ans += hh * (tth[i] + tth[k]) / 2;
			}
		}

		nowh = hmin;
		vln.erase(vln.begin() + idx);
	}

	return ans;
}

int main() {
	FILEIO("roof");
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
	{
		cin>>pt[i].x>>pt[i].y;
	}

	double ans = calc();
	cout<<fixed<<setprecision(20)<<ans<<endl;

    return 0;
}
