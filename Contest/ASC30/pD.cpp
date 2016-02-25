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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

typedef long long ll;

int ip[20],pw[15];
ll dp[19][2][2][60000];

inline int getv(int s, int i) {
	REP(_,i) s /= 3;
	return s%3;
}
inline int addv(int s, int i) {
	int v = getv(s, i);
	assert(v < 2);
	s -= v * pw[i];
	s += (v + 1) * pw[i];
	return s;
}
ll go(int pos, int canAny, int start, int s) {
	if (pos > 18) return start;
	//if (dp[pos][canAny][start].count(s)) return dp[pos][canAny][start][s];
	ll &res = dp[pos][canAny][start][s];
	if (res != -1) return res;
	/*
	cout << "=================\n";
	cout << pos << " " << canAny << " " << start << endl;
	REP1(i,0,9) cout << getv(s, i) << " ";
	cout << endl;
	*/
	res = 0;
	REP1(i,0,9) {
		if (!canAny and i > ip[pos]) continue;
		if ((start or i) and getv(s, i) >= 2) continue;
		int ns = s;
		if (start or i) ns = addv(ns, i);
		res += go(pos+1, canAny||i<ip[pos], start||i, ns);
	}
	return res;
}
ll solve(ll x) {
	memset(dp, -1, sizeof(dp));
	ll val = x;
	for (int i=18; i>=0; i--) {
		ip[i] = val % 10;
		val /= 10;
	}
	//cout << go(16,0,0,0) << endl;
	//exit(0);
	return go(0, 0, 0, 0);
}
ll slow(ll L, ll R) {
	ll res = 0;
	REP1(i,L,R) {
		int cnt[10] = {};
		ll x = i;
		res++;
		while (x) {
			ll v = x % 10;
			x /= 10;
			cnt[v]++;
			if (cnt[v] > 2) {
				res--;
				break;
			}
		}
	}
	return res;
}
int main() {
	pw[0] = 1;
	REP1(i,1,14) pw[i] = pw[i-1] * 3;
	IOS;
	FILEIO("exchange");
	ll L, R;
	cin >> L >> R;
	ll ans = solve(R) - solve(L-1);
	cout << ans << endl;
//	cout << slow(L,R) << endl;

    return 0;
}

