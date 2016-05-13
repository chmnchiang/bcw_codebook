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
const int MXN = 200005;


int N,L;
ll G,P,ip[MXN];

void input() {
	cin >> N >> G >> P;
	REP(i,N) {
		cin >> ip[i];
	}
}
bool test(ll m) {
	if (m >= G) return true;
	if (P <= 5*N) {
		int i = 0;
		REP(_,P) {
			m += ip[i];
			m = max(m,0LL);
			if (m >= G) return true;
			i++;
			if (i >= N) i -= N;
		}
		return false;
	}
	ll step = 0;
	int i = 0;
	while (step < N) {
		m += ip[i];
		m = max(m,0LL);
		if (m >= G) return true;
		i++;
		if (i >= N) i -= N;
		step++;
	}
	ll a = m;
	while (step < 2*N) {
		m += ip[i];
		m = max(m,0LL);
		if (m >= G) return true;
		i++;
		if (i >= N) i -= N;
		step++;
	}
	ll b = m;
	ll add = b - a;
	if (add <= 0) return false;
	ll k = P / N;
	if (k-3 >= (G-m) / add) return true;
	m += (k-3) * add;
	step += (k-3) * N;
	if (m >= G) return true;
	while (step < P) {
		m += ip[i];
		m = max(m,0LL);
		if (m >= G) return true;
		i++;
		if (i >= N) i -= N;
		step++;
	}

	return false;
}
ll solve() {
	ll l=0,r=G+1;
	while (l < r) {
		ll m = (l+r)/2;
		if (test(m)) r = m;
		else l = m+1;
	}
	return l;
}
int main() {
	IOS;
	int nt;
	cin >> nt;
	REP1(t,1,nt) {
		input();
		ll ans = solve();
		cout << "Case #" << t << ": " << ans << endl;
	}


	return 0;
}

