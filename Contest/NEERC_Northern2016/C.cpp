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


const int MX = 1000005;
typedef array<int,3> Arr;

struct BIT {
	int bit[MX];
	int lb(int x) { return x & -x; }
	void upd(int x, int v) {
		x += 2;
		for (int i=x; i<MX; i+=lb(i))
			bit[i] = max(bit[i], v);
	}
	int qry(int x) {
		int r = 0;
		x += 2;
		for (int i=x; i>0; i-=lb(i))
			r = max(r, bit[i]);
		return r;
	}
}bit;

int N,ans[MX],h[MX];
Arr ip[MX];



int main() {
	IOS;
	FILEIO("codecoder");
	cin >> N;
	REP(i,N) {
		cin >> ip[i][0] >> ip[i][1];
		ip[i][2] = i;
	}
	sort(ip,ip+N);
	h[0] = ip[0][1];
	for (int i=1; i<N; i++) {
		h[i] = max(h[i-1], ip[i][1]);
	}
	for (int i=N-1; i>=0; i--) {
		int r = bit.qry(h[i]);
		r = max(r, i);
		ans[ip[i][2]] = r;
		bit.upd(ip[i][1], r);
	}

	REP(i,N) cout << ans[i] << "\n";

	return 0;
}

