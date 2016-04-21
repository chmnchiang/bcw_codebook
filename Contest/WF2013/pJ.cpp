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

typedef pair<double, double> pdd;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, double b){return {a.F*b, a.S*b};}
double dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double abs(pdd a){return sqrt(dot(a, a));}
pdd norm(pdd a){return a * (1 / abs(a));}

const int MAXN = 105;
const double EPS = 1E-8;

int N;
double R;
pdd pt[MAXN];

double calc2(pdd p1, pdd p2)
{
//	cout<<p1<<" ~ "<<p2<<endl;
	int flag = 1;
	if(p1.F > p2.F)
	{
		flag = -1;
		swap(p1, p2);
	}

	double ans = 0;
	pdd cen = p1 * 0.514 + p2 * 0.486;
	if(abs(cen) > R)
	{
		double th1 = asin(max(min(p1.F / R, 1.), -1.));
		double th2 = asin(max(min(p2.F / R, 1.), -1.));
		ans = R * R * ((th2 - th1) / 2 + (sin(2*th2) - sin(2*th1)) / 4);
	}
	else
	{
		ans = (p2.F - p1.F) * (p1.S + p2.S) / 2;
	}

	return ans * flag;
}

double calc()
{
	double ans = 0;

	for(int i=0; i<N; i++)
	{
		pdd p1 = pt[i], p2 = pt[(i+1)%N];
		pdd d = p2 - p1;
		vector<double> vt;
		vt.PB(0);
		vt.PB(1);

		double a = dot(d, d), b = 2 * dot(p1, d), c = dot(p1, p1) - R * R;
		double del = b * b - 4 * a * c;
		if(del >= 0)
		{
			double sdel = sqrt(del);
			double tp = (-b + sdel) / (2 * a);
			double tm = (-b - sdel) / (2 * a);
			if(0 < tp && tp < 1) vt.PB(tp);
			if(0 < tm && tm < 1) vt.PB(tm);
		}
		sort(ALL(vt));
//		cout<<p1<<" "<<p2<<" "<<vt<<endl;
		for(int j=0; j<SZ(vt)-1; j++)
		{
			double res = calc2(p1 + d * vt[j], p1 + d * vt[j+1]);
			ans -= res;
		}
	}

	return ans;
}

int main() {
	IOS;
	cin>>N>>R;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}

