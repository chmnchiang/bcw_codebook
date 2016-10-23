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

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
pll operator*(ll a, pll b){return {a*b.F, a*b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
double abs(pll a){return sqrt(dot(a, a));}

const int MAXN = 401010;

int N, M;
pll pt[MAXN];
vector<ll> vdis[MAXN];

vector<pll> vpt;
vector<bool> ins;

double calc()
{
	vpt.clear();
	ins.clear();
	double ans = 0;

	for(int i=0; i<N; i++)
	{
		if(vdis[i].empty() or vdis[i][0] != 0)
		{
			vpt.PB(pt[i]);
			ins.PB(false);
		}

		pll d = pt[(i+1)%N] - pt[i];
		if(d.F != 0) d.F /= abs(d.F);
		if(d.S != 0) d.S /= abs(d.S);

		for(auto x: vdis[i])
		{
			vpt.PB(pt[i] + x * d);
			ins.PB(true);
		}
	}

	int sz = SZ(vpt);
	vector<pll> stk;
	stk.PB(vpt[0]);

	double len = 0;
	for(int i=sz-1; i>=1; i--)
	{
		pll kk = vpt[i];
		while(SZ(stk) >= 2)
		{
			pll ii = stk[SZ(stk)-2], jj = stk.back();
			if(cross(jj-ii, kk-jj) <= 0)
			{
				len -= abs(jj-ii);
				stk.pop_back();
			}
			else break;
		}
		len += abs(kk-stk.back());
		stk.PB(kk);

		if(ins[i]) ans += len;
	}


	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N;
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		for(int i=0; i<N; i++)
			vdis[i].clear();

		cin>>M;
		for(int i=0; i<M; i++)
		{
			int k, d;
			cin>>k>>d;
			vdis[k].PB(d);
		}

		for(int i=0; i<N; i++)
			sort(ALL(vdis[i]));

		double ans = calc();
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}

    return 0;
}


