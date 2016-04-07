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

const int MAXN = 102;
const double INF = 1e20;
const double EPS = 1e-8;

int N;
pdd pt[MAXN];

double calc()
{
	double area = 0;
	for(int i=0; i<N; i++)
	{
		int j = (i+1) % N;
		area += cross(pt[i], pt[j]);
	}
	if(area < 0)
		reverse(pt, pt+N);

	double ans = INF;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(i == j) continue;
			double cur = 0;
			pdd d = pt[j] - pt[i];
			d = d * (1. / abs(d));
			bool ok = true;
			for(int k=0; k<N; k++)
			{
				double z = cross(d, pt[k] - pt[i]);
				if(z < -EPS)
					ok = false;
				cur = max(cur, z);
			}
			if(ok)
				ans = min(ans, cur);
		}
	}

	return ceil(ans*100-EPS) / 100;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N && N)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		double ans = calc();
		cout<<"Case "<<t<<": "<<fixed<<setprecision(2)<<ans<<endl;
	}

	return 0;
}

