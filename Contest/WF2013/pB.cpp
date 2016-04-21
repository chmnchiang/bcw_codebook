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

const int MAXN = 1000;
const int INF = 1e9;
const int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

double X, P, R;

double eval(int l, int r)
{
	if(l >= 0 || r <= 0) return -INF;
	double vl = l * (1-X), vr = r;
	return vl + (vr-vl) * (1-pow(R, -l)) / (1 - pow(R, r-l));
}

double calc()
{
	if(P == 0 || X == 0) return 0;

	R = (1-P) / P;

	int bi = -2, bj = 2;
	double ans = -INF;

	for(int i=1; i<MAXN; i++)
	{
		for(int j=1; j<MAXN; j++)
		{
			double nval = eval(-i, j);
			if(nval > ans)
			{
				bi = -i;
				bj = j;
				ans = nval;
			}
		}
	}

	while(1)
	{
		bool any = false;
		for(int i=0; i<8; i++)
		{
			int ni = bi + dx[i], nj = bj + dy[i];
			double nval = eval(ni, nj);
			if(nval > ans)
			{
				ans = nval;
				bi = ni;
				bj = nj;
				any = true;
			}
		}
		if(!any) break;
	}

//	cout<<bi<<" ~ "<<bj<<endl;

	return max(ans, 0.);
}

int main() {
	IOS;
	cin>>X>>P;
	X /= 100;
	P /= 100;

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}

