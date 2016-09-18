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

typedef pair<int, int> pii;

pii operator+(pii a, pii b){return {a.F+b.F, a.S+b.S};}
pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}
int dot(pii a, pii b){return a.F*b.F+a.S*b.S;}
int cross(pii a, pii b){return a.F*b.S-a.S*b.F;}
double abs(pii a){return sqrt(dot(a, a));}

const int MAXN = 105;
const double INF = 1E20;

int N;
pii pt[2][MAXN];
int W;
vector<pii> pts[MAXN];
vector<double> dps[MAXN];

bool check(pii p1, pii p2)
{
	for(int i=0; i<=N; i++)
	{
		int x = pt[0][i].F;
		if(x < p1.F or x > p2.F) continue;
		int val = (p2.S-p1.S) * (x-p1.F);
		int lb = (pt[0][i].S-p1.S) * (p2.F-p1.F);
		int rb = (pt[1][i].S-p1.S) * (p2.F-p1.F);
		if(lb > val or val > rb)
			return false;
	}

	return true;
}

double calc()
{
	for(int i=1; i<N; i++)
	{
		pts[i].PB(pt[0][i]);
		pts[i].PB(pt[1][i]);
	}

	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<2; j++)
		{
			pts[0].PB({pt[0][0].F, pt[j][i].S});
			pts[N].PB({pt[0][N].F, pt[j][i].S});
		}
	}

	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<SZ(pts[i]); j++)
			dps[i].PB(i==0 ? 0 : INF);
	}
	
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<SZ(pts[i]); j++)
		{
			for(int k=0; k<i; k++)
			{
				for(int l=0; l<SZ(pts[k]); l++)
				{
					if(!check(pts[k][l], pts[i][j])) continue;
					dps[i][j] = min(dps[i][j], dps[k][l] + abs(pts[i][j] - pts[k][l]));
				}
			}
		}
	}

	double ans = INF;
	for(auto x: dps[N])
		ans = min(ans, x);

	return ans;
}

int main() {
	IOS;
	FILEIO("race");
	
	cin>>N;
	for(int i=0; i<=N; i++)
		cin>>pt[0][i].F>>pt[0][i].S;
	cin>>W;
	for(int i=0; i<=N; i++)
		pt[1][i] = {pt[0][i].F, pt[0][i].S + W};

	double ans = calc();
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

