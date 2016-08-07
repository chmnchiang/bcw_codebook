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

pdd operator+(const pdd &a, const pdd &b){return {a.F+b.F, a.S+b.S};}
pdd operator-(const pdd &a, const pdd &b){return {a.F-b.F, a.S-b.S};}
pdd operator*(const pdd &a, const double &b){return {a.F*b, a.S*b};}
double cross(const pdd &a, const pdd &b){return a.F*b.S-a.S*b.F;}
double dot(const pdd &a, const pdd &b){return a.F*b.F+a.S*b.S;}
double abs(const pdd &a){return sqrt(dot(a, a));}
double angle(const pdd &a){return atan2(a.S, a.F);}

const int MAXN = 15;
const double EPS = 1E-9;
const double PI = acos(-1);
const pdd BAD = {1234782342, 54738282123};

int N;
double LB, RB;
pdd pt[MAXN];

vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
  if(abs(o1 - o2) < EPS) return {};
  double d2 = dot(o1 - o2, o1 - o2);
  double d = sqrt(d2);
  if (d > r1+r2 or d < abs(r1-r2)) return {};
  pdd u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  double A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  pdd v = pdd(o1.S-o2.S, -o1.F+o2.F) * (A / (2*d2));
  return {u+v, u-v};
}

pdd calc()
{
	vector<pdd> ipts;
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			pdd d = pt[j] - pt[i];
			d = d * (1. / abs(d));
			pdd t = {d.S, -d.F};

			for(int k=0; k<N; k++)
			{
				for(int l=0; l<2; l++)
				{
					pdd c = pt[k];
					pdd v = pt[i] - c;
					double r = (l==0 ? LB : RB);
					
					double h = cross(v, d);
					double zz = r*r-h*h;
					if(zz < 0) continue; 
					double x = sqrt(zz);
					ipts.PB(c + t * h + d * x);
					ipts.PB(c + t * h - d * x);
				}
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		for(int ii=0; ii<2; ii++)
		{
			for(int j=0; j<N; j++)
			{
				for(int jj=0; jj<2; jj++)
				{
					pdd c1 = pt[i], c2 = pt[j];
					double r1 = (ii==0 ? LB : RB), r2 = (jj==0 ? LB : RB);
					vector<pdd> vi = interCircle(c1, r1, c2, r2);
					ipts.insert(ipts.end(), ALL(vi));
				}
			}
		}
	}

	pdd ans = BAD;
	double bst = 12345;

	for(auto v: ipts)
	{
		bool ok = true;
		for(int i=0; i<N; i++)
		{
			double dis = abs(v - pt[i]);
			if(dis < LB - EPS or dis > RB + EPS)
				ok = false;
		}

		if(!ok) continue;

		vector<double> angles;
		for(int i=0; i<N; i++)
			angles.PB(angle(pt[i] - v));
		sort(ALL(angles));

		double anan = 1234;
		for(int i=0; i<N; i++)
		{
			int j = (i+1) % N;
			double dif = angles[i] - angles[j];
			while(dif < EPS) dif += 2 * PI;
			anan = min(anan, dif);
		}

	//	cout<<v<<" : "<<anan<<endl;

		if(anan < PI + EPS and anan < bst)
		{
			bst = anan;
			ans = v;
		}
	}
	
	return ans;
}

int main() {
	FILEIO("shepherd");

	cin>>N>>LB>>RB;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	pdd ans = calc();
	if(ans == BAD) cout<<"impossible"<<endl;
	else cout<<fixed<<setprecision(10)<<ans.F<<" "<<ans.S<<endl;

    return 0;
}

