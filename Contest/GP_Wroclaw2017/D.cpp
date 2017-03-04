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


#define int long long

const int MD = 1000000007;

map<int, int> _f, _g;

int f(int x) {
	if (!x) return 0;
	if (_f.count(x)) return _f[x];

	if (x % 2) _f[x] = (f(x/2)*2 + x) % MD;
	else {
		int z = x-1;
		_f[x] = (f(z/2) + f(z - z/2) + x) % MD;
	}
	return _f[x];
}

int g(int x) {
	if (!x) return 0;
	if (_g.count(x)) return _g[x];
	int n = x/2;
	if (x%2) {
		return (g(x-1) + f(x)) % MD;
	}

	int ans;
	if (x%2) {
		ans = ((x+1)/2) % MD * (x % MD) % MD;
	} else {
		ans = (x/2) % MD * ((x+1) % MD) % MD;
	}

	ans += 4 * g(n-1) + f(n);
	ans %= MD;

	return _g[x] = ans;
}

int32_t main() {
	IOS;

	int T; cin >> T;
	while (T--) {
		int a, b; cin >> a >> b;
		cout << (g(b) - g(a-1) + MD) % MD << endl;
	}

	return 0;
}

