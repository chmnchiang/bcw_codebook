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


const int MAXN = 1010;

int W, H, N;
double M, A, xp, xm, C;

double x[MAXN];

void calc()
{
	for(int i=0; i<=N+1; i++)
	{
		x[i] = W * i / (double)(N+1);
	}
	
	M = (double)H / W;
	A = (1. - M * M) / 2.;

	xp = (1. + sqrt(1. - 4. * A * A)) / (2. * A);
	xm = (1. - sqrt(1. - 4. * A * A)) / (2. * A);

	C = W / (pow(xp, N+1) - pow(xm, N+1));

	for(int i=0; i<=N+1; i++)
		x[i] = C * (pow(xp, i) - pow(xm, i));

	double ans = 0;
	for(int i=0; i<=N; i++)
	{
		double dx = x[i+1] - x[i];
		ans += (1. + 2 * M - M * M) / 4. * dx * dx + M * x[i] * dx + M * M * x[i+1] * x[i+1] / 2.;
	}

	cout<<fixed<<setprecision(10);
	cout<<ans<<endl;
	for(int i=1; i<=N and i<=10; i++) cout<<x[i]<<endl;
}

int main() {
	IOS;

	cin>>W>>H>>N;
	calc();

	return 0;
}

