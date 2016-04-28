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
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}

const int MAXN = 105;
const int INF = 1029384756;

int N;
pll pt[MAXN];
ll M, X, MX, L, R;

pll calc()
{
	ll lb = 0, rb = INF;

	for(int i=0; i<N; i++)
	{
		pll p1 = pt[i], p2 = pt[(i+1)%N];
		ll m = cross(p1, p2);
		M += m;
		MX += m * (p1.F + p2.F);
	}

	if(M < 0)
	{
		M = -M;
		MX = -MX;
	}

	L = INF, R = -INF;
	for(int i=0; i<N; i++)
	{
		if(pt[i].S == 0)
		{
			L = min(L, pt[i].F);
			R = max(R, pt[i].F);
		}
	}
	X = pt[0].F;

	ll A = 6 * (L - X), B = MX - 3 * M * L;
	if(A == 0)
	{
		if(B < 0)
			rb = -1;
	}
	else if(A > 0)
		rb = min(rb, (B+A-1) / A);
	else
	{
		A = -A;
		B = -B;
		lb = max(lb, B / A);
	}

	A = 6 * (R - X), B = MX - 3 * M * R;
	if(A == 0)
	{
		if(B > 0)
			rb = -1;
	}
	else if(A > 0)
		lb = max(lb, B / A);
	else
	{
		A = -A;
		B = -B;
		rb = min(rb, (B+A-1) / A);
	}

	return {lb, rb};
}

int main() {
	IOS;
	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	pll res = calc();

	if(res.F > res.S)
		cout<<"unstable"<<endl;
	else if(res.S == INF)
		cout<<res.F<<" .. inf"<<endl;
	else
		cout<<res.F<<" .. "<<res.S<<endl;

	return 0;
}

