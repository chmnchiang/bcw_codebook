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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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


using pii = pair<int, int>;
pii read_exp() {
	string s; cin >> s;
	assert(s == "x");
	cin >> s;
	int t = s == "<=" ? -1 : 1;
	cin >> s;
	int z = atoi(s.c_str());
	return {z, t};
}

const int LB = -32768;
const int UB = 32767;

bool _us[444444];
bool *us = _us + 222222;
vector<pii> ans;

int main() {
	FILEIO("hard");
	IOS;
	
	while (true) {
		int lb = LB, ub = UB;
		auto p = read_exp();

		if (p.S < 0) {
			ub = min(ub, p.F);
		} else lb = max(lb, p.F);

		string s; cin >> s;

		if (s == "&&") {
			p = read_exp();

			if (p.S < 0) {
				ub = min(ub, p.F);
			} else lb = max(lb, p.F);

			cin >> s;
		}

		for (int i=lb; i<=ub; i++) {
			us[i] = 1;
		}

		if (cin.eof()) break;
	}

	{
	int i = LB;

	while (i <= UB) {
		while (i <= UB and !us[i]) {
			i++;
		}
		if (i == UB+1) break;

		int j = i;
		while (j <= UB and us[j]) j++;

		ans.PB({i, j-1});

		i = j;
	}
	}

	int cnt = 0;
	for (int i=LB; i<=UB; i++) cnt += us[i];
	if (!cnt) {
		cout << "false" << endl;
		return 0;
	} else if (cnt == UB - LB+1) {
		cout << "true" << endl;
		return 0;
	}

	int n = SZ(ans);
	for (int i=0; i<n; i++) {
		pii p = ans[i];
		if (p.F == LB) cout << "x <= " << p.S;
		else if (p.S == UB) cout << "x >= " << p.F;
		else {
			cout << "x >= " << p.F << " && x <= " << p.S;
		}

		if (i == n-1) cout << endl;
		else cout << " ||\n";
	}

	return 0;
}

