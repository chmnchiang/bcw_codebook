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

const int MN = 10;
const int MM = 70;

int N, M;
typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii>> pq[MN];
int sz[MM];
typedef array<int, 3> Pack;
vector<Pack> pack;

int calc(vector<int> per) {
	for (int i=0; i<=N; i++) {
		pq[i] = priority_queue<pii, vector<pii>, greater<pii>>();
	}

	int i = 0;
	int r = 0;

	int nsz = 0;
	auto check = [&]() -> bool {
		if (i == N) return false;
		int np = per[i];

		if (not pq[np].size()) return false;
		auto p = pq[np].top();
		if (p.F == r) {
			r = p.S;
			if (r == sz[np]) {
				r = 0;
				i++;
			}
			nsz -= p.S - p.F;
			pq[np].pop();

			return true;
		}

		return false;
	};

	int ans = 0;
	//cout << per << endl;
	for (auto p: pack) {
		
		bool use = false;

		pq[p[0]].push({p[1], p[2]});
		nsz += p[2] - p[1];
		
		while (check()) {
			use = true;
		}

		ans = max(ans, nsz);

	//	cout << i << ' ' << r << endl;
	}
//	cout << ans << endl;
	return ans;
}

int solve() {


	for (int i=1; i<=N; i++) cin >> sz[i];
	pack.clear();
	for (int i=0; i<M; i++) {
		int a, b, c; cin >> a >> b >> c;
		b--;
		pack.PB({a, b, c});
	}
	vector<int> p(N);
	for (int i=0; i<N; i++) p[i] = i+1;


	int ans = 1029384756;
	do {
		ans = min(ans, calc(p));
	} while (next_permutation(ALL(p)));
	return ans;
}

int main() {
    IOS;

	int cas = 0;
	while (true) {
		cin >> N >> M;
		if (not N and not M) return 0;

		int ans = solve();
		cas++;
		cout << "Case " << cas << ": " << ans << endl; 
		cout << endl;
	}

    return 0;
}

