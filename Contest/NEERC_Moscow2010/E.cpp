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
typedef pair<int,int> pii;
const int LOG = 18;
const int MXN = 100005;
using LL = long long;
const LL INF = 1e16;

int N,M,A,B;
pii ip[MXN];
LL rmq[LOG][MXN],rmq2[LOG][MXN];

inline LL qrymin(int i, int j) {
	int l = 31-__builtin_clz(j-i+1);
	return min(rmq[l][i], rmq[l][j-(1<<l)+1]);
}
inline LL qrymax(int i, int j) {
	int l = 31-__builtin_clz(j-i+1);
	return max(rmq2[l][i], rmq2[l][j-(1<<l)+1]);
}

LL S[MXN];
LL calc(vector<pii> ps) {
	int Z = SZ(ps);
	//cout << ps << endl;
	for (int i=0; i<=B; i++) S[i] = 0;
	for (int i=0; i<Z; i++) {
		int l = ps[i].F, r = ps[i].S;
		assert(l <= r);
		int ll = l % B, rr = (r+1) % B;
		//cout << ll << ' ' << rr << endl;
		int len = r - l + 1;
		int hhh = (len + B - 1) / B;
		if (rr <= ll) {
			S[0] += hhh + 1;
			S[rr] --;
			S[ll+1] ++;
		} else {
			S[0] += hhh;
			S[ll+1] ++;
			S[rr] --;
		}
	}

	for (int i=1; i<B; i++) {
		S[i] += S[i-1];
	}
	LL ans = INF;
	for (int i=0; i<B; i++) {
		ans = min(ans, S[i]);
		//cout << S[i] << ' ';
	}
	//cout << endl;
	return ans;
}
int32_t main() {
	IOS;
	cin >> N >> M >> A >> B;
	REP(i,LOG) REP(j,MXN) {
		rmq[i][j] = INF;
		rmq2[i][j] = -INF;
	}
	REP(i,N) {
		cin >> ip[i].F >> ip[i].S;
		rmq[0][i] = ip[i].F;
		rmq2[0][i] = ip[i].S;
	}

	REP1(i,1,LOG-1) {
		REP(j,MXN) {
			if (j + (1<<i) > MXN) break;
			rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
			rmq2[i][j] = max(rmq2[i-1][j], rmq2[i-1][j+(1<<(i-1))]);
		}
	}

	LL ans = INF;
	REP(dx,min(A,N)) {
		vector<pii> vec;
		if (dx) {
			int a = qrymin(0,dx-1);
			int b = qrymax(0,dx-1);
			vec.PB({a,b});
		}
		for (int i=dx; i<N; i+=A) {
			int a = qrymin(i,min(i+A-1,N-1));
			int b = qrymax(i,min(i+A-1,N-1));
			vec.PB({a,b});
		}
		ans = min(ans, calc(vec));
	}
	cout << ans << endl;

	return 0;
}
