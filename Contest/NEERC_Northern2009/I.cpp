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


typedef pair<int,int> pii;
const int MX = 1<<10;

int D,H,W;

int dp[10][10][MX];
int popcount[MX];
pii split[10][10][MX];
pii trans[10][10][MX];
string digit[10][10];

int go(int x, int y, int s) {
	if (popcount[s] == 1) {
		return 1;
	}
	int &res = dp[x][y][s];
	if (res != -1) return res;

	res = 1029384756;
	REP(i,H) REP(j,W) {
		int as = split[i][j][s].F;
		int bs = split[i][j][s].S;
		if (as == 0 or bs == 0) continue;
		int cost = abs(x-i) + abs(y-j) + max(go(i,j,as), go(i,j,bs));
		if (cost < res) {
			res = cost;
			trans[x][y][s] = pii(i,j);
		}
	}
	return res;
}

string gen(int x, int y, int s) {
	string res;
	if (popcount[s] == 1) {
		res += '0';
		REP(i,D) if (s & (1<<i)) res[0] += i;
		return res;
	}
	int nx = trans[x][y][s].F;
	int ny = trans[x][y][s].S;

	int tx = x;
	int ty = y;
	while (tx < nx) {
		res += "D";
		tx++;
	}
	while (tx > nx) {
		res += "U";
		tx--;
	}
	while (ty < ny) {
		res += "R";
		ty++;
	}	

	while (ty > ny) {
		res += "L";
		ty--;
	}

	res += "(" + gen(nx,ny,split[nx][ny][s].F) + ":" + gen(nx,ny,split[nx][ny][s].S) + ")";

	return res;
}
int main() {
	FILEIO("image");
	IOS;
	cin >> D >> H >> W;
	REP(i,D) {
		REP(j,H) cin >> digit[i][j];
	}

	REP(x,H) REP(y,W) {
		REP(i,1<<D) {
			int as = 0;
			int bs = 0;
			REP(j,D) if (i & (1<<j)) {
				if (digit[j][x][y] == 'W') as |= 1 << j;
				else bs |= 1 << j;
			}
			split[x][y][i] = pii(as, bs);
		}
	}

	REP(i,MX) popcount[i] = __builtin_popcount(i);
	FMO(dp);
	int minCost = go(0,0,(1<<D)-1);
	cerr << minCost << endl;
	string ans = gen(0,0,(1<<D)-1);
	cout << ans << endl;

	return 0;
}
