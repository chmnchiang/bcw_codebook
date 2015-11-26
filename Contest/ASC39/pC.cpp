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
// Let's Fight!

#define int long long
const int MX = 101010;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tup;

const int _x = 0;
const int _y = 1;
const int _r = 2;

const double PI = acos(-1);

int& operator / (tup &t, int a) {
	if (a == 0)
		return get<0>(t);
	else if (a == 1)
		return get<1>(t);
	else if (a == 2)
		return get<2>(t);
	assert(false);
}

int N;
vector<tup> ip;
set<pii> st;
int ord[MX];
int32_t main() {
    FILEIO("circles");

	cin >> N;
	for (int i=0; i<N; i++) {
		int x, y, r; cin >> x >> y >> r;
		ip.PB(tup{x, y, r});
	}

	sort(ALL(ip), [](tup t1, tup t2) {
		int s1 = t1/_y - t1/_r;
		int s2 = t2/_y - t2/_r;
		if (s1 != s2)
			return s1 < s2;
		if (t1/_x != t2/_x)
			return t1/_x < t2/_x;
		return t1/_r > t2/_r;
	});

	double ans = 0.0;

	auto isin = [](int a, int b) -> bool {
		int xa, ya, ra;
		tie(xa, ya, ra) = ip[a];
		int xb = ip[b]/_x, yb = ip[b]/_y;
		int disq = (xa - xb) * (xa - xb) + 
			(ya - yb) * (ya - yb);
		return (disq <= ra * ra);
	};

	for (int i=0; i<N; i++) {
		tup t = ip[i];
		pii p = {t/_x, i};
		auto it = st.lower_bound(p);
		bool ok = true;
		int y = t/_y - t/_r;
		while (it != st.end()) {
			pii he = *it;
			tup the = ip[he.S];
			if (y > the/_y + the/_r) {
				st.erase(it);
				it = st.lower_bound(p);
				continue;
			}
			if (isin(he.S, i)) {
				ok = false;
			}
			break;
		}

		it = st.lower_bound(p);
		while (it != st.begin()) {
			pii he = *(--it);
			tup the = ip[he.S];
			if (y > the/_y + the/_r) {
				st.erase(it);
				it = st.lower_bound(p);
				continue;
			}
			if (isin(he.S, i)) {
				ok = false;
			}
			break;
		}

		if (ok) {
			ans += PI * (t/_r) * (t/_r);
			st.insert(p);
		}
	}

	cout << fixed << setprecision(15) << ans << endl;
	


    return 0;
}

