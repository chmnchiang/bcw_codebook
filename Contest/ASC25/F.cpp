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
string S;
const int INF = 1029384756;
using Arr = array<int, 4>;

int id;
Arr go() {
	char c = S[id];
	if (c == 'g') {
		id++;
		return {0, 1, 1, -INF};
	}
	id++;
	Arr ret = {-INF, -INF, -INF, -INF};
	Arr a1 = go(), a2 = go();
	if (c == 'S') {
		for (int i=0; i<4; i++) {
			int h = (i&2)/2, e = i&1;
			ret[i] = max(ret[i], a1[h*2+0] + a2[0*2+e]);
			ret[i] = max(ret[i], a1[h*2+1] + a2[1*2+e] - 1);
		}
	} else {
		for (int i=0; i<4; i++) {
			int z = __builtin_popcount(i);
			ret[i] = max(ret[i], a1[i] + a2[i] - z);
		}
	}
	return ret;
}

int main() {
	FILEIO("independent");
	IOS;
	cin >> S;
	N = SZ(S);
	auto p = go();
	cout << max(p[0], max(p[1], max(p[2], p[3]))) << endl;


	return 0;
}
