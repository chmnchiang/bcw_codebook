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
const int SQM = 100000;

bool isp[SQM];
vector<int> prime;

void pre() {
	fill(isp, isp+SQM, true);
	isp[0] = isp[1] = 0;
	for (int i=2; i<SQM; i++) {
		if (isp[i]) {
			prime.PB(i);
			for (int j=i+i; j<SQM; j+=i) {
				isp[j] = false;
			}
		}
	}
}

//typedef pair<int, int> pii;
typedef map<int, int> mii;
const int MOD = 1000000009;

mii fact(int x) {
	mii res;
	for (auto p: prime) {
		int t = 0;
		while (x % p == 0) {
			x /= p;
			t++;
		}
		if (t) {
			res[p] = t;
		}
		if (not x) break;
	}
	if (x != 1) res[x] = 1;
	return res;
}

int fp(int a, int b) {
	if (b == 0) return 1;
	return (b&1) ? (fp(a*a%MOD, b/2)*a) % MOD : fp(a*a%MOD, b/2);
}

int32_t main() {
	IOS;
	pre();

	int K, D, M;
	cin >> K >> D >> M;

	auto vd = fact(D);
	auto vm = fact(M);

	for (auto x: vd) {
		if (vd[x.F] > vm[x.F]) {
			cout << 0 << endl;
			return 0;
		}
	}

	vector<int> fac;
	for (auto x: vm) {
		fac.PB(x.F);
	}

	/*
	for (auto x: vm) {
		cout << x << endl;
	}

	for (auto x: vd) {
		cout << x << endl;
	}*/

	int n = SZ(vm);
	int s = SZ(vm) * 2;
	int t = (1<<s);
	int ans = 0;
	for (int i=0; i<t; i++) {
		int a = i;
		long long temp = 1;

		for (int j=0; j<n; j++) {
			int t1 = (1<<(j*2));
			int t2 = (1<<(j*2+1));
			int f = fac[j];

			int m = vm[f] - vd[f] + 1;
			if (t1 & a) m--;
			if (t2 & a) m--;
			m = max(m, 0LL);
			if (m == 0) temp = 0;
			else {
				temp *= fp(m, K);
				temp %= MOD;
			}
		}
		int b = __builtin_popcount(a) % 2;
//		cout << temp << endl;
		if (b) {
			ans += (MOD - temp);
			ans %= MOD;
		} else {
			ans += temp;
			ans %= MOD;
		}
	}

	cout << ans << endl;

	return 0;
}

