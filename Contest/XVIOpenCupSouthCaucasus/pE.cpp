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

const int MAXN = 50505;
const ld INF = 1E20;

int N;
ld P;
ld lP, l1mP;

ld lfact[MAXN];
ld lval[MAXN];
double cans[MAXN], ans[MAXN];

ld lcomb(int n, int m)
{
	if(n < 0 || m < 0 || m > n) return -INF;
	return lfact[n] - lfact[n-m] - lfact[m];
}

void pre()
{
	lfact[0] = 0;
	for(int i=1; i<MAXN; i++)
		lfact[i] = lfact[i-1] + log(i);
	lval[0] = -INF;
	for(int i=1; i<MAXN; i++)
		lval[i] = log(i);
}

void calc()
{
	if(P == 0 || P == 1)
	{
		for(int i=1; i<=N; i++)
			cans[i] = P * i;
		return;
	}
	lP = log(P);
	l1mP = log(1-P);
	for(int i=1; i<=N; i++)
	{
		cans[i] = 0;
		int E = i / P;
		int K = sqrt(i * (1-P)) / P * 8 + 10;
		if(i <= 100) K += N;
		ld err = 0;
		ld cur = 0;
		int bst = -1;
		int lb = N+1, rb = -1;
		int lll = max(E-K, i);
		int rrr = min(E+K, N);
//		cout<<i<<" : "<<lll<<"~"<<rrr<<endl;
		double v;
		bool any = false;
		double omp = 1-P;
		for(int j=lll; j<=rrr; j++)
		//for(int j=i; j<=N; j++)
		{
			//if(j < i || j > N) continue;
			if(!any)
			{	
				v = exp(lcomb(j-1, i-1) + i * lP + (j-i) * l1mP) * j;
				any = true;
			}
			else
			{
				v *= j * omp / (j-i);
			}
			cans[i] += v;
			/*if(j < E-K || j > E+K)
				err += v;
			if(v > cur)
			{
				cur = v;
				bst = j;
			}
			if(v > 5e-7)
			{
				lb = min(lb, j);
				rb = max(rb, j);
			}*/
		}
		//if(i%100!=-1)cout<<i<<" E "<<E<<" K "<<K<<" ["<<lll<<","<<rrr<<"] "<<bst<<" : "<<cur<<" ("<<lb<<"~"<<rb<<") "<<err<<endl;
		//assert(err < 5E-7);
//		cout<<cans[i]<<endl;
	}
}

int main() {
	IOS;

	pre();
	cin>>N>>P;

	P = 1 - P;
	calc();
	for(int i=1; i<=N; i++)
		ans[i] = cans[i];
	P = 1 - P;
	calc();
	for(int i=1; i<=N; i++)
		ans[i] += cans[N-i+1];

	//exit(0);
	cout<<fixed<<setprecision(12);
	//for(int i=1; i<=N; i++)
	//	cout<<ans[i]<<"\n";

	ld z = 0; for(int i=1; i<=N; i++) z += ans[i]; cout<<z<<endl;

	for(int i=1; i<=N; i++)
		assert(!std::isnan(ans[i]));

	return 0;
}
