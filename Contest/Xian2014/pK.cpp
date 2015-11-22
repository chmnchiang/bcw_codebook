#include <bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long i64;
typedef pair<i64, i64> pii;
struct dt {
	i64 l, r, s;
};
set<pii> st;
vector<i64> vl;
vector<dt> dl;

void go(i64 &a, i64 &b) {
	if (a < b*4) {
		i64 t = abs(a-b);
		a = b; b = t;
		vl.PB(a); vl.PB(b);
	} else {
		i64 k = a / b;
		k = (k / 2 - 1) * 2;
		dl.PB({a - k*b, a, b});
		a = a - k * b;
	}
}

int main() {

	IOS;
	int T; cin >> T;

	for (int _t=1; _t<=T; _t++) {
		vl.clear();
		dl.clear();

		i64 A, B; cin >> A >> B;
		if (not A and not B) {
			cout << "Case #" << _t << ": " << 1 << endl;
			continue;
		}

		i64 G = __gcd(A, B);
		A /= G; B /= G;
		vl.PB(A);
		vl.PB(B);

		while (B) {
			go(A, B);
		}

		i64 ans = 0;

		sort(ALL(vl));
		vl.resize(unique(ALL(vl)) - vl.begin());
		auto inr = [](i64 a, dt d) {
			if (a > d.r or a < d.l) return false;
			if ( (a - d.l) % d.s != 0 ) return false;
			return true;
		};

		for (int i=0; i<SZ(dl); i++) {
			ans += (dl[i].r - dl[i].l) / dl[i].s + 1;
		}
		//cout << ans << endl;
		for (auto x: vl) {
			bool fg = true;
			for (int i=0; i<SZ(dl); i++) {
				if (inr(x, dl[i])) {
					fg = false;
					break;
				}
			}
			if (fg) ans ++;
		}

		cout << "Case #" << _t << ": " << ans << endl;
	}

	return 0;
}

