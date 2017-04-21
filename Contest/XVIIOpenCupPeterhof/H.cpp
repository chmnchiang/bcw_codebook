#pragma GCC optimize ("O2")
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

struct Poly {
	vector<double> v;
	Poly () { v.PB(0); }
	Poly (int sz) {
		v.resize(sz);
		REP(i,sz) v[i] = 0;
	}
	int size() const { return SZ(v); }
};

const int MAXN = 105;
double jie[MAXN];

Poly operator + (const Poly &a, const Poly &b) {
	int sz = max(a.size(), b.size());
	Poly res(sz);
	REP(i,sz) {
		res.v[i] = 0;
		if (i < a.size()) res.v[i] += a.v[i];
		if (i < b.size()) res.v[i] += b.v[i];
	}
	return res;
}
Poly operator - (const Poly &a, const Poly &b) {
	int sz = max(a.size(), b.size());
	Poly res(sz);
	REP(i,sz) {
		res.v[i] = 0;
		if (i < a.size()) res.v[i] += a.v[i];
		if (i < b.size()) res.v[i] -= b.v[i];
	}
	return res;
}
Poly operator * (const Poly &a, const Poly &b) {
	int sza = a.size();
	int szb = b.size();
	Poly res(sza+szb-1);
	REP(i,sza) REP(j,szb)
		res.v[i+j] += a.v[i] * b.v[j];
	return res;
}
Poly integral(const Poly &a) {
	int sz = a.size();
	Poly res(sz + 1);
	
	REP(i,sz) {
		res.v[i+1] = a.v[i] / (i+1.);
	}

	return res;
}
double eval(const Poly &a, double x)
{
	double ans = 0;
	double cur = 1;
	for(auto c: a.v)
	{
		ans += cur * c;
		cur *= x;
	}
	return ans;
}

int N, L;
int lb[MAXN], rb[MAXN];
int lid[MAXN], rid[MAXN];
vector<int> lx;
Poly P1, P0, PX;
Poly pref[MAXN], suff[MAXN];
Poly pol[MAXN];

void pre() {
	jie[0] = 1;
	REP1(i,1,MAXN-1) jie[i] = jie[i-1] * i;
	P1.v[0] = 1;
	PX = Poly(2);
	PX.v[1] = 1;
}

double calc()
{
	lx.clear();
	for(int i=0; i<N; i++)
	{
		lx.PB(lb[i]);
		lx.PB(rb[i]);
	}
	sort(ALL(lx));
	L = unique(ALL(lx)) - lx.begin();
	lx.resize(L);

	for(int i=0; i<N; i++)
	{
		lid[i] = lower_bound(ALL(lx), lb[i]) - lx.begin();
		rid[i] = lower_bound(ALL(lx), rb[i]) - lx.begin();
	}

	double ans = 0;

	for(int i=0; i<N; i++)
	{
		double dl = 1. / (rb[i] - lb[i]);
		for(int d=lid[i]; d<rid[i]; d++)
		{
			int a = lx[d], b = lx[d+1];
			for(int j=0; j<N; j++)
			{
				if(j == i) continue;
				if(rb[j] <= a) pol[j] = P1;
				else if(lb[j] >= a+1) pol[j] = P0;
				else
				{
					double len = rb[j] - lb[j];
					pol[j] = Poly(2);
					pol[j].v[1] = 1. / len;
					pol[j].v[0] = (a-lb[j]) / len;
				}
			}
			pref[0] = P1;
			for(int j=0; j<N; j++)
			{
				if(j == i) pref[j+1] = pref[j];
				else pref[j+1] = pref[j] * pol[j];
			}
			suff[N] = P1;
			for(int j=N-1; j>=0; j--)
			{
				if(j == i) suff[j] = suff[j+1];
				else suff[j] = suff[j+1] * pol[j];
			}

			Poly pa = PX;
			pa.v[0] = a;
			for(int j=0; j<N; j++)
			{
				if(j == i) continue;
				Poly p = pref[j] * suff[j+1] * (P1 - pol[j]) * pa;
				p = integral(p);
				double val = (eval(p, b-a) - eval(p, 0));
				//cout<<i<<" / "<<a<<"~"<<a+1<<" J "<<j<<" : "<<val<<endl;
				ans += val * dl;
			}
		}
	}

	return ans;
}

int main() {
	IOS;
	pre();
	cin>>N;
	for(int i=0; i<N; i++)
		cin>>lb[i]>>rb[i];

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}

