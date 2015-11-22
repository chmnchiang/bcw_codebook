#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!
#define int long long
typedef long long i64;
typedef pair<i64, i64> pll;
typedef vector<pll> vpll;

const i64 INF = 1029384756102938ll;

vpll merge(vpll v1, vpll v2) {
	int s1 = SZ(v1), s2 = SZ(v2);
	int id1, id2; id1 = id2 = 0;
	vpll ret;
	i64 y = -INF-10;
	while (id1 < s1 and id2 < s2) {
		pll p1 = v1[id1], p2 = v2[id2];
		if (p1.F < p2.F or (p1.F == p2.F and p1.S > p2.S) ) {
			if (y < p1.S) {
				ret.PB(p1);
				y = p1.S;
			}
			id1 ++;
		} else {
			if (y < p2.S) {
				ret.PB(p2);
				y = p2.S;
			}
			id2 ++;
		}
	}
	while (id1 < s1) {
		pll p1 = v1[id1];
		if (y < p1.S) {
			ret.PB(p1);
			y = p1.S;
		}
		id1 ++;
	}
	while (id2 < s2) {
		pll p2 = v2[id2];
		if (y < p2.S) {
			ret.PB(p2);
			y = p2.S;
		}
		id2 ++;
	}
	return ret;
}

vpll negneg(vpll v) {
	vpll ret;
	int sz = SZ(v);
	v.PB({0, 0});
	for (int i=sz-1; i>=0; i--) {
		ret.PB({-v[i+1].F+1, -v[i].S});
	}
	ret[0].F = -INF;
	return ret;
}

vpll shift(vpll v, i64 x, i64 y) {
	vpll ret;
	int sz = SZ(v);
	for (int i=0; i<sz; i++) {
		ret.PB({v[i].F+x, v[i].S+y});
	}
	ret[0].F = -INF;
	return ret;
}

vpll trans(vpll v) {
	vpll ret;
	int sz = SZ(v);
	for (int i=sz-1; i>=0; i--) {
		if (v[i].F <= 1) {
			ret.PB({1, v[i].S});
			break;
		} else {
			ret.PB(v[i]);
		}
	}
	ret.PB({-INF, -INF});
	reverse(ALL(ret));
	return ret;
}

const int MX = 200;
int N, A, B;
vpll ip;
vpll dp[MX];

i64 query(vpll v, i64 x) {
	int sz = SZ(v);
	for (int i=sz-1; i>=0; i--) {
		if (v[i].F <= x) return v[i].S;
	}
	return -INF;
}

void print(vpll v) {
	for (auto x: v) {
		cout << "(" << x.F << ", " << x.S << ")";
	}
	cout << endl;
}

int32_t main() {

	IOS;
	i64 tot = 0;
	cin >> N >> A >> B;
	for (int i=0; i<N; i++) {
		i64 eh, hao; 
		cin >> eh >> hao;
		ip.PB({eh, hao});
		tot += hao;
	}
	ip.PB({0, 0});
	reverse(ALL(ip));
	dp[0].PB({-INF, 0});

	for (int i=1; i<=N; i++) {
		vpll a = shift(negneg(dp[i-1]), -ip[i].F, ip[i].S);
		vpll b = trans(shift(dp[i-1], ip[i].F+1, -ip[i].S));
		dp[i] = merge(a, b);
		/*
		cout << "***" << i << endl ;
		print(a);
		print(b);
		print(dp[i]);
		cout << endl;
		*/
	}
	i64 dhao = query(dp[N], A-B);
	cout << ((tot+dhao)/2) << ' ' << ((tot-dhao)/2) << endl;

    return 0;
}

