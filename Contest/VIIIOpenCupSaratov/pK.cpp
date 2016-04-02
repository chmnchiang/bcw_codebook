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

typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<ld, int> pdi;

const int MAXN = 202020;
const ld PI = acosl(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrtl(dot(a, a));}
ld angle(pdd a){return atan2l(a.S, a.F);}
pdd polar(ld r, ld th){return {r*cosl(th), r*sinl(th)};}

int N, K;
ld alpha;
pdd pt[MAXN];
ld dis[MAXN], theta[MAXN];

ld reg(ld th)
{
	while(th < 0) th += 2*alpha;
	while(th >= 2*alpha) th -= 2*alpha;
	return th;
}

bool test(ld R)
{
	ld D = R * cosl(alpha);
	vector<pdi> vseg;
	for(int i=0; i<N; i++)
	{
		ld r = dis[i], th = theta[i];
		if(r > R) return false;
		if(r > D)
		{
			ld phi = acosl(D / r);
			ld lb = reg(th + phi), rb = reg(th + 2*alpha - phi);
			if(lb < rb)
			{
				vseg.PB({lb, 1});
				vseg.PB({rb, -1});
			}
			else
			{
				vseg.PB({0, 1});
				vseg.PB({rb, -1});
				vseg.PB({lb, 1});
				vseg.PB({2*alpha, -1});
			}
		}
		else
		{
			vseg.PB({0, 1});
			vseg.PB({2*alpha, -1});
		}
	}

	sort(ALL(vseg));
	int cnt = 0;
	for(auto p: vseg)
	{
		cnt += p.S;
		if(cnt == N)
			return true;
	}

	return false;
}

ld calc()
{
	for(int i=0; i<N; i++)
	{
		dis[i] = abs(pt[i]);
		theta[i] = angle(pt[i]);
	}
	
	alpha = PI / K;
	ld lb = 0, rb = 1E7;
	for(int i=0; i<80; i++)
	{
		ld mb = (lb + rb) / 2;
		if(test(mb))
			rb = mb;
		else
			lb = mb;
	}
	return lb;
}

int main() {
	IOS;
	FILEIO("tower");

	cin>>N>>K;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	ld ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}

