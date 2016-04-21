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

const int MAXN = 3030;

int N;
int c[MAXN][MAXN];
double a[MAXN][MAXN];
double y[MAXN], yp[MAXN];
double x[MAXN], xp[MAXN];
double tmp[MAXN];

void calc()
{
	for(int i=0; i<N; i++)
	{
		x[i] = y[i];
		for(int j=0; j<N; j++)
			x[i] += c[i][j];
	}
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			a[i][j] = c[i][j] / x[j];

	for(int z=0; z<20; z++)
	{
		for(int i=0; i<N; i++)
		{
			tmp[i] = yp[i];
			for(int j=0; j<N; j++)
				tmp[i] += a[i][j] * xp[j];
		}
		for(int i=0; i<N; i++)
			xp[i] = tmp[i];
	}
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			scanf("%d", &c[i][j]);
	for(int i=0; i<N; i++)
		scanf("%lf", &y[i]);
	for(int i=0; i<N; i++)
		scanf("%lf", &yp[i]);

	calc();

	for(int i=0; i<N; i++)
		printf("%.12f%c", xp[i], i==N-1 ? '\n' : ' ');

	return 0;
}
