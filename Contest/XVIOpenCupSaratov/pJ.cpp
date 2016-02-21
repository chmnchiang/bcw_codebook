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

int N, M;
vector<int> soc, dev;


bool check(int k) {
	if (not k) return true;
	vector<int> use(k);
	for (int i=0; i<k; i++) {
		use[k-i-1] = dev[i];
	}

	int uid = 0, sid = 0;
	int t = 1;
	int level = 0;
	while (uid < k) {
		int safe = use[uid];
		if (safe < level) return false;
		else if (safe == level) {
			if (not t) return false;
			t --;
			uid ++;
		} else {
			int left = k - uid;
			int nx = min(sid + t, N);
			for (int i=sid; i<nx; i++) {
				t += soc[i] - 1;
			}
			sid = nx;
			level ++;
			if (t >= left) return true;
		}
	}

	return true;
}

int32_t main() {
	IOS;

	cin >> N >> M;
	soc.resize(N);
	dev.resize(M);

	for (int i=0; i<N; i++) {
		cin >> soc[i];
	}
	for (int i=0; i<M; i++)
		cin >> dev[i];

	sort(ALL(soc), greater<int>());
	sort(ALL(dev), greater<int>());

	int l = 0, r = M;
	while (l < r) {
		int md = (l+r+1)/2;
		if (check(md)) {
			l = md;
		} else {
			r = md-1;
		}
	}
	cout << l << endl;

    return 0;
}
