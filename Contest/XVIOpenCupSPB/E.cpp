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

#define int long long
int N;
using pii = pair<int, int>;
vector<pii> ip;
vector<pii> ans;

vector<pii> nrm(const vector<pii> &a) {
	vector<pii> ret;
	for (auto p: a) {
		if (p.S) ret.PB(p);
	}
	return ret;
}

void calc() {
	ans.clear();
	if (SZ(ip) == 1) return;

	for (int i=N-2; i>=0; i--) {
		if (i == N-2 and ip[i].F == ip[i+1].F + 1) continue;

		for (int j=0; j<i; j++) {
			ans.PB(ip[j]);
		}
		pii p = ip[i];
		int z = p.F - 1;
		ans.PB({p.F, p.S-1});


		int sm = p.F, sl = 1;
		for (int j=i+1; j<N; j++) {
			sm += ip[j].F * ip[j].S;
			sl += ip[j].S;
		}
		int alp = (sm - sl) / (z - 1);
		int bet = (sm - sl) % (z - 1);


		ans.PB({z, alp});
		if (bet) ans.PB({bet+1, 1});
		ans.PB({1, sl - alp - !!bet});
		break;
	}

	if (SZ(ans)) ans = nrm(ans);
}

int32_t main() {
	IOS;
	cin >> N;
	ip.resize(N);
	
	for (int i=0; i<N; i++) cin >> ip[i].S >> ip[i].F;

	calc();

	if (!SZ(ans)) {
		cout << -1 << endl;
	} else {
		cout << SZ(ans) << endl;
		for (auto p: ans) {
			cout << p.S << ' ' << p.F << endl;
		}
	}

	return 0;
}

