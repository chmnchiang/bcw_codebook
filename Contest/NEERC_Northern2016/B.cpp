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


char B = 'G';
char G = 'B';

void gg() {
	cout << "Impossible" << endl;
	exit(0);
}

void cc(char c, int t) {
	for (int i=0; i<t; i++) cout << c;
}

bool ook(int x, int m, int a, vector<int> &vec) {
	if (a == 0 and m != x) return false;
	if (m < a) return false;
	if (m > x-a) return false;
	for (int i=0; i<a; i++) vec.PB(2);
	for (int i=0; i<m-a; i++) vec.PB(1);
	int d = x - (a*2+(m-a));
	if (d < 0) return false;
	vec[0] += d;
	return true;
}

bool ok(int n, int a, int a1, int x, int y) {
	int a2 = a - a1;
	if (a1 < 0 or a1*2 > x or a2 < 0 or a2*2 > y) return false;
	
	vector<int> ch;
	if (a1 == 0) ch.PB(x);
	else ch.PB(a1), ch.PB(x-a1);

	if (a2 == 0) ch.PB(y);
	else ch.PB(a2), ch.PB(y-a2);
	for (auto m: ch) {
		vector<int> v1, v2;
		if (ook(x, m, a1, v1) && ook(y, m, a2, v2)) {
			for (int i=0; i<m; i++) {
				cc(G, v1[i]);
				cc(B, v2[i]);
			}
			exit(0);
		}
	}
	return false;
}

int main() {
	IOS;
	FILEIO("boysgirls");

	int n, x, y; cin >> n >> x >> y;
	if (x < y) {
		swap(x, y);
		swap(B, G);
	}
	int z = x+y-n;
	if (z < 0) {
		gg();
	}
	if (z%2) {
		gg();
	}
	z /= 2;
	x -= z; y -= z;

	if (!y) {
		if (x != n || z) gg();
		for (int i=0; i<x; i++) cout << G;
		cout << endl;
		return 0;
	}

	for (int i=0; i<=z; i++) {
		if (ok(n, z, i, x, y)) return 0;
	}
	gg();


	return 0;
}

