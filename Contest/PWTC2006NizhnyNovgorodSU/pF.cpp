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
pdd norm(pdd a){return a * (1. / abs(a));}

const double EPS = 1E-8;

double Lm, Lg;
pdd pt[3];

bool calc()
{
	if(abs(cross(pt[1]-pt[0], pt[2]-pt[0])) < EPS)
	{
		if(abs(pt[1]-pt[0]) > max(Lm, 2*Lg) + EPS) return false;
		if(abs(pt[2]-pt[0]) > max(Lm, 2*Lg) + EPS) return false;
		if(abs(pt[2]-pt[1]) > max(Lm, 2*Lg) + EPS) return false;
		return true;
	}

	for(int i=0; i<3; i++)
	{
		pdd p1 = pt[i], p2 = pt[(i+1)%3], p3 = pt[(i+2)%3];
		pdd d = norm(p2 - p1);
		double t = dot(d, p3 - p1);
		pdd ipt = p1 + d * t;
		if(abs(p1-ipt) < Lg + EPS && abs(p2-ipt) < Lg + EPS && abs(p3-ipt) < Lm + EPS) return true;
		if(abs(p1-ipt) < Lm + EPS && abs(p2-ipt) < Lm + EPS && dot(p1-ipt, p2-ipt) > -EPS && abs(p3-ipt) < Lg + EPS) return true;
	}

	return false;
}

int main() {
	IOS;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>Lm>>Lg;
		for(int i=0; i<3; i++)
			cin>>pt[i].F>>pt[i].S;
		bool res = calc();
		cout<<(res ? "YES" : "NO")<<"\n";
	}

	return 0;
}
