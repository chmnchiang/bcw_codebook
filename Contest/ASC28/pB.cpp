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

typedef pair<int,int> pii;
const int MXN = 100005;

int N,M,W,D;
int T;
pii ip[MXN],ans[MXN];

void solve1(int i) {
	T = ip[i].F + ip[i].S;
	int l = 0, r = T;
	ans[i] = {l, r-ip[i].S};
	l += ip[i].F;
	r -= ip[i].S;

	REP(j,N) {
		if (i == j) continue;
		ans[j] = {l, r-ip[j].S};
		l += ip[j].F;
		r -= ip[j].S;
	}
	
}
void solve2() {
	T = M;
	int wl, wr, dl, dr;
	wl = dl = 0;
	wr = dr = M;
	int best = 0, cost = -1;
	REP(i,N) {
		int v = min(ip[i].F, ip[i].S);
		if (v > cost) {
			cost = v;
			best = i;
		}
	}

	ans[best] = {wl, dr-ip[best].S};

	wl += ip[best].F;
	dr -= ip[best].S;

	REP(i,N) {
		if (i == best) continue;
		if (ip[i].F <= ip[i].S) {
			ans[i] = {wr-ip[i].F, dr-ip[i].S};
			wr -= ip[i].F;
			dr -= ip[i].S;
		} else {
			ans[i] = {wl, dl};
			wl += ip[i].F;
			dl += ip[i].S;
		}
	}

}
int main() {
	IOS;
	FILEIO("carwash");
	cin >> N;
	REP(i,N) cin >> ip[i].F >> ip[i].S;

	W = D = 0;
	REP(i,N) {
		W += ip[i].F;
		D += ip[i].S;
	}

	int cas = -1;
	M = max(W,D);
	REP(i,N) {
		if (ip[i].F + ip[i].S >= M) {
			cas = i;
			break;
		}
	}
	if (cas != -1) solve1(cas);
	else solve2();

	cout << T << endl;
	REP(i,N) cout << ans[i].F << " " << ans[i].S << "\n";

	REP(i,N) {
		assert(ans[i].F+ip[i].F <= ans[i].S or ans[i].F >= ans[i].S+ip[i].S);
	}


    return 0;
}

