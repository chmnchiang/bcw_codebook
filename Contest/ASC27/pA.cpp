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

#define y1 wefoijwefio

const double PI = acos(-1);

double x1, y1, r1, b1, e1;
double x2, y2, r2, b2, e2;

double calc()
{
	b1 *= PI / 180;
	e1 *= PI / 180;
	b2 *= PI / 180;
	e2 *= PI / 180;

	if(e1 < b1) e1 += 2*PI;
	if(e2 < b2) e2 += 2*PI;

	double ob1 = b1, oe1 = e1;
	double ob2 = b2, oe2 = e2;

	double th1 = b1, th2 = b2, bdis=1E20;
	double EPS = 0.005;

	while(EPS > 1E-15)
	{
		bdis = 1E20;
		for(double x=b1; x<e1; x+=EPS)
		{
			for(double y=b2; y<e2; y+=EPS)
			{
				if(x < ob1 || x > oe1 || y < ob2 || y > oe2) continue;
				double dx = (x2 + r2 * cos(y)) - (x1 + r1 * cos(x));
				double dy = (y2 + r2 * sin(y)) - (y1 + r1 * sin(x));
				double dis = sqrt(dx*dx+dy*dy);
				if(dis < bdis)
				{
					bdis = dis;
					th1 = x;
					th2 = y;
				}
			}
		}
		b1 = th1 - 2*EPS;
		e1 = th1 + 2*EPS;
		b2 = th2 - 2*EPS;
		e2 = th2 + 2*EPS;
		EPS *= 0.1;
	}


	return bdis;
}

int main() {
	IOS;
	FILEIO("circular");

	cin>>x1>>y1>>r1>>b1>>e1;
	cin>>x2>>y2>>r2>>b2>>e2;

	double ans = calc();
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

