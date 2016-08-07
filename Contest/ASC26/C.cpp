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

using pii = pair<int, int>;
vector<pii> ip;
int CC, DD;
using p3i = array<int, 3>;
vector<p3i> l1, l2;

deque<int> dq;

void push(int x) {
	while (SZ(dq) and l2[dq.back()][1] <= l2[x][1]) {
		dq.pop_back();
	}
	dq.PB(x);
}

int32_t main() {
	FILEIO("dowry");

	int N, L, R;
	cin>>N>>L>>R;

	for (int i=0; i<N; i++) {
		int w, v;
		cin>>w>>v;
		ip.PB({w, v});
	}

	CC = min(16LL, N);
	DD = N - CC;

	l1.resize(1LL<<CC);
	l2.resize(1LL<<DD);

	for (int i=0; i<(1<<CC); i++) {
		int ww = 0, vv = 0;
		for (int j=0; j<CC; j++) {
			if (i&(1<<j)) {
				ww += ip[j].F;
				vv += ip[j].S;
			}
		}
		l1[i] = {ww, vv, i};
	}

	for (int i=0; i<(1<<DD); i++) {
		int ww = 0, vv = 0;
		for (int j=0; j<DD; j++) {
			if (i&(1<<j)) {
				ww += ip[CC+j].F;
				vv += ip[CC+j].S;
			}
		}
		l2[i] = {ww, vv, i};
	}

	sort(ALL(l1));
	reverse(ALL(l1));
	sort(ALL(l2));

	//cout << l1 << ' ' << l2 << endl;

	int rr2;
	rr2 = 0;
	int ans = 0, exa = 0;

	for (int i=0; i<SZ(l1); i++) {
		auto pi = l1[i];
		while (rr2 < SZ(l2) and pi[0] + l2[rr2][0] <= R) {
			push(rr2++);
		}

		while (SZ(dq) and l2[dq.front()][0] + pi[0] < L) {
			dq.pop_front();
		}

		if (dq.size()) {
			auto zz = l2[dq.front()][0] + pi[0];
			if (zz >= L and zz <= R) {
				auto val = l2[dq.front()][1] + pi[1];
				//cout << val << endl;
				if (val > ans) {
					ans = val;
					exa = pi[2] + (l2[dq.front()][2] << CC);
				}
			}
		}
	}

	cout << __builtin_popcountll(exa) << endl;
	for (int i=0; i<N; i++) {
		if ((1<<i) & exa) {
			cout << i+1 << " \n"[i == N-1];
		}
	}

    return 0;
}

