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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<pdd, pdd> Line;

const int MAXN = 11;
const ld INF = 1E20;
const ld EPS = 1E-7;
const ld PI = acosl(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld abs(pdd a){return sqrtl(dot(a, a));}
pdd angle(ld th){return {cosl(th), sinl(th)};}
ld theta(pdd x){return atan2l(x.S, x.F);}

int N;
ld X, Y;
pdd pt[MAXN];
ld pr[MAXN];
vector<Line> vline;
vector<pdd> vpt;

bool check(pdd x)
{
	if(x.F < -EPS || x.F > X+EPS || x.S < -EPS || x.S > Y+EPS)
		return false;
	for(int i=0; i<N; i++)
	{
		ld dis = abs(x - pt[i]);
		if(dis < pr[i] - EPS)
			return false;
	}

	vector<pdd> vth;
	for(int i=0; i<N; i++)
	{
		ld phi = theta(pt[i] - x);
		ld dis = abs(pt[i] - x);
		ld th = asinl(pr[i] / dis); 
		vth.PB({phi-th, phi+th});
		vth.PB({phi-th+2*PI, phi+th+2*PI});
	}

	sort(ALL(vth));
	int L = vth.size();
	for(int i=0; i<L-1; i++)
		if(vth[i].S > vth[i+1].F + EPS)
			return false;

	return true;
}

pdd calc()
{
	vline.PB({{0, 0}, {X, 0}});
	vline.PB({{X, 0}, {X, Y}});
	vline.PB({{X, Y}, {0, Y}});
	vline.PB({{0, Y}, {0, 0}});

	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			pdd p1 = pt[i], p2 = pt[j];
			ld r1 = pr[i], r2 = pr[j];

			ld d = abs(p1 - p2);
			ld r = r1 + r2;

			if(abs(r-d) > EPS)
			{
				ld th = acosl(r / d);
				ld phi = theta(p2 - p1);

				pdd p1p = p1 + angle(th + phi) * r1;
				pdd p1m = p1 + angle(-th + phi) * r1;
				pdd p2m = p2 + angle(-th + phi + PI) * r2;
				pdd p2p = p2 + angle(th + phi + PI) * r2;

				vline.PB({p1p, p2p});
				vline.PB({p1m, p2m});
			}
			else
			{
				pdd dif = p2 - p1;
				ld rat = r1 / r;
				pdd x = p1 + dif * rat;
				pdd ten = {-dif.S, dif.F};
				vline.PB({x, x+ten});
			}
		}
	}

//	cout<<vline<<endl<<endl;

	int L = SZ(vline);
	for(int i=0; i<L; i++)
	{
		for(int j=i+1; j<L; j++)
		{
			Line l1 = vline[i], l2 = vline[j];
			pdd p1 = l1.F, p2 = l1.S, q1 = l2.F, q2 = l2.S;
			ld f1 = cross(p2 - p1, q1 - p1);
			ld f2 = cross(p2 - p1, p1 - q2);
			ld f = f1 + f2;

			if(abs(f) < EPS)
				continue;
			pdd x = q1 * (f2 / f) + q2 * (f1 / f);
			vpt.PB(x);
		}
	}

	for(int i=0; i<L; i++)
	{
		for(int j=0; j<N; j++)
		{
			pdd p = vline[i].F - pt[j], p2 = vline[i].S - pt[j];
			pdd v = p2 - p;
			ld r = pr[j];
			ld dt = dot(p, v);
			ld sq = dt * dt - dot(v, v) * (dot(p, p) - r * r);
			if(sq < 0) continue;
			sq = sqrtl(sq);
			ld t1 = (-dt + sq) / dot(v, v);
			ld t2 = (-dt - sq) / dot(v, v);
			pdd x1 = p + v * t1;
			pdd x2 = p + v * t2;
			vpt.PB(x1);
			vpt.PB(x2);
		}
	}

//	cout<<vpt<<endl;

	for(auto p: vpt)
		if(check(p))
			return p;

	return {INF, INF};
}

int main() {
	IOS;
	FILEIO("zen");

	cin>>N>>X>>Y;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S>>pr[i];

	pdd ans = calc();
	if(ans.F == INF)
		cout<<"No Zen"<<endl;
	else
		cout<<fixed<<setprecision(12)<<ans.F<<" "<<ans.S<<endl;

    return 0;
}
