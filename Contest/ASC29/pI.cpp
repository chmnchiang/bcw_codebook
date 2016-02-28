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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

#define int long long

int32_t main() {
	IOS;
	FILEIO("video");

	int D, B, T, P;
	cin >> D >> B >> T >> P;

	int SS = D * P;

	auto ans = [&](int s) {
		return (T*(B-D)+s-1)/s;
	};

	int a = ans(SS);
	int l = 1, r = SS;

	while (l < r) {
		int md = (l+r)/2;

		if (ans(md) == a) {
			r = md;
		} else {
			l = md+1;
		}
	}

	cout << l << endl;

	return 0;
}
