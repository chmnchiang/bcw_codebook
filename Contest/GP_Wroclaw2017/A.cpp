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


double pt[4][3];

int main() {
	IOS;
	int T;
	cin>>T;
	REP(t,T) {
		for(int i=0; i<4; i++)
			for(int j=0; j<3; j++)
				cin>>pt[i][j];

		for(int i=0; i<3; i++)
			for(int j=0; j<3; j++)
				pt[i][j] -= pt[3][j];

		double ans = pt[0][0] * (pt[1][1] * pt[2][2] - pt[1][2] * pt[2][1]);
		ans += pt[0][1] * (pt[1][2] * pt[2][0] - pt[1][0] * pt[2][2]);
		ans += pt[0][2] * (pt[1][0] * pt[2][1] - pt[1][1] * pt[2][0]);

		ans = abs(ans) / 6.;
		cout<<fixed<<setprecision(10)<<ans<<endl;
	}

	return 0;
}

