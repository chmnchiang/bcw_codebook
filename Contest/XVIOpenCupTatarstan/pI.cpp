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
multiset<int> st[16];


inline int get_num(int i, const vector<int> &vec) {
	int res = 0;
	REP(j,4) {
		if (i & (1<<j)) res += vec[j];
		else res -= vec[j];
	}
	return res;
}
int main() {
	IOS;
	cin >> N;
	REP(_,N) {
		int t;
		vector<int> vec;
		cin >> t;
		REP(i,4) {
			int v;
			cin >> v;
			vec.PB(v);
		}
//		cout << t << " " << vec << endl;
		if (t == 1) {
			REP(i,16) {
				st[i].insert(get_num(i,vec));
			}
		} else if (t == 2) {
			REP(i,16) {
				st[i].erase(st[i].find(get_num(i,vec)));
			}
		} else {
			int res = 0;
			REP(i,16) {
				int x = get_num(i,vec);
				res = max(res, *st[i].rbegin() - x);
//				cout << "#" << i << ": " << x << " " << *st[i^0xF].begin() << endl;
			}
			cout << res << "\n";
		}
	}

	return 0;
}

