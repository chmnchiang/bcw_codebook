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

const int MX = 333;
int N;
int one[MX];
vector<vector<int>> ip;
vector<vector<int>> op;

int realp[MX];
bool check(int id, int pos) {
	for (int i=0; i<pos; i++) {
		realp[i] = ip[id][i] + 1;
	}
	realp[pos] = 1;
	for (int i=pos; i<N; i++) {
		realp[i+1] = ip[id][i] + 1;
	}

	for (int i=0; i<N; i++) {
		int t = realp[i];
		for (int j=0; j<i; j++) {
			op[i][j] = realp[j] - (realp[j] > t);
		}
		for (int j=i+1; j<N; j++) {
			op[i][j-1] = realp[j] - (realp[j] > t);
		}
	}
	sort(ALL(op));
	if (ip == op) {
		for (int i=0; i<N; i++) {
			cout << realp[i] << ' ';
		}
		cout << endl;
		return true;
	}
	return false;
}

int main() {
	IOS;
	FILEIO("permutation");

	cin >> N;
	ip.resize(N);
	op.resize(N);
	for (int i=0; i<N; i++) {
		ip[i].resize(N-1);
		op[i].resize(N-1);
		for (int j=0; j<N-1; j++) {
			cin >> ip[i][j];
			if (ip[i][j] == 1) one[j] ++;
		}
	}
	sort(ALL(ip));

	int mv = -1, mi = -1;
	for (int i=0; i<N-1; i++) {
		if (one[i] > mv) {
			mv = one[i];
			mi = i;
		}
	}

	for (int i=0; i<N; i++) {
		for (int j=-1; j<=1; j++) {
			int t = j+mi;
			if (t < 0 or t >= N) continue;
			if (check(i, t)) goto done;
		}
	}
done:

	return 0;
}

