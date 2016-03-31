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
using pii=pair<int, int>;
vector<pii> ip;
const int INF = 102934847;
const double EPS = 1e-8;

bool test(double t, const vector<int> &per) {
	vector<pii> op(N);
	for (int i=0; i<N; i++) {
		op[i] = ip[per[i]];
	}

	double nt = 0;
	for (int i=0; i<N; i++) {
		nt = max(nt, (double)op[i].F);
		if (nt > op[i].S) return 0;
		nt += t;
	}
	return 1;
}
double calc(const vector<int> &per) {
	double l = 0, r = 1e5;
	for (int i=0; i<50; i++) {
		double md=(l+r)/2;
		if (test(md, per)) {
			l=md;
		} else r=md;
	}
	return l;
}

int main() {
	IOS;
	int cas=0;
	while (true) {
		cin >> N;
		if (not N) break;

		ip.resize(N);
		for (int i=0; i<N; i++) {
			int s, t; cin >> s >> t;
			ip[i] = {s, t};
		}

		vector<int> per(N);
		for (int i=0; i<N; i++) {
			per[i] = i;
		}

		double ans = 0;
		do {
			ans = max(calc(per), ans);
//			cout << per << ' ' << calc(per) << endl;
		} while (next_permutation(ALL(per)));

		ans += EPS;
		int min = floor(ans);
		ans -= min;
		ans *= 60;
		int sec = round(ans);

		cas++;
		cout << "Case " << cas << ": " << min << ":" << (sec<10 ? "0" : "") << sec << endl;
	}

	return 0;
}


