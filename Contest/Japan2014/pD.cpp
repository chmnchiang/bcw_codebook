#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MAXN = 101;
const double EPS = 1E-9;

int N, B;
double D;

double p[MAXN], h[MAXN];

double calc(int b)
{
	double d = D / b;
	double hmx = d / 4;
	for(int i=0; i<N; i++)
	{
		double x = fmod(p[i], d) - d / 2.;
		double rat = 1. - (4. * x * x) / (d * d);
		if(rat < EPS)
			return 1E20;
		double nh = h[i] / rat;
		hmx = max(hmx, nh);
	}
	double vy = sqrt(hmx * 2.);
	double vx = d / (2. * vy);
	double v = sqrt(vx * vx + vy * vy);
	return v;
}

int main() {
	IOS;
	cin>>D>>N>>B;
	for(int i=0; i<N; i++)
		cin>>p[i]>>h[i];

	double ans = 1E20;
	for(int i=1; i<=B+1; i++)
		ans = min(ans, calc(i));

	cout<<fixed<<setprecision(10)<<ans<<endl;

    return 0;
}

