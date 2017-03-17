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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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
int PRE;
using pii = pair<int, int>;
vector<pii> events;
vector<pii> qry;
const int MX = 333333;
int ans[MX];

int32_t main() {
	FILEIO("expect");
	IOS;

	int N, Q;
	cin >> N >> Q;
	int cur = 0;
	int positive = 0;
	for (int i=0; i<N; i++) {
		string s; cin >> s;
		int t, k; cin >> t >> k;
		int nx = cur;
		if (s == "-") nx -= k;
		else nx += k, positive += k;
		
		int f = (s == "-" ? -1 : 1);

		int l = max(min(-nx, -cur), 0LL), r = max(max(-nx, -cur), 0LL);
		PRE += (r - l) * t * (f);

		events.PB({l, -t*f});
		events.PB({r, t*f});

		cur = nx;
	}

	sort(ALL(events));


	qry.resize(Q);
	for (int i=0; i<Q; i++) {
		cin >> qry[i].F;
		qry[i].S = i;
	}

	sort(ALL(qry));

	int nt = 0;
	int eid = 0;
	int diff = 0;

	for (auto p: qry) {
		int qt = p.F;
		while (eid < SZ(events) && events[eid].F <= qt) {
			int xt = events[eid].F;
			PRE += diff * (xt - nt);
			nt = xt;
			diff += events[eid].S;
			eid++;
		}

		PRE += diff * (qt - nt);
		nt = qt;
		if (cur + qt < 0) {
			ans[p.S] = -1;
		} else ans[p.S] = PRE;
	}

#define endl "\n"
	for (int i=0; i<Q; i++) {
		if (ans[i] == -1) cout << "INFINITY" << endl;
		else cout << ans[i] << endl;
	}


	return 0;
}

