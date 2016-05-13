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


typedef long long ll;
const ll MX = 100000000000000000LL;
const int MXN = 10000005;

ll N;
int M,ip[55],app[55];
vector<ll> num[55];

inline bool is2(ll x) {
	ll y = sqrt(x);
	y = max(y-1,0LL);
	while (y*y < x) y++;
	return y*y == x;
}
inline bool is3(ll x) {
	ll y = cbrt(x);
	y = max(y-1,0LL);
	while (y*y*y < x) y++;
	return y*y*y == x;
}
inline ll count2(ll x) {
	ll y = sqrt(x) + 1;
	while (y*y > x) y--;
	ll z = cbrt(x) + 1;
	while (z*z*z > x) z--;
	ll res = 0;
	if (app[2]) res += y;
	if (app[3]) res += z;
	if (app[2] and app[3]) res -= upper_bound(ALL(num[6]),x)-begin(num[6]);
	return res;
}
inline void merge(vector<ll> &A, vector<ll> &B, vector<ll> &C) {
	C.clear();
	int sz1 = SZ(A);
	int sz2 = SZ(B);
	int i=0,j=0;
	while (i<sz1 or j<sz2) {
		if (i<sz1 and (j >= sz2 or A[i] <= B[j])) {
			if ((app[2] and is2(A[i])) or (app[3] and is3(A[i]))) {
				i++;
				continue;
			}
			if (!C.empty() and C.back() == A[i]) {
				i++;
				continue;
			}
			C.PB(A[i++]);
		} else {
			if ((app[2] and is2(B[j])) or (app[3] and is3(B[j]))) {
				j++;
				continue;
			}
			if (!C.empty() and C.back() == B[j]) {
				j++;
				continue;
			}
			C.PB(B[j++]);
		}
		if (SZ(C) >= N) break;
	}
}
vector<ll> vv[2];
ll solve(vector<ll> vec[]) {
	int my = 0;
	vv[0].clear();
	vv[1].clear();
	for (int i=M-1; i>=0; i--) {
		if (ip[i] == 3 or ip[i] == 2) continue;
		vv[my^1].clear();
		merge(vv[my],vec[ip[i]],vv[my^1]);
		my ^= 1;
	}
	ll l,r;
	l = 0;
	r = SZ(vv[my]);
	while (l < r) {
		ll m = (l + r) / 2;
		if (m+1+count2(vv[my][m]) >= N) r = m;
		else l = m+1;
	}
	int x = l;
	if (SZ(vv[my]) == 0) {
		l = 1;
		r = MX;
	} else if (x == 0) {
		l = 1;
		r = vv[my][x];
	} else if (x >= SZ(vv[my])) {
		l = vv[my].back();
		r = MX;
	} else {
		l = vv[my][x-1];
		r = vv[my][x];
	}
	ll aaa=r;
	while (l<r) {
		ll m = (l + r) / 2;
		ll cnt = count2(m)+x+(m>=aaa);
		if (vv[my].empty()) cnt -= m>=aaa;
		if (cnt < N) l = m+1;
		else r = m;
	}
	return l;
}
int main() {
	IOS;

	REP1(i,3,50) {
		vector<ll> &vec = num[i];
		REP1(j,1,1e8) {
			ll val = 1;
			REP(_,i) {
				val = val * j;
				if (val > MX) break;
			}
			if (val > MX) break;
			vec.PB(val);
		}
	}

	int Q;
	cin >> Q;
	REP(_,Q) {
		memset(app,0,sizeof(app));
		cin >> N >> M;
		REP(i,M) {
			cin >> ip[i];
			app[ip[i]] = 1;
		}
		sort(ip,ip+M);
		ll res;
		if (app[1]) {
			res = N;
		} else {
			res = solve(num);
		}
		cout << res << endl;
	}

	return 0;
}


