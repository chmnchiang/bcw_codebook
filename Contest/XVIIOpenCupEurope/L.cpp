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


const int MX = 444;
int N;
int ip[MX][3];
int fid[10];
int typ[MX];

using pii = pair<int, int>;
vector<pair<pii, pii>> ans;

void push(int a, int b, int c, int d) {
	ans.PB({{a, b}, {c, d}});
}

int main() {
	IOS;

	cin >> N;

	for (int j=0; j<3; j++)
		for (int i=0; i<N; i++) {
			cin >> ip[i][j];
		}

	for (int i=0; i<4; i++) fid[i] = -1;

	int cnt = 0;
	for (int i=0; i<N; i++) {
		int a = ip[i][0] ^ ip[i][1];
		int b = ip[i][0] ^ ip[i][2];


		int t = a*2 + b;
		typ[i] = t;

		if (fid[t] == -1) {
			fid[t] = i;
			if (t) cnt++;
		}
	}

	if (cnt == 3) {
		cout << -1 << endl;
		return 0;
	}

	assert(cnt == 2);

	if (fid[0] != -1) {
		int i = fid[0];
		push(i, !ip[i][0], i, ip[i][0]);
	}

	for (int i=0; i<N; i++) {
		int t = typ[i];
		int f = fid[t];
		if (f == i) continue;

		push(f, ip[f][0], i, ip[i][0]);
		push(f, !ip[f][0], i, !ip[i][0]);
	}

	if (fid[1] == -1) {
		// 2 3
		int i2 = fid[2], i3 = fid[3];
		push(i2, !ip[i2][0], i3, !ip[i3][0]);
	} else if (fid[2] == -1) {
		int i1 = fid[1], i3 = fid[3];
		push(i1, !ip[i1][0], i3, !ip[i3][0]);
	} else {
		int i1 = fid[1], i2 = fid[2];
		push(i1, !ip[i1][0], i2, ip[i2][0]);
	}

	cout << SZ(ans) << endl;
	for (auto p: ans) {
		cout << (p.F.S ? "" : "!")  << 'x' << p.F.F+1 << " -> " <<
			(p.S.S ? "" : "!") << 'x' << p.S.F+1 << endl;
	}


	return 0;
}

