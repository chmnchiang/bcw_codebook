#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

const int MX = 200005;

int N, K, Q, bye[MX];
set<pii> st;
vector<pii> seg;

int main() {
    IOS;
	while (cin >> N >> K) {
		cin >> Q;
		FZ(bye);
		seg.clear();
		st.clear();
		st.insert({0, 0});
		st.insert({N, 0});
		while (Q--) {
			int l, r, c;
			cin >> l >> r >> c;
			l--; r--;

			auto iter = st.lower_bound({l+1, -1});
			iter--;
			vector<set<pii>::iterator> vec;
			int fstL = iter->F;
			int fstC = iter->S;
			int lstC = 0;;
			while (iter->F <= r) {
				vec.PB(iter);
				auto nxt = iter;
				nxt++;

				int nl = max(iter->F, l);
				int nr = min(r, nxt->F - 1);

				if (iter->S != c-1) {
					seg.PB({nl, nr});
				}
				lstC = iter->S;;
				iter = nxt;
			}
			for (auto it : vec) {
				st.erase(it);
			}
			st.insert({l, c});
			if (fstL < l) {
				st.insert({fstL, fstC});
			}
			iter = st.lower_bound({l, c+1});
			if (iter->F > r+1) {
				st.insert({r+1, lstC});
			}
			/*
			cout << "==== after oper ====" << endl;
			for (auto it : st) cout << it << endl;
			*/
		}
		/*
		for (auto it : seg) {
			cout << "bye " << it << endl;
		}
		*/
		vector<pii> vec;
		for (auto it : st) {
			vec.PB(it);
		}
		for (int i=0; i<SZ(vec)-1; i++) {
			if (vec[i].S != K) {
				seg.PB({vec[i].F, vec[i+1].F-1});
			}
		}
		for (auto it : seg) {
			bye[it.F]++;
			bye[it.S+1]--;
		}
		int ans = 0;
		for (int i=0; i<N; i++) {
			if (i) bye[i] += bye[i-1];
			if (!bye[i]) ans++;
		}
		cout << ans << endl;
	}

    return 0;
}

