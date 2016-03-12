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

struct Coord {
	int x,y,z,f;
	friend ostream& operator << (ostream &s, const Coord &he) {
		s << "{ " << he.x << "," << he.y << "," << he.z << " ";
		if (he.f == 0) s << "+x";
		if (he.f == 1) s << "-x";
		if (he.f == 2) s << "+y";
		if (he.f == 3) s << "-y";
		if (he.f == 4) s << "+z";
		if (he.f == 5) s << "-z";
		s << " }";
		return s;
	}
};

const int dir[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

int X,Y,Z,used[26][26][26];
Coord st,ed;
Coord trans[6][8],fl[6][8][4];

int getf(string s) {
	if (s == "+x") return 0;
	if (s == "-x") return 1;
	if (s == "+y") return 2;
	if (s == "-y") return 3;
	if (s == "+z") return 4;
	if (s == "-z") return 5;
	assert(false);
}
void predo() {
	REP(i,6) {
		int x = dir[i][0];
		int y = dir[i][1];
		int z = dir[i][2];
		int p = 0;
		{
			REP(nd,6) {
				if (i == nd or (i^1) == nd) continue;
				fl[i][p][0] = {0,0,0,i};
				fl[i][p][1] = {x,y,z,i};
				int tx = x, ty = y, tz = z;
				REP1(j,2,3) {
					tx += dir[nd][0];
					ty += dir[nd][1];
					tz += dir[nd][2];
					fl[i][p][j] = {tx,ty,tz,nd};
				}
				tx += dir[nd][0];
				ty += dir[nd][1];
				tz += dir[nd][2];
				trans[i][p] = {tx,ty,tz,nd};
				p++;
			}
		}
		{
			REP(nd,6) {
				if (i == nd or (i^1) == nd) continue;
				fl[i][p][0] = {0,0,0,i};
				fl[i][p][1] = {x,y,z,i};
				int tx = x + dir[i][0];
				int ty = y + dir[i][1];
				int tz = z + dir[i][2];
				fl[i][p][2] = {tx,ty,tz,i};
				tx += dir[nd][0];
				ty += dir[nd][1];
				tz += dir[nd][2];
				fl[i][p][3] = {tx,ty,tz,nd};
				tx += dir[nd][0];
				ty += dir[nd][1];
				tz += dir[nd][2];
				trans[i][p] = {tx,ty,tz,nd};
				p++;
			}
		}

	}
}
bool inrange(int x, int y, int z) {
	return (1 <= x and x <= X) and (1 <= y and y <= Y) and (1 <= z and z <= Z);
}
bool DFS(Coord c, int pos, int lim) {
	//cout << c << endl;
	if (pos >= lim) {
		if (c.f == 0) c.x--;
		if (c.f == 1) c.x++;
		if (c.f == 2) c.y--;
		if (c.f == 3) c.y++;
		if (c.f == 4) c.z--;
		if (c.f == 5) c.z++;
		return tie(c.x,c.y,c.z,c.f) == tie(ed.x,ed.y,ed.z,ed.f);
	}
	REP(i,8) {
		int ok = 1;
		int f = c.f;
		int x = c.x;
		int y = c.y;
		int z = c.z;
//		cout << "CUR " << c << endl;
		REP(j,4) {
			int nx = fl[f][i][j].x + x;
			int ny = fl[f][i][j].y + y;
			int nz = fl[f][i][j].z + z;
			if (used[nx][ny][nz] or !inrange(nx,ny,nz)) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			REP(j,4) {
				int nx = fl[f][i][j].x + x;
				int ny = fl[f][i][j].y + y;
				int nz = fl[f][i][j].z + z;
				used[nx][ny][nz] = 1;
//				cout << fl[f][i][j] << endl;
			}
//			cout << "USED " << i << endl;
			Coord nxt = trans[f][i];
			nxt.x += c.x;
			nxt.y += c.y;
			nxt.z += c.z;
			if (DFS(nxt, pos+1, lim)) return true;
			REP(j,4) {
				int nx = fl[f][i][j].x + x;
				int ny = fl[f][i][j].y + y;
				int nz = fl[f][i][j].z + z;
				used[nx][ny][nz] = 0;
			}
		}
	}
	return false;
}
int solve() {
	
	/*
	REP(i,8) {
		REP(j,4) cout << fl[5][i][j] << " ";
		cout << trans[5][i];
		cout << endl;
	}
	exit(0);
	DFS(st,0,2);
	return -1;
	*/
	REP1(i,1,6) {
		if (DFS(st, 0, i)) {
			return i;
		}
	}
	return -1;
}
int main() {
	predo();
	IOS;
	int cas = 0;
	while (cin >> X) {
		if (not X) break;
		string f1,f2;
		cin >> Y >> Z >> st.x >> st.y >> st.z >> f1 >> ed.x >> ed.y >> ed.z >> f2;
		st.f = getf(f1);
		ed.f = getf(f2);
		FZ(used);

		int ans = solve();

		cas++;
		if (ans == -1) {
			cout << "Case " << cas << ": Impossible" << endl;
		} else {
			cout << "Case " << cas << ": " << ans << endl;
		}
	}


    return 0;
}

