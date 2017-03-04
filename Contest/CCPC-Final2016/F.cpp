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
using pii = pair<int, int>;

bool isp[50];
vector<int> primes;

static void init() {
	for (int i=2; i<=40; i++) {
		isp[i] = 1;
		for (int j=2; j<i; j++) {
			if (i%j == 0) isp[i] = 0;
		}
		if (isp[i]) primes.PB(i);
	}
}

int phi(int x) {
	int t = x;
	for (auto p: primes) {
		if (x % p == 0) {
			t /= p;
			t *= p-1;
		}
	}
	return t;
}

int fmul(int a, int b, int m) {
	int ret = 0;
	while (b) {
		if (b&1) (ret += a) %= m;
		(a += a) %= m;
		b /= 2;
	}
	return ret;
}


int fp(int a, int b, int m) {
	a %= m;
	if (!b) return 1%m;
	int ret = fp(a*a%m, b/2, m);
	if (b&1) ret = ret*a%m;
	return ret;
}

const pii BAD = {-1, -1};

struct TWODRMQ {
	static const int MXN = 205;
	static const int LOG = __lg(MXN)+1;
	int n,m;
	pii arr[MXN][MXN];
	pii ra[LOG][LOG][MXN][MXN];

	pii merge4(pii p1, pii p2, pii p3, pii p4) {
		return merge(merge(p1, p2), merge(p3, p4));
	}

	pii merge(pii p1, pii p2) {
		if (p1 == BAD or p2 == BAD) return BAD;
		if (p1.S > p2.S) swap(p1, p2);
		if (p2.S % p1.S == 0) {
			if (p1.F % p1.S != p2.F % p1.S) return BAD;
			else return {max(p1.F, p2.F), p2.S};
		}
		int a1, a2, b1, b2;
		tie(a1, b1) = p1;
		tie(a2, b2) = p2;

		int d = a1 - a2;
		int g = __gcd(b1, b2);
		if (d % g) return BAD;
		int bb2 = b2 / g, bb1 = b1 / g;
		d /= g;
		d %= bb1;

//		cout << d << ' ' << bb2 << ' ' << bb1 << endl;

		int ph = phi(bb1);
		int re = fp(bb2, ph-1, bb1);

		//cout << re << ' ' << bb2 << ' ' << bb1 << endl;
		assert(re * bb2 % bb1 == 1);

		int x = fmul(d, re, bb1);
		int a = x * b2 + a2;
		int b = bb2 * bb1 * g;
		int mm = max(a1, a2);
		int dd = mm - a;
		if (dd > 0) {
			a += dd / b * b;
		}

		while (a < mm) a += b;
		while (a - b >= mm) a -= b;

		//cout << pii(a, b) << endl;
		//assert(a % b1 == a1 % b1);
		//assert(a % b2 == a2 % b2);
		//assert(a >= a1 and a >= a2);


		return {a, b};
	}
	void init(int tn, int tm) {
		n = tn;
		m = tm;
		REP(i,LOG) REP(j,LOG) REP(x,n) REP(y,m) {
			if (x + (1<<i) > n or y + (1<<j) > m) continue;
			if (i == 0 and j == 0) {
				ra[i][j][x][y] = arr[x][y];
			} else if (i == 0) {
				ra[i][j][x][y] = merge(ra[i][j-1][x][y], ra[i][j-1][x][y+(1<<(j-1))]);
			} else {
				ra[i][j][x][y] = merge(ra[i-1][j][x][y], ra[i-1][j][x+(1<<(i-1))][y]);
			}
		}
//		cout << "INIT DONE" << endl;
	}
	pii query(int x1, int y1, int x2, int y2) {
		int i = __lg(x2-x1+1);
		int j = __lg(y2-y1+1);
		x2 = x2 - (1<<i) + 1;
		y2 = y2 - (1<<j) + 1;
		return merge4(ra[i][j][x1][y1], ra[i][j][x1][y2], ra[i][j][x2][y1], ra[i][j][x2][y2]);
	}
} rmq;

int N, M;

int32_t main() {
	IOS;
	init();
	int T; cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cout << "Case #" << cas << ": " << endl;
		cin >> N >> M;

		for (int i=0; i<N; i++) {
			for (int j=0; j<M; j++) {
				cin >> rmq.arr[i][j].F;
			}
		}

		for (int i=0; i<N; i++) {
			for (int j=0; j<M; j++) {
				cin >> rmq.arr[i][j].S;
			}
		}
		rmq.init(N, M);

		int Q; cin >> Q;
		for (int i=0; i<Q; i++) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			pii ret = rmq.query(x1-1, y1-1, x2-1, y2-1);
//			cout << "ans = ";
			if (ret == BAD) {
				cout << -1 << endl;
			} else {
				cout << ret.F << endl;
			}
		}
	}

	return 0;
}

