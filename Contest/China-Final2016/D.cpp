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
const int MX = 3e18;

int N, K;
vector<int> ip;
vector<int> tp;

bool test(int x) {
	tp.resize(x);
	fill(ALL(tp), 0);

	int id = 0;
	for (int k=0; k<K; k++) {
		for (int i=0; i<x; i++) {
			while (id < N and ip[id]/2 < tp[i]) id++;

			if (id == N) return false;

			tp[i] = ip[id++];
		}
	}
	return true;
}

int32_t main() {
	IOS;

	int T;
	cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cin >> N >> K;
		ip.resize(N);
		for (int i=0; i<N; i++) cin >> ip[i];
		
		sort(ALL(ip));

		int l = 0, r = N;

		while (l < r) {
			int md = (l+r+1)/2;
			if (test(md)) {
				l = md;
			} else {
				r = md-1;
			}
		}
		cout << "Case #" << cas << ": " << l << endl;
	}

	return 0;
}

