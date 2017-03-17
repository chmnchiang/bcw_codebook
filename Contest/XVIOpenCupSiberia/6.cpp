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



const double PI = acos(-1);
const double EPS = 1E-8;

double T1, T2, Tmax, alpha, phi, lambda, delta, xi0, calpha, salpha, sphi, cphi;

double get_eta(double t)
{
	return 2 * PI * t / T2 + lambda;
}

double get_mu(double t)
{
	double xi = 2 * PI * t / T1 + xi0;
	int round = floor(xi / (2*PI));

	double x = cos(xi), y = sin(xi) * calpha;
	double dxi = atan2(y, x);
	if(dxi < -1E-15) dxi += 2*PI;

	return round * 2*PI + dxi;
}

double get_phi(double t)
{
	double xi = 2 * PI * t / T1 + xi0;
	return asin(salpha * sin(xi));
}

double get_dif(double t)
{
	return get_mu(t) - get_eta(t);
}

double get_time(double dif, double curt)
{
	double lb = curt - T2*10, rb = curt + T2*10;
	for(int i=0; i<100; i++)
	{
		if(rb - lb < EPS) continue;
		double mb = (lb + rb) / 2;
		if(get_dif(mb) < dif) lb = mb;
		else rb = mb;
	}
	return (lb+rb)/2;
}

double get_cdis(double t)
{
	double xi = 2 * PI * t / T1 + xi0;
	double eta = get_eta(t);
	
	double sxi = sin(xi);
	double x = cos(xi), y = sxi * calpha, z = sxi * salpha;
	double xx = cphi * cos(eta), yy = cphi * sin(eta), zz = sphi;

	double inn = x * xx + y * yy + z * zz;
	return acos(min(1., inn));
}

void calc()
{
	xi0 = atan2(sin(lambda), calpha * cos(lambda));
	if(xi0 < -EPS) xi0 += 2*PI;

	/*for(double i=0; i<1000; i+=10)
	{
		double dx = get_dif(i);
		cout<<i<<" : D "<<dx<<endl;
//		cout<<i<<" : ETA "<<get_eta(i)<<" MU "<<get_mu(i)<<endl;
	}*/

	double curt = 0;
	int round = 0;
	while(curt < Tmax + T2*10)
	{
		double rpi = round * 2 * PI;
		double tm = get_time(rpi, curt);
		//cout<<round<<" : "<<tm<<" PH "<<get_phi(tm)<<" DEL "<<get_dif(tm)<<endl;

		double lf = get_time(rpi-0.04, tm);
		double rf = get_time(rpi+0.04, tm);

		double lb = lf, rb = rf;
		for(int i=0; i<100; i++)
		{
			if(rb - lb < EPS) break;
			double m1 = (lb+lb+rb)/3, m2 = (lb+rb+rb)/3;
			double v1 = get_cdis(m1), v2 = get_cdis(m2);
			if(v1 < v2) rb = m2;
			else lb = m1;
		}
		double cen = (lb + rb) / 2;
		double cval = get_cdis(cen);
		//cout<<lf<<"~"<<rf<<" CEN At "<<cen<<" DIS "<<cval<<endl;

		if(cval < delta)
		{
			lb = lf, rb = cen;
			for(int i=0; i<100; i++)
			{
				if(rb - lb < EPS) break;
				double mb = (lb + rb) / 2;
				if(get_cdis(mb) > delta) lb = mb;
				else rb = mb;
			}
			double lin = (lb + rb) / 2;

			lb = cen, rb = rf;
			for(int i=0; i<100; i++)
			{
				if(rb - lb < EPS) break;
				double mb = (lb + rb) / 2;
				if(get_cdis(mb) > delta) rb = mb;
				else lb = mb;
			}
			double rin = (lb + rb) / 2;

			lin = max(lin, 2*T1);
			rin = min(rin, Tmax);
			if(lin < rin)
			{
//				cout<<" !!! INSIDE "<<lin<<" ~ "<<rin<<endl;
				cout<<lin<<endl;
				return;
			}
		}

		curt = tm;
		round++;
	}

	cout<<"-1"<<endl;
}

int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;

	cout<<fixed<<setprecision(10);
	cin>>T1>>T2>>Tmax>>alpha>>phi>>lambda>>delta;
	alpha *= PI / 180;
	phi *= PI / 180;
	lambda *= PI / 180;
	delta *= PI / 180;
	calpha = cos(alpha);
	salpha = sin(alpha);
	cphi = cos(phi);
	sphi = sin(phi);

	calc();

	return 0;
}

