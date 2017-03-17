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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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


const int MAXN = 1010101;

int N;
double w[MAXN], s[MAXN];
string st;

double calc()
{
	double ret = 0;

	w[0] = s[0] = 0;
	for(int i=1; i<=N; i++)
	{
		w[i] = w[i-1] + (st[i-1] == 'W');
		s[i] = s[i-1] + w[i];
		double p = (i==N ? 1. : 1. / (i+1));
		double E = 0;
		if(st[i-1] == 'C')
			E = w[i] - s[i-1] / i;
		else
			E = (i+1) / 2. - w[i] + s[i-1] / i;
		
		ret += E * p;
	}

	return ret;
}

int main() {
	FILEIO("foreign");
	IOS;

	while(cin>>st)
	{
		N = SZ(st);
		reverse(ALL(st));
		
		double ans = calc();
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}

	return 0;
}

