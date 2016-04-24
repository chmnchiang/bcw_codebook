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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

typedef long long ll;
const ll INF = 1LL << 60;

struct Car {
	ll x,v;
	ll at(ll t) { return x + v*t; }
};
struct Item {
	ll t,p,f;
}ip[4005];

int N,T;
ll dp[4005];
//ll dp2[4005][4005];
int deqfr[4005];
vector<Car> deq[4005];

inline bool better(const Car &a, const Car &b, const Car &c) {
	return (a.x-b.x)*(c.v-b.v) >= (b.x-c.x)*(b.v-a.v);
}
inline void push_deq(vector<Car> &d, int &fr, Car c) {
	if (SZ(d)>fr) assert(d.back().v <= c.v);
	while (SZ(d)>fr and d.back().x <= c.x) d.pop_back();
	while (SZ(d)-fr >= 2 and better(d[SZ(d)-2],d[SZ(d)-1],c)) d.pop_back();
	d.PB(c);
}
int main() {
	IOS;
	while (cin >> N >> T) {
		REP(i,T) deq[i].reserve(4005);
		REP1(i,1,N) {
			cin >> ip[i].t >> ip[i].p >> ip[i].f;
		}
		sort(ip+1,ip+1+N, [](Item a, Item b) { return a.f < b.f; } );
		REP1(i,0,T) {
			deq[i].clear();
			deqfr[i] = 0;
		}
//		REP1(i,0,N) REP1(j,0,T) dp2[i][j] = -INF;

		ll ans = 0;
		REP1(i,1,N) {
			for (int j=T; j>=ip[i].t; j--) {
				int tp = j-ip[i].t;
				ll res = -INF;
				int &fr = deqfr[tp];
				vector<Car> &d = deq[tp];
				while (SZ(d)-fr > 1 and d[fr].at(ip[i].f) <= d[fr+1].at(ip[i].f)) fr++;
				if (SZ(d) > fr)	res = d[fr].at(ip[i].f);
				res += ip[i].p - ip[i].f * ip[i].f;
				res = max(res, (ll)ip[i].p);
				ans = max(ans, res);
				Car c;
				c.x = res - ip[i].f*ip[i].f;
				c.v = 2*ip[i].f;
				push_deq(deq[j],deqfr[j],c);
			}
		}
		cout << ans << endl;
	}

	return 0;
}

