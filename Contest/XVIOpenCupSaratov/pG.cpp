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
#define REP(i,n) for (int i=0;i<(n);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

#define int long long

const int MX = 30;
int sl[MX], sr[MX];

int32_t main() {

	int L, R;
	cin >> L >> R;
	R++;

	int x = L;
	for (int i=18; i>=0; i--) {
		sl[i] = x%10;
		x /= 10;
	}

	x = R;
	for (int i=18; i>=0; i--) {
		sr[i] = x%10;
		x /= 10;
	}

	int ans = 0, res = -1;

	auto check = [&](int z) {
		int y = z;
		int r = 1;
		while (z) {
			r *= (z%10);
			z /= 10;
		}
		if (r > res) {
			res = r;
			ans = y;
		}
	};

	for (int i=0; i<=18; i++) {
		if (sr[i] == 0) continue;
		int t = 0;
		for (int j=0; j<=18; j++) {
			int c = sr[j];
			if (i == j) c--;
			else if (j > i) c = 9;
			t *= 10;
			t += c;
		}
		if (t >= L) {
			check(t);
		}
	}
	cout << ans << endl;

    return 0;
}
