#pragma GCC optimize ("O2")
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

typedef pair<double, int> pdi;

const double EPS = 1E-9;
const double PI = acos(-1);
const int MAXN = 2020;

struct Point
{
	double x, y, z;
};

Point operator+(Point a, Point b){return {a.x+b.x, a.y+b.y, a.z+b.z};}
Point operator-(Point a, Point b){return {a.x-b.x, a.y-b.y, a.z-b.z};}
Point operator*(Point a, double b){return {a.x*b, a.y*b, a.z*b};}
double dot(Point a, Point b){return a.x*b.x+a.y*b.y+a.z*b.z;}
Point cross(Point a, Point b)
{
	return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};
}
double abs(Point a){return sqrt(dot(a, a));}
Point norm(Point a){return a * (1. / abs(a));}

ostream& operator <<(ostream &s, const Point &c) {
    return s << "("<<c.x<<","<<c.y<<","<<c.z<<")";
}

double reg(double x)
{
	while(x < -PI) x += 2*PI;
	while(x >= PI) x -= 2*PI;
	return x;
}

int N;
double alpha, talpha;
Point pc, pt[MAXN];

int calc()
{
	int ans = 1;
	for(int i=0; i<N; i++)
	{
		Point rd = {1.234, 5.472, 8.7323};
		Point xh = norm(cross(pt[i], rd));
		Point yh = norm(cross(pt[i], xh));

		int base = 0;
		vector<pdi> vec;
		for(int j=0; j<N; j++)
		{
			if(abs(pt[i] - pt[j]) < EPS)
			{
				base++;
				continue;
			}

			double theta = 0.5 * acos(dot(pt[i], pt[j]));
			double rat = tan(theta) / talpha;
			if(rat >= 1) continue;
			double delta = acos(rat);

			double xp = dot(pt[j], xh);
			double yp = dot(pt[j], yh);
			double phi = atan2(yp, xp);

			double lb = reg(phi - delta), rb = reg(phi + delta);

			//cout<<lb<<"~"<<rb<<endl;
			vec.PB({lb, 1});
			vec.PB({rb, -1});
			if(lb > rb)
				base++;
		}

		sort(ALL(vec));
		int cur = base;
		for(auto p: vec)
		{
			cur += p.S;
			ans = max(ans, cur);
		}
	}

	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>alpha;
		alpha *= PI / 180;
		alpha += EPS;
		talpha = tan(alpha);
		cin>>pc.x>>pc.y>>pc.z;
		for(int i=0; i<N; i++)
		{
			cin>>pt[i].x>>pt[i].y;
			pt[i].z = 0;
			pt[i] = pt[i] - pc;
			pt[i] = norm(pt[i]);
		}

		int ans = calc();
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

