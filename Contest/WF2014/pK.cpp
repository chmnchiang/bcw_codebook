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
const int MXN = 4000005;

struct Segment {
	int l,r;
};
int N,K,nxt[MXN],vst[MXN],prv[MXN];
Segment ip[MXN];
vector<int> add[MXN],sub[MXN];
multiset<pii> st;

int dis(int l, int r) {
	while (r < l) r += N;
	return r-l;
}
int check(vector<int> cyc) {
//	cout << cyc << endl;
//	for (auto id:cyc) cout << ip[id].l << " " << ip[id].r << endl;
	vector<pii> vec;
	for (auto it:cyc) {
		vec.PB({ip[it].l,ip[it].r});
	}
	for (auto it:cyc) {
		vec.PB({ip[it].l,ip[it].r});
	}
	REP1(i,1,SZ(vec)-1) {
		while (vec[i].F < vec[i-1].F) {
			vec[i].F += N;
			vec[i].S += N;
		}
	}
//	cout << vec << endl;
	int j = 0;
	int res = K+1;
	REP(i,SZ(vec)) {
		while (j < SZ(vec) and vec[j].S-vec[i].F < N) j++;
		if (j != SZ(vec)) {
//			cout << i << " " << j << endl;
			res = min(res, j-i+1);
		}
	}
	return res;
}
int main() {
	cin >> N >> K;
	int trivial = 0;
	REP(i,K) {
		cin >> ip[i].l >> ip[i].r;
		ip[i].r++;
		if (ip[i].r > N) ip[i].r -= N;
		if (ip[i].l >= ip[i].r) ip[i].r += N;
		ip[i+K] = ip[i];
		ip[i+K].l += N;
		ip[i+K].r += N;
		if (ip[i].l+N == ip[i].r) trivial = 1;
	}
	REP(i,2*K) {
		add[ip[i].l].PB(i);
		sub[ip[i].r].PB(i);
	}
	REP(i,MXN) {
		for (auto it:add[i]) st.insert({ip[it].r,it});
		for (auto qid:sub[i]) {
			nxt[qid] = st.rbegin()->S;
		}
		for (auto it:sub[i]) st.erase(st.find({ip[it].r,it}));
	}
	REP(i,K) {
		int d1 = ip[nxt[i]].r - ip[i].r;
		int d2 = ip[nxt[i+K]].r - ip[i+K].r;
		if (d1 < d2) nxt[i] = nxt[i+K];
		int d = max(d1,d2);
		if (d == 0) nxt[i] = i;
		else nxt[i] %= K;
	}
	/*
	REP(i,K) {
		cout << "#" << i << " : " << pii(ip[i].l,ip[i].r) << " " << pii(ip[i+K].l,ip[i+K].r) << endl;
	}
	REP(i,K) cout << i << " " << nxt[i] << endl;
	*/

	int ans = 1e9;
	int ts = 0;
	REP(i,K) {
		if (vst[i]) continue;
		ts++;
		int cur = i;

		vector<int> vec;
		while (!vst[cur]) {
			vec.PB(cur);
			vst[cur] = ts;
			cur = nxt[cur];
		}
		if (vst[cur] != ts) continue;
		vector<int> cyc;
		cyc.PB(cur);
		while (vec.back() != cur) {
			cyc.PB(vec.back());
			vec.pop_back();
		}
		reverse(ALL(cyc));
		if (SZ(cyc) > 1) ans = min(ans, check(cyc));
//		if (check(cyc)) ans = min(ans,SZ(cyc));
	}
	if (trivial) ans = 1;
	if (ans > K) cout << "impossible\n";
	else cout << ans << endl;

	return 0;
}

