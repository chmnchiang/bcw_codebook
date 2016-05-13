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


int ans[11][11];

int main() {
	IOS;
	memset(ans,-1,sizeof(ans));
	ans[7][2] = 149;
	ans[6][6] = 16;
	ans[2][2] = 1;
	ans[9][4] = 166;
	ans[2][8] = 11;
	ans[9][6] = 156;
	ans[4][4] = 2;
	ans[8][8] = 3;
	ans[8][2] = 13;
	ans[7][4] = 46;
	ans[4][6] = 12;
	ans[5][6] = 112;
	ans[6][8] = 79;
	ans[3][6] = 88;
	ans[3][2] = 5;
	ans[4][8] = 115;
	ans[6][4] = 6;
	ans[1][6] = 4;
	ans[1][2] = 17;
	ans[8][6] = 116;
	ans[7][8] = 159;
	ans[5][4] = 102;
	ans[4][2] = 105;
	ans[1][1] = 0;
	ans[2][6] = 8;
	ans[8][4] = 106;
	ans[9][8] = 63;
	ans[2][4] = 18;
	ans[9][2] = 53;
	ans[5][2] = 9;
	ans[3][4] = 78;
	ans[5][8] = 19;
	ans[7][6] = 56;
	ans[6][2] = 89;
	ans[1][8] = 7;
	ans[3][8] = 15;
	ans[1][4] = 10;
	int A,B;
	cin >> A >> B;
	cout << ans[A][B] << endl;

	return 0;
}

