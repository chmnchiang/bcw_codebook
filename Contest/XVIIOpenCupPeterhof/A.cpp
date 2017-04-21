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

int go(int x, int l, int r, int m) {
	map<int, int> mp;
	vector<int> ls;
	ls.PB(1);

	int y = x;
	int cur = 1;
	mp[y] = cur;
	ls.PB(y);

	while (1) {
		cur++;
		y = (y * x) % m;
		if (mp.count(y)) break;
		ls.PB(y);
		mp[y] = cur;
	}

	int len = r - l + 1;

	int in = mp[y];
	int cyc = cur - in;

	if (len >= 3) {

		int t = go(l, l+1, r, cyc);
		int g = (t - in) % cyc + in;
		return ls[g];

	} else {
		int t = l;
		if (len == 2) {
			for (int i=0; i<r-1; i++) {
				t *= l;
			}
		}
		if (t < in) {
			return ls[t];
		} else {
			int g = (t - in) % cyc + in;
			return ls[g];
		}
	}
}


int32_t main() {
	IOS;

	int A, B; cin >> A >> B;

	if (A == 1) {
		cout << 1 << endl;
		return 0;
	}

	if (A == B) {
		cout << A%10 << endl;
		return 0;
	}

	cout << go(A, A+1, B, 10) << endl;
	

	return 0;
}

