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

int Z[] = {5, 3, 4, 1, 2, 0};
int N;
string ip, op;

double f(int a) {
	if (a >= 3) return 1;
	if (a == 2) return 5.0/6.0;
	if (a == 1) return 0.5;
	return 0.0;
}

double calc(string s, int n, char tar) {
	int a = 0;
	int t1 = -1;
	for (int i=0; i<6; i++) {
		if (i == n) continue;
		if (i == Z[n] and s[i] == tar) return 1.0;
		if (s[i] == tar) {
			a++;
			t1 = i;
		}
	}

	if (a == 2) {
		if (s[Z[t1]] == tar)
			return 0.5;
		else return 1.0;
	}
	return f(a);
}

int main() {
	IOS;
	cin >> ip >> op;
	N = ip.length();

	double prob = 1;
	for (int i=0; i<N; i++) {
		char c1 = ip[i], c2 = op[i];
		string s; cin >> s;
		if (c1 == c2) continue;

		int t = 0;
		double tp = 0;
		for (int j=0; j<6; j++) {
			if (s[j] == c1) {
				t++;
				tp += calc(s, j, c2);
			}
		}
//		cout << t << endl;
//		cout << "tp = " << tp << endl;
		tp /= t;
		prob *= tp;
	}
	cout << fixed << setprecision(10) << prob << endl;


	return 0;
}

