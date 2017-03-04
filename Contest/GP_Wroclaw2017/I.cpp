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


const int MAXN = 101010;

int N, L;
double X, Y;
double y[MAXN], v[MAXN];

double eval(double s)
{
	double res = 0;

	for(int i=0; i<=L; i++)
	{
		double h = min(Y, y[i+1]) - y[i];
		double si = s * v[i];
		res += h * si / sqrt(1 - si * si);
	}

	return res;
}

double calc()
{
	L = 0;
	for(int i=1; i<=N; i++)
	{
		if(Y > y[i] + 1E-10) L = i;
		else break;
	}
	double mx = 0;
	for(int i=0; i<=L; i++)
		mx = max(mx, v[i]);

	double lb = 0, rb = 1. / mx;

	for(int i=0; i<60; i++)
	{
		double mb = (lb + rb) / 2;
		double val = eval(mb);
		if(val > X) rb = mb;
		else lb = mb;
	}

	double s = (lb + rb) / 2;
	double ans = 0;

	for(int i=0; i<=L; i++)
	{
		double h = min(Y, y[i+1]) - y[i];
		double si = s * v[i];
		ans += h / sqrt(1 - si * si) / v[i];
	}

	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>X>>Y;
		y[0] = 0;
		for(int i=1; i<=N; i++)
			cin>>y[i];
		y[N+1] = 1E20;
		for(int i=0; i<=N; i++)
			cin>>v[i];

		double ans = calc();
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}

	return 0;
}

