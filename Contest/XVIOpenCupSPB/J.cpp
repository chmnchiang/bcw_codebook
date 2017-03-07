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

char ip[10];

void rd() {
	cin >> ip;
	cin >> (ip+3);
	cin >> (ip+6);
}

void op() {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) cout << ip[i*3+j];
		if (i == 2) cout << endl;
		else cout << '\n';
	}
}

void play() {
	rd();
	if (ip[0] == 'x') exit(0);

	ip[4] = 'x';
	op();

	rd();
	int h1 = -1;
	for (int i=0; i<9; i++) {
		if (ip[i] == 'o') h1 = i;
	}

	int X2, X3, X4, X5, X6;
	if (h1 == 0) {
		X2 = 7, X3 = 1, X4 = 6, X5 = 2, X6 = 8;
	} else if (h1 == 6) {
		X2 = 1, X3 = 7, X4 = 0, X5 = 2, X6 = 8;
	} else if (h1 == 2 or h1 == 3 or h1 == 5) {
		X2 = 7, X3 = 1, X4 = 8, X5 = 0, X6 = 6;
	} else if (h1 == 1 or h1 == 7 or h1 == 8) {
		X2 = 3, X3 = 5, X4 = 6, X5 = 0, X6 = 2;
	} else assert(0);
	
	ip[X2] = 'x';
	op();

	rd();
	if (ip[X3] == '.') {
		ip[X3] = 'x';
		op();
		return;
	}

	ip[X4] = 'x';
	op();
	rd();

	if (ip[X5] == '.') ip[X5] = 'x';
	else ip[X6] = 'x';

	op();
	return;
	
}

int main() {
	IOS;

	while (true) {
		play();
	}

	return 0;
}

