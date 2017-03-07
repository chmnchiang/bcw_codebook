#pragma GCC optimize ("O2")
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

#define int long long

const int NORM = 0;
const int HARD = 1;
int LEN;
string S;
int mode;
int score, wave, max_chain, remain_move, level;
using Disc = pair<int, int>;
const Disc DOT = {-1, -1};
Disc board[10][10];
int err;

int get_remain(int lev) {
	if (mode == NORM) return max(5LL, 31LL - lev);
	else return 5;
}

inline int get_score(int w) {
	return (w*w*w*7 + w*w*72 - 73*w + 36)/6;
}

static void init() {
	score = 0;
	wave = 0;
	max_chain = 0;
	level = 1;
	remain_move = get_remain(level);
	err = 0;
}

Disc toDisc(char c) {
	if (c == '.') return DOT;
	if ('1' <= c and c <= '7') return {c - '1'+1, 0};
	if ('a' <= c and c <= 'g') return {c - 'a'+1, 1};
	if ('A' <= c and c <= 'G') return {c - 'A'+1, 2};
	assert(false);
}

char toChar(Disc d) {
	if (d == DOT) return '.';
	if (d.S == 0) return '1'+d.F-1;
	if (d.S == 1) return 'a'+d.F-1;
	if (d.S == 2) return 'A'+d.F-1;
	assert(false);
}

void print_board() {
	for (int i=7; i>=0; i--) {
		for (int j=0; j<7; j++) cout << toChar(board[j][i]);
		cout << endl;
	}
}

int id = 0;

char next_char() {
	if (id >= LEN) return 0;
	return S[id++];
}

void gravity(Disc *ds) {
	int j = 0;
	for (int i=0; i<8; i++) {
		if (ds[i] != DOT) {
			if (i != j) swap(ds[i], ds[j]);
			j++;
		}
	}
}

void gravity() {
	for (int i=0; i<7; i++) gravity(board[i]);
}

bool check_dead() {
	for (int i=0; i<7; i++) if (board[i][7] != DOT) return true;
	return false;
}

#define left lleefftt
#define right rriigghhtt
int up[10][10], down[10][10], left[10][10], right[10][10];

void make_lurd() {
	for (int i=0; i<7; i++) {
		for (int j=0; j<7; j++) {
			if (board[i][j] == DOT) up[i][j] = left[i][j] = 0;
			else {
				up[i][j] = (i ? up[i-1][j] : 0) + 1;
				left[i][j] = (j ? left[i][j-1] : 0) + 1;
			}
		}
	}

	for (int i=6; i>=0; i--) {
		for (int j=6; j>=0; j--) {
			if (board[i][j] == DOT) down[i][j] = right[i][j] = 0;
			else {
				down[i][j] = (i!=6 ? down[i+1][j] : 0) + 1;
				right[i][j] = (j!=6 ? right[i][j+1] : 0) + 1;
			}
		}
	}
}

const int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
inline bool inr(int x, int y) {
	return x >= 0 and x < 7 and y >= 0 and y < 7;
}

using pii = pair<int, int>;
vector<pii> exp_l;

int play() {

	wave = 0;

	char c = next_char();
	if (!c) {
		err = id+1;
		return -1;
	}
	Disc d = toDisc(c);

	c = next_char();
	if (!c) {
		err = id+1;
		return -1;
	}

	if (!(c >= '1' and c <= '7')) {
		err = id;
		return -1;
	}

	int col = c - '1';
	assert(board[col][7] == DOT);

	board[col][7] = d;
	gravity(board[col]);
	if (check_dead()) return 1;


	
	while (true) {
		make_lurd();

		exp_l.clear();

		int exp_n = 0;

		for (int i=0; i<7; i++) {
			for (int j=0; j<7; j++) {
				if (board[i][j] == DOT || board[i][j].S) continue;
				int hao = board[i][j].F;
				if (hao+1 == up[i][j] + down[i][j] || hao+1 == left[i][j] + right[i][j]) {
					board[i][j] = DOT;
					exp_n ++; 
					exp_l.PB({i, j});
				}
			}
		}
		for (auto x: exp_l) {
			int i = x.F, j = x.S;
			for (auto dd: dir) {
				int ni = dd[0] + i, nj = dd[1] + j;
				if (inr(ni, nj) && board[ni][nj] != DOT and board[ni][nj].S) {
					board[ni][nj].S --;
				}
			}
		}
		gravity();
		if (!exp_n) break;
		wave++;
		score += exp_n * get_score(wave);

	}
	remain_move --;
	if (!remain_move) {
		level++;
		remain_move = get_remain(level);
		score += mode == NORM ? 7000 : 17000;

		for (int i=0; i<7; i++) {
			for (int j=7; j>=1; j--) {
				board[i][j] = board[i][j-1];
			}

			c = next_char();
			if (!c) {
				err = id+1;
				return -1;
			}

			board[i][0] = toDisc(c);
		}

		if (check_dead()) return 1;

		while (true) {
			make_lurd();

			exp_l.clear();

			int exp_n = 0;

			for (int i=0; i<7; i++) {
				for (int j=0; j<7; j++) {
					if (board[i][j] == DOT || board[i][j].S) continue;
					int hao = board[i][j].F;
					if (hao+1 == up[i][j] + down[i][j] || hao+1 == left[i][j] + right[i][j]) {
						board[i][j] = DOT;
						exp_n ++; 
						exp_l.PB({i, j});
					}
				}
			}
			for (auto x: exp_l) {
				int i = x.F, j = x.S;
				for (auto dd: dir) {
					int ni = dd[0] + i, nj = dd[1] + j;
					if (inr(ni, nj) && board[ni][nj] != DOT and board[ni][nj].S) {
						board[ni][nj].S --;
					}
				}
			}
			gravity();
			if (!exp_n) break;
			wave++;
			score += exp_n * get_score(wave);

		}

	}

	max_chain = max(max_chain, wave);

	return 0;
}


int32_t main() {
	IOS;

	string typ; cin >> typ; cin >> typ;
	if (typ[0] == 'N') mode = NORM;
	else mode = HARD;

	for (int i=7; i>=0; i--) {
		string hao; cin >> hao;
		for (int j=0; j<7; j++) board[j][i] = toDisc(hao[j]);
	}

	cin >> S;
	LEN = SZ(S);

	init();

	while (true) {
		int res = play();
		if (res == -1) {
			if (err <= LEN) cout << "Error in game log at position " << err << endl;
			else cout << "Game log is not complete" << endl;
			exit(0);
		} else if (res == 1) {
			if (id != LEN) {
				cout << "Error in game log at position " << id+1 << endl;
			} else {
				cout << "Game is over!" << endl;
				cout << "Score: " << score << endl;
				cout << "Longest chain: " << max_chain << endl;
				cout << "Level reached: " << level << endl;
				print_board();
			}
			exit(0);
		} else if (id == LEN) {
			cout << "Score: " << score << endl;
			cout << "Longest chain: " << max_chain << endl;
			cout << "Level reached: " << level << endl;
			print_board();
			exit(0);
		}
	}


	return 0;
}


/*
   .......
   .......
   .......
   .......
   .......
   3A3.g..
   14e2e2e
   .......
   .......
   .......
   .e.....
   3A3.g..
   14e2e2e
   2e2e2e2
 */
