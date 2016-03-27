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
template<typename T>
ostream& operator <<(ostream &s, const set<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!


typedef long long ll;
typedef pair<ll,ll> pll;
const ll MOD = 1097774749;
const int P1 = 12721;
const int P2 = 13331;
const int P3 = 14341;
const int P4 = 999983;
const int MAG1 = 222557;
const int MAG2 = 999983;
const int MAG3 = 17341;
const int MAG4 = 66449;
const int MXN = 100005;

pll operator + (pll a, pll b) { return {a.F+b.F,a.S+b.S}; }
pll operator - (pll a, pll b) { return {a.F-b.F,a.S-b.S}; }

int N,T;
ll ip[MXN];
pll hs;
string str;
set<pll> app;
set<pll> seg[2],pq;

ll fast_pow(ll x, ll y) {
	if (!y) return 1;
	ll r = fast_pow(x, y/2);
	r = r * r % MOD;
	if (y & 1) r = r * x % MOD;
	return r;
}
inline pll get_hash(ll p, ll len) {
	pll res;
	res.F = MAG1 * fast_pow(P1,p) + MAG2 * fast_pow(P2,len);
	res.S = MAG3 * fast_pow(P3,p) + MAG4 * fast_pow(P3,len);
	res.F %= MOD;
	res.S %= MOD;
	return res;
}
inline void add(int u, ll p, ll len) {
	seg[u].insert({p,len});
	pq.insert({-len,p});
	if (u) {
//		cout << "ADD " << pll(p,len) <<  " " << get_hash(p,len) << endl;
		hs = hs + get_hash(p, len);
		if (hs.F >= MOD) hs.F -= MOD;
		if (hs.S >= MOD) hs.S -= MOD;
	}
}
inline void del(int u, ll p, ll len) {
	assert(seg[u].count({p,len}));
	seg[u].erase({p,len});
	pq.erase({-len,p});
	if (u) {
//		cout << "DEL " << pll(p,len) << " " << get_hash(p,len) << endl;
		hs = hs - get_hash(p, len);
		if (hs.F < 0) hs.F += MOD;
		if (hs.S < 0) hs.S += MOD;
	}
}
void pick_white(ll p, ll len) {
	del(0,p,len);
	ll a = len / 2;
	ll b = a;
	if (len & 1) a++;
	
	add(0,p,a);

	p += a;
	auto it = seg[1].lower_bound({p,0});
	if (it != end(seg[1])) {
		assert(it->F == p+b);
		b += it->S;
		del(1,it->F,it->S);
	}
	add(1,p,b);
}
void pick_black(ll p, ll len) {
	del(1,p,len);

	ll a = len / 2;
	ll b = a;
	if (len & 1) b++;

	auto it = seg[0].lower_bound({p,0});
	if (it != begin(seg[0])) {
		it--;
		assert(it->F + it->S == p);
		p = it->F;
		a += it->S;
		del(0,it->F,it->S);
	}
	add(0,p,a);

	p += a;
	add(1,p,b);
}
int main() {
	IOS;
	FILEIO("segments");

	cin >> N >> T;
	cin >> str;
	int u = 0;
	if (str == "black") u = 1;
	ll curp = 0;
	hs = {0,0};
	REP(i,N) {
		cin >> ip[i];
		add(u,curp,ip[i]);
		curp += ip[i];
		u ^= 1;
	}


	int ans = T;
	REP1(t,1,T) {

		ll p = pq.begin()->S;
		ll len = -pq.begin()->F;

		if (app.count(hs) or len == 1) {
			ans = t - 1;
			break;
		}
		app.insert(hs);

		if (seg[0].count({p,len})) {
			pick_white(p,len);
		} else {
			pick_black(p,len);
		}
		/*
		cout << "==== " << t << " ====\n";
		cout << seg[0] << endl;
		cout << seg[1] << endl;
		*/
	}
	cout << ans << endl;


	return 0;
}
