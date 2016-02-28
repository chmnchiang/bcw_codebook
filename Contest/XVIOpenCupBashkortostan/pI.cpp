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
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

#define int long long

const int A = 487237;
const int B = 1011807;
const int M = 1<<20;
int f(int a) {
	return (A*a+B) % M;
}

int g(int a) {
	return __builtin_popcount(f(a)) & 1;
}

vector<pair<string, int>> vec;

void play() {
	int t;
	const int MAG = 25;
	static int s[MAG+3];
	cin >> t;

	for (int i=0; i<MAG; i++) {
		cout << 1 << endl;
		int nt; cin >> nt;
		if (nt == -1) return;
		s[i] = (nt > t);
		t = nt;
	}


	int fin = -1;
	for (int j=0; j<(1<<20); j++) {
		int q = j;
		for (int i=0; i<MAG; i++) {
			int fl = __builtin_popcount(q) & 1;
			if (s[i] != fl) {
				break;
			}
			if (i == MAG-1) {
				fin = q;
			}
			q = f(q);
		}

		if (fin != -1) break;
	}

	int q = fin;
	while (1) {
		q = f(q);
		int v = __builtin_popcount(q) & 1;
		if (v&1) {
			cout << t << endl;
			cin >> t;
		} else {
			cout << 1 << endl;
			cin >> t;
		}
		if (t == -1) return;
	}
}

int32_t main() {
	IOS;

	play();
	
	return 0;
}

