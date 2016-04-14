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

int N, M;
vector<int> ip[2];

bool calc() {
	int my = 0, he = 1;
	while (true) {
		vector<int> &mv = ip[my], &hv = ip[he];
		int mb = mv.back(), hb = hv.back();
		if (mb <= hb) {
			if (SZ(mv) == 1) {
				return he;
			}
			mv.pop_back();
			mv.back() += mb;
		} else {
			if (SZ(hv) == 1) return my;
			if (SZ(mv) == 1) {
				hv.pop_back();
				continue;
			}

			int mbb = mv[SZ(mv)-2], hbb = hv[SZ(hv)-2];
			if (mbb+mb > hbb+hb) {
				mv.pop_back();
				mv.back() += mb;
			} else {
				hv.pop_back();
			}
		}

		swap(my, he);
	}
}

int32_t main() {
	IOS;

	int cas=0;
	while (cin >> N >> M) {
		ip[0].clear();
		ip[1].clear();
		for (int i=0; i<N; i++) {
			int t; cin >> t;
			ip[0].PB(t);
		}
		for (int i=0; i<M; i++) {
			int t; cin >> t;
			ip[1].PB(t);
		}
		sort(ALL(ip[0]));
		sort(ALL(ip[1]));
		
		cas++;
		cout << "Case " << cas << ": " << (!calc() ? "Takeover Incorporated" : "Buyout Limited") << endl;
	}

	return 0;
}

