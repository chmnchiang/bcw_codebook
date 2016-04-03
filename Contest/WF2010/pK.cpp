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

typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pdd;

struct Point
{
	ll x, y, z;
};

bool operator==(Point a, Point b) {return a.x==b.x && a.y==b.y && a.z==b.z;}
Point operator+(Point a, Point b) {return {a.x+b.x, a.y+b.y, a.z+b.z};}
Point operator-(Point a, Point b) {return {a.x-b.x, a.y-b.y, a.z-b.z};}
Point operator*(Point a, ll b) {return {a.x*b, a.y*b, a.z*b};}
ll dot(Point a, Point b) {return a.x*b.x+a.y*b.y+a.z*b.z;}
Point cross(Point a, Point b) {return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};}
ld abs(Point a) {return sqrtl(dot(a, a));}
ll volume(Point a, Point b, Point c, Point d) {return dot(cross(b-a, c-a), d-a);}

ostream& operator <<(ostream &s, const Point &p) {
    return s<<"("<<p.x<<","<<p.y<<","<<p.z<<")";
}

const ld INF = 1e20;

ll V;
Point pt[5], F, M;
ll dis[5];

bool check_edge(Point P, Point Q, Point n)
{
	Point t = cross(n, Q-P); 
	ld dd = 0;
	dd += (ld)t.x * ((ld)M.x/V-P.x);
	dd += (ld)t.y * ((ld)M.y/V-P.y);
	dd += (ld)t.z * ((ld)M.z/V-P.z);
	ld a = 0;
	a += (ld) t.x * t.x;
	a += (ld) t.y * t.y;
	a += (ld) t.z * t.z;
	dd /= sqrtl(a);
//	ld dd = dot(t, M - P * V) / (V * abs(t));
//	cout<<dd<<endl;
	return dd >= 0.2;
}

ld get_dis(Point P, Point Q, Point R)
{
	Point PQ = Q - P, PR = R - P;
	Point n = cross(PQ, PR);
	if(dot(n, n) == 0) return INF;

	for(int i=0; i<5; i++)
	{
		dis[i] = dot(n, pt[i] - P);
		if(dis[i] < 0) return INF;
	}
//	cout<<P<<" "<<Q<<" "<<R<<endl;

	double dd = dot(n, F - P) / abs(n);

	bool four = false;
	Point X;

	for(int i=0; i<5; i++)
	{
		if(pt[i] == P || pt[i] == Q || pt[i] == R)
			continue;
		if(dis[i] == 0)
		{
			four = true;
			X = pt[i];
		}
	}
	//cout<<P<<" "<<Q<<" "<<R<<" : "<<dd<<endl;

	if(!four)
	{
		if(!check_edge(P, Q, n)) return INF;
		if(!check_edge(Q, R, n)) return INF;
		if(!check_edge(R, P, n)) return INF;
	}
	else
	{
//		assert(false);
//		cout<<"FOUR!! "<<X<<endl;

		bool d1 = dot(cross(X-P, R-P), cross(X-P, Q-P)) <= 0;
		bool d2 = dot(cross(X-Q, P-Q), cross(X-Q, R-Q)) <= 0;
		bool d3 = dot(cross(X-R, P-R), cross(X-R, Q-R)) <= 0;
		
//		cout<<d1<<" "<<d2<<" "<<d3<<endl;

		if(d1 && d2 && d3)
		{
			if(!check_edge(P, Q, n)) return INF;
			if(!check_edge(Q, R, n)) return INF;
			if(!check_edge(R, P, n)) return INF;
		}
		else if(d1)
		{
			if(!check_edge(P, Q, n)) return INF;
			if(!check_edge(Q, X, n)) return INF;
			if(!check_edge(X, R, n)) return INF;
			if(!check_edge(R, P, n)) return INF;
		}
		else if(d2)
		{
			if(!check_edge(Q, R, n)) return INF;
			if(!check_edge(R, X, n)) return INF;
			if(!check_edge(X, P, n)) return INF;
			if(!check_edge(P, Q, n)) return INF;
		}
		else if(d3)
		{
			if(!check_edge(R, P, n)) return INF;
			if(!check_edge(P, X, n)) return INF;
			if(!check_edge(X, Q, n)) return INF;
			if(!check_edge(Q, R, n)) return INF;
		}
	}

	return dd;
}

pdd calc()
{
	V = 0;
	M = {0, 0, 0};

	ld v = abs(volume(pt[0], pt[1], pt[2], pt[3]));
	Point p = (pt[0] + pt[1] + pt[2] + pt[3]);
	V += v * 4;
	M = M + p * v;

	v = abs(volume(pt[0], pt[1], pt[2], pt[4]));
	p = (pt[0] + pt[1] + pt[2] + pt[4]);
	V += v * 4;
	M = M + p * v;

//	cout<<(double)M.x/V<<","<<(double)M.y/V<<","<<(double)M.z/V<<endl;

	ld mind = INF, maxd = -INF;

	for(int i=0; i<5; i++)
	{
		for(int j=i+1; j<5; j++)
		{
			for(int k=j+1; k<5; k++)
			{
				ld res = get_dis(pt[i], pt[j], pt[k]);
				if(res != INF)
				{
					mind = min(mind, res);
					maxd = max(maxd, res);
				}
				res = get_dis(pt[i], pt[k], pt[j]);
				if(res != INF)
				{
					mind = min(mind, res);
					maxd = max(maxd, res);
				}
			}
		}
	}

	/*vector<Point> vec;
	vec.PB({0, 1, 3});
	vec.PB({1, 2, 3});
	vec.PB({0, 2, 3});
	vec.PB({0, 1, 4});
	vec.PB({1, 2, 4});
	vec.PB({0, 2, 4});
	for(auto pp: vec)
	{
		int i = pp.x, j = pp.y, k = pp.z;
		ld res = get_dis(pt[i], pt[j], pt[k]);
		if(res != INF)
		{
			mind = min(mind, res);
			maxd = max(maxd, res);
		}
		res = get_dis(pt[i], pt[k], pt[j]);
		if(res != INF)
		{
			mind = min(mind, res);
			maxd = max(maxd, res);
		}
	}*/

	assert(mind != INF && maxd != INF);
	return {mind, maxd};
}

int main() {
	IOS;

	int t = 0;
	while(1)
	{
		t++;
		bool ok = true;
		for(int i=0; i<5; i++)
			if(!(cin>>pt[i].x>>pt[i].y>>pt[i].z))
				ok = false;
		if(!(cin>>F.x>>F.y>>F.z))
			ok = false;
		if(!ok)
			break;

		pdd res = calc();
		cout<<"Case "<<t<<": "<<fixed<<setprecision(5)<<res.F<<" "<<res.S<<endl;
	}

	return 0;
}

