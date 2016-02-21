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
#define REP(i,n) for (int i=0;i<(n);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef long long ll;
typedef pair<ll,ll> pll;
const int MXN = 500005;

struct Query {
	ll x, y;
	int id;
}qry[MXN];

int N,Q;
ll ans[MXN];
pll ip[MXN];
int fr,bk;
pll deq[MXN];
ll ans2[MXN];

void slow() {
	REP(i,Q) {
		ans2[i] = -1;
		REP(j,N) {
			ll c = ip[j].F * qry[i].x + ip[j].S * qry[i].y;
			if (ans2[i] == -1 || c < ans2[i])
				ans2[i] = c;
		}
	}
}
bool compQ(const Query& a, const Query& b) {
	return a.y * b.x < a.x * b.y;
}
bool comp(const pll& a, const pll& b) {
	return tie(a.S, a.F) > tie(b.S, b.F);
}
bool check(pll x, pll y, pll z) {
	return (z.F-y.F)*(x.S-y.S) < (y.F-x.F)*(y.S-z.S);
}
int main() {
	IOS;
	cin >> Q;
	REP(i,Q) {
		cin >> qry[i].x >> qry[i].y;
		qry[i].id = i;
	}
	cin >> N;
	REP(i,N) {
		cin >> ip[i].F >> ip[i].S;
	}

//	slow();

	sort(qry,qry+Q,compQ);
	sort(ip,ip+N,comp);
	fr = bk = 0;
	REP(i,N) {
		while (bk > fr && ip[i].F <= deq[bk-1].F) {
			bk--;
		}
		while (bk - fr >= 2 && check(deq[bk-2], deq[bk-1], ip[i])) {
			bk--;
		}
		deq[bk++] = ip[i];
	}
	REP(i,Q) {
		int id = qry[i].id;
		ll x = qry[i].x, y = qry[i].y;
		while (bk - fr >= 2 && deq[fr].F*x+deq[fr].S*y > deq[fr+1].F*x+deq[fr+1].S*y)
			fr++;
		ans[id] = deq[fr].F*x+deq[fr].S*y;
	}

	REP(i,Q) {
//		assert(ans[i] == ans2[i]);
		cout << ans[i] << " \n"[i == Q-1];
	}

    return 0;
}
