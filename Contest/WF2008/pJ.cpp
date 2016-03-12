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

typedef long long ll;
typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<pdd, pdd> Line;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(ld a, pdd b){return {a*b.F, a*b.S};}
ld operator%(pdd a, pdd b){return {a.F*b.S-a.S*b.F};}

const int MAXN = 50505;
const ld INF = 1E9;
const ld EPS = 1E-8;

int N;
Line pt[MAXN];
vector<ld> vpos;

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	double f1 = (p2 - p1) % (q1 - p1);
	double f2 = (p2 - p1) % (p1 - q2);
	double f = (f1 + f2);

	if(fabs(f) < EPS) return pdd(INF, INF);
	return (f2 / f) * q1 + (f1 / f) * q2;
}

ld calc()
{
	vpos.clear();
	for(int i=0; i<2*N; i++)
	{
		vpos.PB(pt[i].F.F);
		vpos.PB(pt[i].S.F);
		for(int j=i+1; j<2*N; j++)
		{
			pdd ip = interPnt(pt[i].F, pt[i].S, pt[j].F, pt[j].S);
			if(ip.F != INF)
				vpos.PB(ip.F);
		}
	}

	sort(ALL(vpos));
	int V = unique(ALL(vpos)) - vpos.begin();
	vpos.resize(V);

	ld ans = 0;
	ld lmx = 0;
	ld lx = -INF;
	for(int i=0; i<V; i++)
	{
		ld mx = 0;
		ld x = vpos[i];
		for(int j=0; j<2*N; j++)
		{
			if(x < pt[j].F.F-EPS || x > pt[j].S.F+EPS) continue;
			ld rat = (x - pt[j].F.F) / (pt[j].S.F - pt[j].F.F);
			ld y = pt[j].F.S + rat * (pt[j].S.S - pt[j].F.S);
			mx = max(mx, y);
		}
//		cout<<x<<","<<mx<<endl;
		if(lmx >= EPS || mx >= EPS)
		{
			ld dx = x - lx, dy = mx - lmx;
			ld dis = sqrtl(dx * dx + dy * dy);
			ans += dis;
		}
		lmx = mx;
		lx = x;
	}

	return ans;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N && N)
	{
		t++;
		ld X, H, B;
		for(int i=0; i<N; i++)
		{
			cin>>X>>H>>B;
			pt[2*i] = {{X-B/2, 0}, {X, H}};
			pt[2*i+1] = {{X, H}, {X+B/2, 0}};
		}

		ll ans = calc() + 0.5 + 1E-8;
		cout<<"Case "<<t<<": "<<ans<<endl<<endl;
	}

    return 0;
}

