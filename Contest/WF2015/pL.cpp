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


typedef long double ld;
typedef long long ll;
typedef pair<ld,ll> pdl;

int N;
ll jie[21];
ld prob[4];

int main() {
	IOS;
	cin >> N;
	REP(i,4) cin >> prob[i];
	jie[0] = 1;
	REP1(i,1,N) jie[i] = jie[i-1] * i;
	priority_queue<pdl> pq;

	REP1(a,0,N) REP1(b,0,N) REP1(c,0,N) REP1(d,0,N) {
		if (a + b + c + d == N) {
			ld p = 1;
			REP(i,a) p *= prob[0];
			REP(i,b) p *= prob[1];
			REP(i,c) p *= prob[2];
			REP(i,d) p *= prob[3];
			ll x = jie[N] / jie[a] / jie[b] / jie[c] / jie[d];
			pq.push(pdl(-p,x));
		}
	}

	ld ans = 0;
	while (!pq.empty()) {
		auto x = pq.top();
		pq.pop();
		if (x.S == 1) {
			if (pq.empty()) break;
			auto y = pq.top();
			pq.pop();
			ans += x.F + y.F;
			y.S--;
			if (y.S) pq.push(y);
			pq.push(pdl(x.F+y.F,1));
		} else {
			int odd = x.S & 1;
			ans += x.F * (x.S - odd);
			if (odd) pq.push(pdl(x.F,1));
			ll rem = x.S / 2;
			pq.push(pdl(x.F*2,rem));
		}
	}
	ans = -ans;
	cout << fixed << setprecision(10) << ans << endl;

	return 0;
}

