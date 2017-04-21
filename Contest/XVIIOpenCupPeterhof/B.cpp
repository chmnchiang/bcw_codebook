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

using ll = long long;
const int MAXN = 115;
const ll MOD = 1000000007;

int spj = 0;
int counter = 0;
int R,C;
ll lt[MAXN][MAXN],up[MAXN][MAXN];
ll ip1[MAXN][MAXN],ip2[MAXN][MAXN];

ll fpow(ll x, ll y) {
	if (!y) return 1;
	ll res = fpow(x*x%MOD,y/2);
	if (y & 1) res = res * x % MOD;
	return res;
}

inline void norm(int vec[]) {
	static int app[12];
	int ts = 0;
	int zero = 0;
	REP(i,11) app[i] = 0;
	REP(i,R) {
//		counter++;
		if (vec[i] == 0) {
			zero = 1;
			continue;
		}
		int &x = app[vec[i]];
		if (x == 0) x = ++ts;
		vec[i] = x;
	}
	if (!zero) {
		REP(i,R) vec[i] = 1;
	}
}
inline ll encode(const int vec[]) {
	ll res = 0;
	REP(i,R) {
//		counter++;
		res <<= 4;
		res += vec[i];
	}
	return res;
}

void decode(ll v, int res[]) {
	ll x = v;
	for (int i=R-1; i>=0; i--) {
		counter++;
		res[i] = x & 0xF;
		x >>= 4;
	}
	//cout<<"DECODE "<<v<<" "<<res<<endl;
}
void uni(int vec[], int x, int y) {
	if (x == y) return;
	if (x > y) swap(x, y);
	REP(i,R) {
//		counter++;
		if (vec[i] == y) vec[i] = x;
	}
}

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<ll,int> umap_t;

umap_t mp;
vector<ll> states;

const int MM = 1000001;

int gen_ok[2][MM];
ll probDP[2][MM];
array<ll,4> edge[2][MM];

void output(ll v) {
	static int vec[MAXN];
	decode(v, vec);
	REP(i,R) {
		cout<<vec[i];
		if (i != R-1) cout<<" ";
	}
}
void gen_edge(int x, int it) {
	if (x) x = 1;
	if (gen_ok[x][it]) return;
	gen_ok[x][it] = 1;
//	counter++;

	static int vec[MAXN], vec2[MAXN];
	decode(states[it], vec);

	auto &vvv = edge[x][it];
	int mx = 0;
	REP(i,R) mx = max(mx, vec[i]);
	mx++;

	REP(i,4) {
		REP(j,R) vec2[j] = vec[j];
		vec2[R-1] = mx;
		if (i & 1) uni(vec2, vec[R-1], vec2[R-1]);
		if (x and (i & 2)) uni(vec2, vec[0], vec2[R-1]);

//		int zz = vec2[R-1];
//		for (int j=R-1; j>0; j--) vec2[j] = vec2[j-1];
//		vec2[0] = zz;
		rotate(vec2,vec2+R-1,vec2+R);

		norm(vec2);
		ll m = encode(vec2);
		if (mp.find(m) == end(mp)) {
			mp[m] = SZ(states);
			states.PB(m);
		}
		vvv[i] = mp[m];
	}
}

void pre() {
	if (R < C) return;
	spj = 1;
	int N = R;
	int M = C;
	R = M - 1;
	C = N + 1;

	ll arr[MAXN][MAXN];
	REP(i,MAXN) REP(j,MAXN) {
		arr[i][j] = ip1[i][j];
	}
	REP(i,MAXN) REP(j,MAXN) {
		ip1[i][j] = 100 - arr[j][i];
	}

	REP(i,MAXN) REP(j,MAXN) {
		arr[i][j] = ip2[i][j];
	}
	REP(i,MAXN) REP(j,MAXN) {
		ip2[i][j] = 100 - arr[j][i];
	}
}
void solve() {
	static int vec[MAXN];
	int uuu = 0;

	mp[0] = SZ(states);
	states.PB(0);
	probDP[uuu][0] = 1;

	REP1(y,1,C-1) {
		REP(x,R) {
			auto &me = probDP[uuu];
			auto &he = probDP[uuu^1];
			REP(i,MM) he[i] = 0;

//			cout<<"== "<<x<<", "<<y<<" =="<<endl;
			int sszz = SZ(states);
			REP(id, sszz) {
//				int it = states[id];
				gen_edge(x, id);

				const auto &e = edge[x ? 1 : 0][id];
//				cout<<id<<" "<<it<<" : ";
//				output(it);
//				cout<<endl;
				REP(i,4) {
					ll p = 1.0;

					if (i & 1) p *= lt[x][y];
					else p *= 1 - lt[x][y];
					p %= MOD;
					if (p < 0) p += MOD;

					if (i & 2) p *= up[x][y];
					else p *= 1 - up[x][y];
					p %= MOD;
					if (p < 0) p += MOD;

//					cout<<"*";
//					output(states[e[i]]);
//					cout<<" "<<me[id]*p<<endl;
					he[e[i]] += me[id] * p % MOD;
					if (he[e[i]] >= MOD) he[e[i]] -= MOD;
				}
			}


/*			
			cout<<"TRANS TO"<<endl;
			for (auto it:states) {
				output(it);
				cout<<" : "<<he[mp[it]]<<endl;
			}
*/
			

			uuu ^= 1;
//			swap(me,he);
		}
	}


	ll ans = 0;
	REP(id, SZ(states)) {
		int ok = 0;
		decode(states[id], vec);
		REP(i,R) if (vec[i] == 0) ok = 1;
		if (ok) ans += probDP[uuu][id];
		if (ans >= MOD) ans -= MOD;
	}
	if (spj) ans = (1 - ans + MOD) % MOD;
	cout<<ans<<endl;
}
int main() {
	IOS;
	cin>>R>>C;
	REP(i,R) REP(j,C-1) {
		cin>>ip1[i][j];
	}
	REP(i,R-1) REP(j,C-2) {
		cin>>ip2[i][j];
	}

	pre();

	ll inv100 = fpow(100, MOD-2);
	REP(i,R) REP(j,C-1) {
		lt[i][j+1] = ip1[i][j] * inv100 % MOD;
	}
	REP(i,R-1) REP(j,C-2) {
		up[i+1][j+1] = ip2[i][j] * inv100 % MOD;
	}

	solve();
//	cerr<<"COUNTER = "<<counter<<endl;

	return 0;
}

