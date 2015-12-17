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
// Let's Fight!

const int MXN = 305;
struct Rule {
	int left;
	vector<int> vec;
};

int N,Q,A,S,T;
int canStop[MXN];
int canStopS[MXN];
int canCycle[MXN];
int canCycleS[MXN];
Rule allRule[MXN];
vector<Rule> rule[MXN];

int vst[MXN], ons[MXN];

vector<int> split(string str) {
	vector<int> res;
	for (auto ch : str) {
		if ('A' <= ch && ch <= 'Z') {
			res.PB(ch-'A');
		}
	}
	return res;
}

void predo1() {
	FZ(canStop);
	for (int t=0; t<300; t++) {
		for (int i=0; i<N; i++) {
			int l = allRule[i].left;
			if (l == T) continue;
			if (canStop[l]) continue;
			int tmp = 1;
			for (auto it:allRule[i].vec) {
				if (it == T || !canStop[it]) {
					tmp = 0;
					break;
				}
			}
			canStop[l] = tmp;
		}
	}
}

void predo2() {
	FZ(canStopS);
	if (!canStop[S]) return;
	canStopS[S] = 1;
	for (int t=0; t<300; t++) {
		for (int i=0; i<N; i++) {
			int l = allRule[i].left;
			if (l == T) continue;
			if (canStopS[l]) continue;
			int ss = 0;
			int fail = 0;
			for (auto it:allRule[i].vec) {
				if (!canStop[it]) fail = 1;
				if (canStopS[it]) ss++;
			}
			if (!fail && ss >= 1) canStopS[l] = 1;
		}
	}
}

bool DFS(int u) {
	if (ons[u]) return true;
	if (vst[u]) return false;
	ons[u] = 1;
	//vst[u] = 1;
	for (auto r : rule[u]) {
		for (auto v : r.vec) {
			if (v == T) break;
			if (DFS(v)) return true;
			if (!canStop[v]) break;
		}
	}
	ons[u] = 0;
	return false;
}

void predo3() {
	FZ(canCycle);
	for (int i=0; i<26; i++) {
		FZ(vst); FZ(ons);
		if (i == T) continue;
		canCycle[i] = DFS(i);
	}
}

void predo4() {
	FZ(canCycleS);
	if (canCycle[S]) canCycleS[S] = 1;
	for (auto r:rule[S]) {
		for (auto v:r.vec) {
			if (v==T) break;
			if (canCycle[v]) canCycleS[S] = 1;
			if (!canStop[v]) break;
		}
	}
	for (int t=0; t<300; t++) {
		for (int i=0; i<N; i++) {
			int l = allRule[i].left;
			if (l == T) continue;
			if (canCycleS[l]) continue;
			int ss = 0;
			for (auto it : allRule[i].vec) {
				if (it == T) break;
				if (ss >= 1 && canCycle[it]) {
					canCycleS[l] = 1;
					break;
				}
				if (canCycleS[it]) {
					canCycleS[l] = 1;
					break;
				}
				if (canStopS[it]) ss++;
				if (!canStop[it]) break;
			}
		}
	}
}

void solve() {
	predo1();
	predo2();
	predo3();
	predo4();

	int ans = canStopS[A] || canCycleS[A];
	if (!ans) cout << "YES" << endl;
	else cout << "NO" << endl;
}


int main() {
	string str;
	FILEIO("formal");
	IOS;
	cin >> str;
	A = str[0]-'A';
	cin >> N;
	getline(cin, str);
	for (int i=0; i<N; i++) {
		getline(cin, str);
		int id = str[0] - 'A';
		Rule tmp;
		tmp.vec = split(str.substr(1));
		tmp.left = id;

		allRule[i] = tmp;
		rule[id].PB(tmp);
	}
	cin >> Q;
	while (Q--) {
		cin >> str;
		S = str[0]-'A';
		cin >> str;
		T = str[0]-'A';
		solve();
	}

	return 0;
}
