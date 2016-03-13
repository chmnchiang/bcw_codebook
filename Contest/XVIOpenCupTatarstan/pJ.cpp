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

set<pii> st;

inline void del_point(int x) {
	auto it = st.upper_bound({x+1,0});
	if (it == st.begin()) return;
	it--;
	int a = it->F, b = it->S;
	if (a <= x and x <= b) {
		st.erase(it);
		if (a <= x-1) st.insert({a,x-1});
		if (x+1 <= b) st.insert({x+1,b});
	}
}
inline pii go(int x, int y) {
	auto it = st.upper_bound({x+1,0});
	int t = x;
	if (it != st.begin()) {
		it--;
		if (x <= it->S) t = it->S + 1;
	}

	int u = t + y - 1;
	it = st.lower_bound({t,t});
	if (it != st.end()) {
		if (it->F <= u) u = it->F - 1;
	}
	pii res(t,u);
	while (true) {
		it = st.lower_bound({t,u});
		if (it == st.begin()) break;
		it--;
		if (it->S == t-1) {
			t = it->F;
			st.erase(it);
		} else {
			break;
		}
	}
	while (true) {
		it = st.lower_bound({t,u});
		if (it == st.end()) break;
		if (it->F == u+1) {
			u = it->S;
			st.erase(it);
		} else {
			break;
		}
	}
	st.insert({t,u});

	return res;
}
int main() {
	IOS;
	int Q,x,y;
	cin >> Q;
	REP(_,Q) {
		cin >> x;
		if (x < 0) {
			del_point(-x);
		} else {
			cin >> y;
			pii res = go(x,y);
			cout << res.F << " " << res.S << "\n";
		}
		/*
		cout << "SET ";
		for (auto it:st)
			cout << it << " ";
		cout << endl;
		*/
	}

	return 0;
}

