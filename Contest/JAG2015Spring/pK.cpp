#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const double PI = acos(-1);

double X, Y, TH, W, R, DIFFTH;

bool test(double v)
{
	double r0 = v / W;
	double dth = acos(r0 / R);
	double totalth = dth + DIFFTH;
	double dis = sqrt(R*R-r0*r0);
	double tm = dis / v;
	return W * tm < totalth;
}

int main() {
	IOS;
	cin>>X>>Y>>TH>>W;

	TH *= PI / 180;
	W *= PI / 180;
	R = sqrt(X*X+Y*Y);

	DIFFTH = atan2(Y, X) - TH;
	while(DIFFTH < -PI) DIFFTH += 2 * PI;
	DIFFTH = abs(DIFFTH);

	double lb = 1E-10, rb = R * W;
	while(rb - lb > 1E-12)
	{
		double mb = (lb + rb) / 2;
		if(test(mb))
			rb = mb;
		else
			lb = mb;
	}


	double ans = (lb + rb) / 2;
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

