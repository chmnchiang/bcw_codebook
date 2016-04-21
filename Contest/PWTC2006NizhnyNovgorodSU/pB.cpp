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

int N,X;
set<int> st[2];

int main() {
	cin >> N >> X;
	REP(i,N) {
		int x,v;
		cin >> x >> v;
		st[v].insert(x);
	}
	st[0].insert(0);

	int ans = 0;
	int f = 0;
	while (true) {
		if (f == 0) {
			auto it = st[0].upper_bound(X);
			assert(it != begin(st[0]));
			it--;
			X = *it;
			if (*it == 0) {
				ans++;
			} else {
				st[0].erase(it);
			}
		} else {
			auto it = st[1].upper_bound(X);
			if (it == end(st[1])) break;
			X = *it;
			st[1].erase(it);
		}
		f ^= 1;
	}
	if (SZ(st[1]) || SZ(st[0]) != 1) {
		ans = -1;
	}
	cout << ans << endl;

	return 0;
}
