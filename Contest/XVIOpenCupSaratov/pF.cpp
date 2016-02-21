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
#define endl "\n"
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

typedef pair<int, int> pii;

pii gcd(int a, int b){
	if(b == 0) return make_pair(1, 0);
	else{
		int p = a / b;
		pii q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}

inline int norm(int a, int m) {
	return ((a%m)+m)%m;
}

const int MX = 20;
int N, A; 
int W[MX];
int ID[MX];
int G[MX];

namespace Sim {
	int cur[MX];
	vector<array<int, 3>> ans;
	
	void init() {
		FZ(cur);
	}

	void one(int a) {
		ans.PB({1, ID[a]+1, 0});
	}
	void two(int a) {
		ans.PB({2, ID[a]+1, 0});
	}
	void three(int a, int b) {
		ans.PB({3, ID[a]+1, ID[b]+1});
	}

	void preform(int a) {
		assert(not cur[a]);
		one(a);
		int t = W[N-1] - cur[N-1];
		if (t >= W[a]) {
			three(a, N-1);
			cur[N-1] += W[a];
		} else {
			three(a, N-1);
			two(N-1);
			three(a, N-1);
			cur[N-1] += W[a];
			cur[N-1] -= W[N-1];
		}
	}

	void output() {
		assert(ans.size() <= 1000000);
		cout << ans.size() << endl;
		for (auto p: ans) {
			cout << p[0];
			if (p[0] != 3) {
				cout << ' ' << p[1] << endl;
			} else cout << ' ' << p[1] << ' ' << p[2] << endl;
		}
	}
}

int32_t main() {
	IOS;

	cin >> N >> A;

	for (int i=0; i<N; i++) {
		cin >> W[i];
		ID[i] = i;
	}

	int mid = max_element(W, W+N) - W;
	swap(W[mid], W[N-1]);
	swap(ID[mid], ID[N-1]);

	int g = 0;
	for (int i=0; i<N; i++) {
		g = __gcd(g, W[i]);
		G[i+1] = g;
	}

	static int ans[MX];

	if (A % g or (A > W[N-1])) {
		cout << -1 << endl;
		return 0;
	}

	if (N == 1) {
		if (A == W[0]) {
			cout << "1" << endl;
			cout << "1 1" << endl;
		} else cout << -1 << endl;
		return 0;
	}

	if (W[N-1] == A) {
		cout << "1" << endl;
		cout << "1 " << ID[N-1]+1 << endl;
		return 0;
	}

	static int WW[MX];
	for (int i=0; i<N; i++) {
		WW[i] = W[i] / g;
	}
	int AA = A / g;

	int w = WW[N-1];
#define _n(x) norm((x), w)
	int ls = AA;
	for (int i=N-1; i>=0; i--) {
		if (i == 0) {
			ans[i] = _n(ls);
			continue;
		}
		auto p = gcd(WW[i], G[i]/g);
		int ll = ls;
		int t = _n(p.F*ll);
		ans[i] = t;
		ls = _n(p.S*ll);
	}

	//int t = 0;
	//for (int i=0; i<N; i++) {
	//	t += W[i] * ans[i];
	//	t %= W[N-1];
	//	cout << ans[i] << ' ';
	//}
	//cout << endl;
	//assert(t % W[N-1] == A % W[N-1]);

	Sim::init();
	for (int i=0; i<N-1; i++) {
		for (int j=0; j<ans[i]; j++) {
			Sim::preform(i);
		}
	}
	Sim::output();

    return 0;
}
