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
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
int N,R,C;
int dis[51][51][10005];
string mp[51],ip;
vector<pii> E[51][51];
queue<int> que;

inline void push(int x, int y, int i) {
	que.push(x);
	que.push(y);
	que.push(i);
}
inline void pop(int &x, int &y, int &i) {
	x = que.front(); que.pop();
	y = que.front(); que.pop();
	i = que.front(); que.pop();
}
inline int inr(int x, int y) {
	return 0 <= x and x < R and 0 <= y and y < C;
}
int main() {
	IOS;
	cin >> R >> C;
	REP(i,R) cin >> mp[i];
	cin >> ip;
	ip += "*";
	N = SZ(ip);
	REP(i,R) {
		REP(j,C) {
			REP(d,4) {
				int x = i + dir[d][0];
				int y = j + dir[d][1];
				int ok = 0;
				while (inr(x,y)) {
					if (mp[x][y] != mp[i][j]) {
						ok = 1;
						break;
					}
					x += dir[d][0];
					y += dir[d][1];
				}
				if (ok) E[i][j].PB({x,y});
			}
		}
	}

	REP(i,R) REP(j,C) REP(k,N+1) dis[i][j][k] = -1;

	dis[0][0][0] = 0;
	push(0,0,0);
	while (!que.empty()) {
		int x,y,p;
		pop(x,y,p);
		if (ip[p] == mp[x][y] and dis[x][y][p+1] == -1) {
			dis[x][y][p+1] = dis[x][y][p] + 1;
			push(x,y,p+1);
		}
		for (auto it:E[x][y]) {
			int nx = it.F;
			int ny = it.S;
			if (dis[nx][ny][p] == -1) {
				dis[nx][ny][p] = dis[x][y][p] + 1;
				push(nx,ny,p);
			}
		}
	}

	int ans = 1029384756;
	REP(i,R) REP(j,C) {
		if (dis[i][j][N] != -1) ans = min(ans, dis[i][j][N]);
	}
	assert(ans != 1029384756);
	cout << ans << endl;

	return 0;
}

