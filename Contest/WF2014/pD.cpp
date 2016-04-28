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





int N;

int toi(string s) {
	int t = 0;
	for (auto c: s) {
		t |= (1<<(c-'a'));
	}
	return t;
}

vector<int> ip[30];
int ans[30][30];

void solve(int e) {
	for (int i=0; i<N; i++) ans[i][e] = -1;
	ans[e][e] = 0;

	int curf = 1<<e;
	bool us[30] = {};
	us[e] = 1;

	int nd = 1;
	//cout << "e = " << e << endl;
	while (true) {
		int xcurf = curf;
		for (int i=0; i<N; i++) {
			if (us[i]) continue;
			for (auto x: ip[i]) {
				if ((x|curf) == curf) {
					ans[i][e] = nd;
					xcurf |= (1<<i);
					us[i] = 1;
					//cout << i << endl;
				}
			}
		}
		nd++;
		if (curf == xcurf) break;
		curf = xcurf;
		//cout << "---" << endl;
	}
	return;
}

int main() {
	cin>>N;
	for (int i=0; i<N; i++) {
		int a; cin>>a;
		for (int j=0; j<a;j++) {
			string s; cin >> s;
			ip[i].PB(toi(s));
		}
	}

	for (int i=0; i<N; i++) {
		solve(i);
	}

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cout << ans[i][j] << " \n"[j == N-1];
		}
	}

	return 0;
}

