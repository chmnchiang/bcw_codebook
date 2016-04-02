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
typedef pair<ll, ll> pll;

const int MAXN = 1010;
const ll RL = 10007;
const double INF = 1E20;

pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
double abs(pll a){return sqrt(dot(a, a));}

int N, K;
pll pt[MAXN], qt[MAXN];
double lenu[MAXN][MAXN], lend[MAXN][MAXN];
double dpu[MAXN][MAXN], dpd[MAXN][MAXN];

double calc()
{
	for(int i=0; i<N; i++)
		pt[i] = {pt[i].F*RL+pt[i].S, -pt[i].F+pt[i].S*RL};
	for(int i=0; i<K; i++)
		qt[i] = {qt[i].F*RL+qt[i].S, -qt[i].F+qt[i].S*RL};

	sort(pt, pt+N);
	sort(qt, qt+K);

	for(int i=0; i<N; i++)
	{
		for(int j=i; j<N; j++)
		{
			lenu[i][j] = lend[i][j] = abs(pt[j] - pt[i]);
			for(int k=0; k<K; k++)
			{
				if(qt[k].F >= pt[i].F && qt[k].F <= pt[j].F)
				{
					pll dif = pt[j] - pt[i];
					if(i == j)
						dif = {1, 0};
					ll crs = cross(dif, qt[k]-pt[i]);
					if(crs > 0)
						lenu[i][j] = INF;
					if(crs < 0)
						lend[i][j] = INF;
				}
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
			dpu[i][j] = dpd[i][j] = INF;
		dpu[i][i] = lenu[i][i];
		dpd[i][i] = lend[i][i];
	}

	for(int i=0; i<N; i++)
	{
		for(int j=i; j<N; j++)
		{
			for(int k=j+1; k<N; k++)
			{
				dpu[i][k] = min(dpu[i][k], dpu[i][j] + lenu[j][k]);
				dpd[i][k] = min(dpd[i][k], dpd[i][j] + lend[j][k]);
			}
		}
	}

	double ans = INF;

	for(int i=0; i<N; i++)
	{
		for(int j=i; j<N; j++)
		{
			if(pt[i].F <= qt[0].F && pt[j].F >= qt[K-1].F)
				ans = min(ans, dpu[i][j] + dpd[i][j]);
		}
	}

	return ans;
}

int main() {
	IOS;
	FILEIO("mines");

	cin>>N>>K;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;
	for(int i=0; i<K; i++)
		cin>>qt[i].F>>qt[i].S;

	double ans = calc();
	if(ans >= INF/2)
		cout<<-1<<endl;
	else
	{
		double real_ans = ans / sqrt(RL*RL+1);
		cout<<fixed<<setprecision(12)<<real_ans<<endl;
	}

	return 0;
}

