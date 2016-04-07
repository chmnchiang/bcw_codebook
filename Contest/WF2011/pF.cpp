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
typedef pair<ll,ll> pll;
const int MXN = 100005;
const ll INF = 1LL<<60;

struct Machine {
	ll d,p,r,g;
}ip[MXN];
struct Car {
	ll x,v;
	ll at(ll t) { return x + v * t; }
	bool operator < (const Car &he) const { return tie(v,x) < tie(he.v,he.x); }
};

int N;
ll C,D;
ll dp[MXN];
int fr,bk,deq[MXN];

bool better(const Car &a, const Car &b, const Car &c) {
	__int128_t dx1,dv1,dx2,dv2;
	dx1 = a.x-b.x;
	dv1 = b.v-a.v;
	dx2 = b.x-c.x;
	dv2 = c.v-b.v;
	return dx1*dv2 >= dx2*dv1;
	return (a.x-b.x) * (c.v-b.v) >= (b.x-c.x) * (b.v-a.v);
}
bool compD(Machine a, Machine b) { return a.d < b.d; }
void dc(int l, int r) {
	if (l >= r) return;
	int m = (l+r)/2;
	dc(l,m);
	
	vector<Car> cars;
	vector<pll> qry;
	REP1(i,l,m) {
		Car c;
		c.x = dp[i]+ip[i].r-ip[i].d*ip[i].g-ip[i].g;
		c.v = ip[i].g;
		cars.PB(c);
	}
	REP1(i,m+1,r) {
		qry.PB({ip[i].d,i});
	}

	sort(ALL(cars));
	sort(ALL(qry));

	fr = bk = 0;
	REP(i,SZ(cars)) {
		while (fr != bk and cars[deq[bk-1]].x <= cars[i].x) bk--; 
		while (bk-fr >= 2 and better(cars[deq[bk-2]],cars[deq[bk-1]],cars[i])) bk--;
		deq[bk++] = i;
	}
	for (auto it:qry) {
		ll t = it.F;
		int id = it.S;
//		while (bk-fr >= 2 and cars[deq[fr]].at(t) <= cars[deq[fr+1]].at(t)) fr++;
//		dp[id] = max(dp[id], cars[deq[fr]].at(t)-ip[id].p);
		REP1(i,fr,bk-1)
			dp[id] = max(dp[id], cars[deq[i]].at(t)-ip[id].p);
		if (dp[id] < 0) dp[id] = -INF;
	}

	dc(m+1,r);
}
int main() {
	IOS;
	int cas = 0;
	while (cin >> N >> C >> D) {
		if (N+C+D <= 0) break;
		REP1(i,1,N) {
			cin >> ip[i].d >> ip[i].p >> ip[i].r >> ip[i].g;
		}
		ip[0] = {0,0,0,0};
		sort(ip+1,ip+1+N,compD);

		REP1(i,0,N) dp[i] = -INF;

		dp[0] = C;
		dc(0,N);
		/*
		   REP1(i,1,N) {
		   REP1(j,0,i-1) {
		   dp[i] = max(dp[i], dp[j]+ip[j].r-ip[j].d*ip[j].g-ip[j].g+ip[i].d*ip[j].g-ip[i].p);
		   }
		   if (dp[i] < 0) dp[i] = -INF;
		   }
		 */

		ll ans = C;
		REP1(i,1,N) {
			ans = max(ans, dp[i] + ip[i].r + (D-ip[i].d) * ip[i].g);
		}

		cas++;
		cout << "Case " << cas << ": " << ans << endl;
	}


	return 0;
}

