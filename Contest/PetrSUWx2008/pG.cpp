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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

typedef long double ld;

ld calc(ld L)
{
	ld ans = 1e20;
	for(int i=1; i<=60; i++)
	{
		ans = min(ans, i * powl(L, 1.l / i));
	}
	return ans;
}

int main() {
	IOS;
	FILEIO("princess");

	ld L;
	cin>>L;
	ld ans = calc(L);
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

