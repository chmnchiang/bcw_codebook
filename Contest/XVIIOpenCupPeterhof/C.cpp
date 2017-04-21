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

int N;
using Arr = array<int, 5>;

Arr operator * (const Arr &a, const Arr &b) {
	Arr r;
	for (int i=0; i<5; i++) {
		r[i] = b[a[i]];
	}
	return r;
}

const Arr X = {1, 0, 3, 2, 4};
const Arr Y = {2, 1, 4, 3, 0};

map<Arr, vector<int>> mp;

int main() {
	IOS;
	cin >> N;

	for (int i=0; i<N; i++) {
		string s; cin >> s;
		Arr r = {0, 1, 2, 3, 4};
		for (auto c: s) {
			if (c == '0') {
				r = r * X;
			} else {
				r = r * Y;
			}
		}

		mp[r].PB(i+1);
	}

	vector<vector<int>> ans;
	for (auto p: mp) {
		ans.PB(p.S);
	}
	sort(ALL(ans));

	cout << SZ(ans) << endl;
	for (auto it: ans) {
		cout << SZ(it);
		for (auto x: it) {
			cout << ' ' << x;
		}
		cout << endl;
	}

	return 0;
}

