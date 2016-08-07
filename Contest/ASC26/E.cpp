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



struct Point
{
	double x, y, z;
};

const double EPS = 1E-8;
const double PI = acos(-1);

double R, D;
Point P, Q, C1, C2;

Point operator-(const Point &a, const Point &b) {return {a.x-b.x, a.y-b.y, a.z-b.z};}
Point operator*(const Point &a, const double &b) {return {a.x*b, a.y*b, a.z*b};}
Point cross(const Point &a, const Point &b){return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};}
double abs(Point &a){return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}

void print(const Point &a){cout<<"("<<a.x<<","<<a.y<<","<<a.z<<")"<<endl;}

double dis(Point a, Point b)
{
	double dx = a.x-b.x;
	double dy = a.y-b.y;
	double dz = a.z-b.z;
	return sqrt(dx*dx+dy*dy+dz*dz);
}

double arcdis(Point a, Point b)
{
	double x = dis(a, b);
	return 2 * R * asin(x / (2*R));
}

double calc()
{
	C1 = Point({0, 0, -D/2});
	C2 = Point({0, 0, D/2});

	double dp1 = dis(P, C1);
	double dp2 = dis(P, C2);
	double dq1 = dis(Q, C1);
	double dq2 = dis(Q, C2);

	if((dp1 < R+EPS and dq1 < R+EPS) or (dp2 < R+EPS and dq2 < R+EPS))
	{
		if(P.z > 0)
		{
			P.z *= -1;
			Q.z *= -1;
		}

		Point vp = P - C1, vq = Q - C1;
		Point crs = cross(vp, vq);
//		print(vp); print(vq);
//		print(crs);
		double len = abs(crs);
		if(len < EPS) return arcdis(P, Q);

		Point crs2 = cross(crs, Point({0, 0, 1}));
		double len2 = abs(crs2);
		double rat = len2 / len;
//		cout<<rat<<endl;
		double highz = rat * R - D/2;
//		cout<<highz<<endl;

		Point crs3 = cross(crs2, crs);
		double len3 = abs(crs3);
		crs3 = crs3 * (R / len3);
		if(crs3.z < 0) crs3 = crs3 * -1.;
		crs3.z -= D/2;

		if(crs3.z < 0) return arcdis(P, Q);
		if(arcdis(P, crs3) + arcdis(crs3, Q) > arcdis(P, Q) + EPS) return arcdis(P, Q);

		Q.z *= -1;
	}

	double H = sqrt(R * R - D * D / 4);
	int K = 1000000;
	double ans = 1E20;
	double bestphi = 0;
	for(int i=0; i<K; i++)
	{
		double phi = 2 * PI * i / K;
		Point Z({cos(phi) * H, sin(phi) * H, 0});
		double val = arcdis(P, Z) + arcdis(Z, Q);
		if(val < ans)
		{
			ans = val;
			bestphi = phi;
		}
	}
	for(int i=0; i<K; i++)
	{
		double phi = bestphi - (2 * PI / K) + (4 * PI * i / K / K);
		Point Z({cos(phi) * H, sin(phi) * H, 0});
		double val = arcdis(P, Z) + arcdis(Z, Q);
		if(val < ans)
		{
			ans = val;
			bestphi = phi;
		}
	}


	return ans;
}

int main() {
	FILEIO("path");

	cin>>R>>D;
	cin>>P.x>>P.y>>P.z;
	cin>>Q.x>>Q.y>>Q.z;
	P.z -= D/2;
	Q.z -= D/2;

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

    return 0;
}

