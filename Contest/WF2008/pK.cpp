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

const int MX = 105;
const int INF = 1029384756;
const int dir[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

struct Edge {
	int x,y,w;
};

int R,C,dis[5][MX][MX],inq[5][MX][MX];
int to[5][MX][MX],frm[5][MX][MX];
pii st,ed;
vector<Edge> E[MX][MX];

inline int getdir(pii sx, pii sy) {
	assert(abs(sx.F-sy.F) + abs(sx.S-sy.S) == 1);
	if (sx.F-1 == sy.F) return 0;
	if (sx.S+1 == sy.S) return 1;
	if (sx.F+1 == sy.F) return 2;
	return 3;
}
bool input() {
	cin >> R >> C >> st.F >> st.S >> ed.F >> ed.S;
	if (R + C + st.F + st.S + ed.F + ed.S == 0) return false;
	st.F--;
	st.S--;
	ed.F--;
	ed.S--;
	REP(i,R) REP(j,C) E[i][j].clear();
	REP(i,R) {
		int w;
		REP(j,C-1) {
			cin >> w;
			if (not w) continue;
			E[i][j].PB({i,j+1,w});
			E[i][j+1].PB({i,j,w});
		}
		if (i != R-1) {
			REP(j,C) {
				cin >> w;
				if (not w) continue;
				E[i][j].PB({i+1,j,w});
				E[i+1][j].PB({i,j,w});
			}
		}
	}
	return true;
}
int solve() {
	queue<int> que;
	REP(i,5) REP(j,R) REP(k,C) {
		dis[i][j][k] = INF;
		inq[i][j][k] = 0;
		to[i][j][k] = INF;
		frm[i][j][k] = INF;
	}
	REP(i,R) {
		REP(j,C) {
			for (auto it:E[i][j]) {
				int d = getdir(pii(i,j), pii(it.x,it.y));
				to[d][i][j] = it.w;
				frm[d][it.x][it.y] = it.w;
			}
		}
	}

	dis[4][st.F][st.S] = 0;
	inq[4][st.F][st.S] = 1;
	que.push(4);
	que.push(st.F);
	que.push(st.S);


	while (!que.empty()) {
		int d = que.front(); que.pop();
		int x = que.front(); que.pop();
		int y = que.front(); que.pop();
		inq[d][x][y] = 0;
		if (d == 4) {
			REP(nd,4) {
				if (to[nd][x][y] == INF) continue;
				int nx = x + dir[nd][0];
				int ny = y + dir[nd][1];
				int w = to[nd][x][y];
				//cout << x << " " << y << " " << dis[d][x][y] << " --> " << nd << " " << nx << " " << ny << " " << w << endl;
				if (dis[nd][nx][ny] > dis[d][x][y] + 2 * w) {
					dis[nd][nx][ny] = dis[d][x][y] + 2 * w;
					if (!inq[nd][nx][ny]) {
						que.push(nd);
						que.push(nx);
						que.push(ny);
						inq[nd][nx][ny] = 1;
					}
				}
				if (dis[4][nx][ny] > dis[d][x][y] + 2 * w) {
					dis[4][nx][ny] = dis[d][x][y] + 2 * w;
					if (!inq[4][nx][ny]) {
						que.push(4);
						que.push(nx);
						que.push(ny);
						inq[4][nx][ny] = 1;
					}
				}
			}
		} else {
			if (frm[d][x][y] != INF) {
				if (dis[4][x][y] > dis[d][x][y] + frm[d][x][y]) {
					dis[4][x][y] = dis[d][x][y] + frm[d][x][y];
					if (!inq[4][x][y]) {
						que.push(4);
						que.push(x);
						que.push(y);
						inq[4][x][y] = 1;
					}
				}
			}
			if (to[d][x][y] != INF) {
				int nx = x + dir[d][0];
				int ny = y + dir[d][1];
				if (dis[d][nx][ny] > dis[d][x][y] + to[d][x][y]) {
					dis[d][nx][ny] = dis[d][x][y] + to[d][x][y];
					if (!inq[d][nx][ny]) {
						que.push(d);
						que.push(nx);
						que.push(ny);
						inq[d][nx][ny] = 1;
					}
				}
			}
		}
	}

	return dis[4][ed.F][ed.S];
}
int main() {
	IOS;
	int cas = 0;
	while (input()) {
		cas++;
		int res = solve();
		if (res == INF) {
			cout << "Case " << cas << ": Impossible" << endl;
		} else {
			cout << "Case " << cas << ": " << res << endl;
		}
	}


    return 0;
}

