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

const int MX = 1111;
bool isp[MX];

static void pre() {
	fill(isp, isp+MX, 1);
	isp[0] = isp[1] = 0;
	for (int i=2; i<MX; i++) if (isp[i]) {
		for (int j=i+i; j<MX; j+=i) isp[j] = 0;
	}
}

void print(vector<int> v) {
	int n = SZ(v);
	for (int i=0; i<n; i++) {
		cout << v[i] << " \n"[i == n-1];
	}
	exit(0);
}

int main() {
	IOS;
	pre();

	int N; cin >> N;

	switch(N) {
		case 1:
			print({1});
		case 2:
			print({1, 2});
		case 3:
			print({3, 1, 2});
		case 4:
			print({3, 1, 2, 4});
		case 6:
			print({5, 1, 4, 2, 6, 3});
		default:
			cout << -1 << endl;
	}

	return 0;
}

