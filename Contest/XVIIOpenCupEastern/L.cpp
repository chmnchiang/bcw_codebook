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

int fib[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55};

int main() {
	IOS;

	int a, b, c;
	while(cin>>a>>b>>c)
	{
		int mx = max(max(a, b), c);
		if(mx > 10)
		{
			int dif = mx - 10;
			a -= dif;
			b -= dif;
			c -= dif;
		}

		int A = fib[a], B = fib[b], C = fib[c];
		int d = B * B - 4 * A * C;

		int ans = 0;
		if(d < 0) ans = 0;
		else if(d == 0) ans = 1;
		else ans = 2;

		if(A == 0) ans = 1;

		cout<<ans<<endl;
	}

	return 0;
}

