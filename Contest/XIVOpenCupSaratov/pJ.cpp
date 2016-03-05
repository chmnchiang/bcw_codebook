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
typedef long long ll;

const int MXN = 1000005;

int N,T,cnt[MXN],tc,ansh[MXN];
int lim[MXN];
ll tot,cost[MXN],ansc[MXN];
vector<int> fac[MXN];

void predo() {
	REP1(i,1,N) {
		for (int j=i; j<=N; j+=i) {
			fac[j].PB(i);
		}
	}
}
void solve() {
	REP1(i,1,N-1) {
		cnt[i] = 1;
		cost[i] = 0;
	}
	ansh[N] = 0;
	int rpos = N-1;
	tot = 0;
	tc = N-1;
	REP1(i,1,N) {
		for (auto it:fac[i]) {
			if (it > rpos) break;
			tot += i;
			cost[it] += i;
			cnt[it]++;
			tc++;
		}
		while (tc >= N and rpos >= 1) {
			ansh[rpos] = i;
			ansc[rpos] = tot;
			ansc[rpos] -= 1LL * (tc - N) * i;
//			cout << rpos << " : " << i << " " << ansc[rpos] << endl;
//			cout << "CURRENT " << tc << " " << tot << endl;
			tot -= cost[rpos];
			tc -= cnt[rpos];
			rpos--;
//			cout << "AFTER " << tc << " " << tot << endl;
		}
	}
}
void output() {
	int best = 1;
	REP1(i,1,N) {
		ansc[i] += 1LL * (i-1) * T + N;
		lim[i] = 0;
//		cout << i << " " << ansc[i] << endl;
		if (ansc[i] < ansc[best]) best = i;
	}
//	cout << "BEST " << best << endl;

	tc = best;
	REP1(i,1,ansh[best]) {
		for (auto it:fac[i]) {
			if (it > best) break;
			if (tc >= N) break;
			lim[it] = i;
			tc++;
		}
		if (tc >= N) break;
	}
	ll t = 0;
	vector<int> vec;
	int cur = 0;
	REP1(i,1,best) {
//		cout << "lim " << i << " : " << lim[i] << endl;
		for (int j=0; j<=lim[i]; j+=i) {
			t += j+1;
			cur++;
			if (cur >= N) break;
		}
		if (cur >= N) break;
		vec.PB(cur);
		t += T;
	}
//	cout << t << " " << ansc[best] << endl;
	assert(t == ansc[best]);

	cout << t << endl;
	cout << SZ(vec) << endl;
	for (auto it:vec) cout << it << " ";
	cout << endl;
}
int32_t main() {
	IOS;
	cin >> N >> T;
	predo();
	solve();
	output();

	return 0;
}
