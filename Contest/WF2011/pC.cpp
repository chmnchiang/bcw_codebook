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

#define loop(i, a, b) for (auto (i)=(a); (i) < (b); ((i) += ((a) < (b) ? 1 : -1)))

const int MX = 1000;
const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int _H, _W;
int H, W;
int N;
int mp[MX][MX];

inline bool inrange(int x, int y) {
	return (x >= 0) and (x < H) and (y >= 0) and (y < W);
}

inline int getID(int x, int y) {
	return x*W+y;
}

int djs[MX*MX];
void djsInit() {
	loop (i, 0, N) {
		djs[i] = i;
	}
}

int ffa(int a) {
	return (djs[a] == a ? a : (djs[a] = ffa(djs[a])));
}

void join(int a, int b) {
	int fa = ffa(a), fb = ffa(b);
	djs[fa] = fb;
}

int tohex(char c) {
	if (isdigit(c)) return c-'0';
	return c-'a'+10;
}

set<int> cans;

void dfs(int x, int y) {
	mp[x][y] = 2;
	for (auto d: dir) {
		int nx=x+d[0], ny=y+d[1];
		if (not inrange(nx, ny)) continue;
		if (mp[nx][ny] == 1) dfs(nx, ny);
		if (mp[nx][ny] == 0) {
			cans.insert(ffa(getID(nx, ny)));
		}
	}
}

int main() {
	IOS;
	map<int,char> itc;
	itc[1] = 'A';
	itc[3] = 'J';
	itc[5] = 'D';
	itc[4] = 'S';
	itc[0] = 'W';
	itc[2] = 'K';
	int cas=0;

	while(1) {
		cin>>_H>>_W;
		if (!_H and !_W) break;
		H = _H+2;
		W = _W*4+2;
		N = H*W+5;
		loop(i, 0, H+2) {
			loop (j, 0, W+2) mp[i][j] = 0;
		}
		loop (i, 0, _H) {
			string s;cin>>s;
			int ni = i+1;
			loop (j, 0, _W) {
				int c = tohex(s[j]);
				int nj = j*4+1;
				loop (k, 0, 4) {
					if ((1<<(4-k-1)) & c) mp[ni][nj+k] = 1;
				}
			}
		}
		djsInit();
		loop (i, 0, H) {
			loop (j, 0, W) {
				if (mp[i][j]) continue;
				for (auto d: dir) {
					int ni = i+d[0], nj = j+d[1];
					if (inrange(ni, nj) and mp[ni][nj] == 0) {
						join(getID(i, j), getID(ni, nj));
					}
				}
			}
		}

		vector<char> ans;
		loop (i, 0, H) {
			loop (j, 0, W) {
				if (mp[i][j] == 1) {
					cans.clear();
					dfs(i, j);
					ans.PB(itc[SZ(cans)-1]);
				}
			}
		}
		sort(ALL(ans));
		cas++;
		cout << "Case " << cas << ": ";
		for (auto c: ans) {
			cout << c;
		}
		cout << endl;
	}



	return 0;
}

