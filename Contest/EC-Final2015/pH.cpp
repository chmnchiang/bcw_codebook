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


int ban[14];
int ans;
string ip[14];
int state[3];
int stCnt[3];
//vector<string> gVec[3];
struct Hand {
	int lv;
	vector<int> vec;
	bool operator > (const Hand &he) const {
		return tie(lv,vec) > tie(he.lv,he.vec);
	}
};
Hand hh[3];
Hand h3[1<<14],h5[1<<14];
int chrank[256];
int sumap[256];

void input() {
	REP(i,14) cin >> ip[i];
}
void predo() {
	REP1(i,'2','9') chrank[i] = i-'0';
	chrank['T'] = 10;
	chrank['J'] = 11;
	chrank['Q'] = 12;
	chrank['K'] = 13;
	chrank['A'] = 14;
	sumap['C'] = 0;
	sumap['D'] = 1;
	sumap['H'] = 2;
	sumap['S'] = 3;
}
inline int get_rank(const string &s) {
	return chrank[(int)s[0]];
}
inline int get_suit(const string &s) {
	return sumap[(int)s[1]];
}
Hand verify3(const vector<string> &vec) {
	assert(SZ(vec) == 3);
	Hand res;
	if (vec[0][0] == vec[1][0] and vec[1][0] == vec[2][0]) {
		res.lv = 4;
		res.vec.PB(get_rank(vec[0]));
	} else if (vec[0][0] == vec[1][0]) {
		res.lv = 2;
		res.vec.PB(get_rank(vec[0]));
		res.vec.PB(get_rank(vec[2]));
		res.vec.PB(-1);
		res.vec.PB(-2);
	} else if (vec[1][0] == vec[2][0]) {
		res.lv = 2;
		res.vec.PB(get_rank(vec[1]));
		res.vec.PB(get_rank(vec[0]));
		res.vec.PB(-1);
		res.vec.PB(-2);
	} else {
		res.lv = 1;
		REP(i,3) res.vec.PB(get_rank(vec[i]));
		sort(ALL(res.vec),greater<int>());
	}
	return res;
}

int suit[4],rk[15];
Hand verify5(const vector<string> &vec) {
	assert(SZ(vec) == 5);
	Hand res;
	memset(suit,0,sizeof(suit));
	memset(rk,0,sizeof(rk));
	vector<int> r;
	REP(i,5) {
		r.PB(get_rank(vec[i]));
		rk[get_rank(vec[i])]++;
		suit[get_suit(vec[i])]++; 
	}
	sort(ALL(r));
	int fu = 0;
	REP(i,4) fu |= suit[i] == 5;
	// Royal Flush
	if (fu and r[0]==10 and r[1]==11 and r[2]==12 and r[3]==13 and r[4]==14) {
		res.lv = 10;
		return res;
	}

	// Straight Flush
	if (fu and r[0] == r[1]-1 and r[1] == r[2]-1 and r[2] == r[3]-1 and r[3] == r[4]-1) {
		res.lv = 9;
		res.vec.PB(r[4]);
		return res;
	}
	if (fu and r[0] == 2 and r[1] == 3 and r[2] == 4 and r[3] == 5 and r[4] == 14) {
		res.lv = 9;
		res.vec.PB(r[3]);
		return res;
	}

	// Four of a Kind
	if (r[0] == r[1] and r[1] == r[2] and r[2] == r[3]) {
		res.lv = 8;
		res.vec.PB(r[0]);
		return res;
	}
	if (r[1] == r[2] and r[2] == r[3] and r[3] == r[4]) {
		res.lv = 8;
		res.vec.PB(r[1]);
		return res;
	}

	// Full House
	int three,two;
	three = two = 0;
	for (auto i:r) {
		if (rk[i] == 3) three = i;
		if (rk[i] == 2) two = i;
	}
	if (three and two) {
		res.lv = 7;
		return res;
	}

	// Flush
	if (fu) {
		res.lv = 6;
		REP(i,5) res.vec.PB(get_rank(vec[i]));
		sort(ALL(res.vec),greater<int>());
		return res;
	}

	// Straight
	if (r[0]==10 and r[1]==11 and r[2]==12 and r[3]==13 and r[4]==14) {
		res.lv = 5;
		res.vec.PB(14);
		return res;
	}

	if (r[0] == r[1]-1 and r[1] == r[2]-1 and r[2] == r[3]-1 and r[3] == r[4]-1) {
		res.lv = 5;
		res.vec.PB(r[4]);
		return res;
	}

	if (r[0] == 2 and r[1] == 3 and r[2] == 4 and r[3] == 5 and r[4] == 14) {
		res.lv = 5;
		res.vec.PB(r[3]);
		return res;
	}

	// Three of a Kind
	if (three) {
		res.lv = 4;
		res.vec.PB(three);
		return res;
	}

	// Two Pair
	r.resize(unique(ALL(r))-begin(r));
	int one;
	vector<int> pp;
	for (auto i:r) {
		if (rk[i] == 2) pp.PB(i);
		if (rk[i] == 1) one = i;
	}
	if (SZ(pp) == 2) {
		res.lv = 3;
		if (pp[0] < pp[1]) swap(pp[0], pp[1]);
		res.vec.PB(pp[0]);
		res.vec.PB(pp[1]);
		res.vec.PB(one);
		return res;
	}

	// Pair

	if (SZ(pp) == 1) {
		vector<int> v1;
		for (auto i:r) if (rk[i] == 1) v1.PB(i);
		reverse(ALL(v1));
		res.lv = 2;
		res.vec.PB(pp[0]);
		res.vec.insert(end(res.vec),ALL(v1));
		return res;
	}

	// High Card
	res.lv = 1;
	for (auto i:r) if (rk[i] == 1) res.vec.PB(i);
	reverse(ALL(res.vec));

	return res;
}

int counter;
inline void calc() {
	counter++;
	static Hand h[3];
	h[0] = h3[state[0]];
	h[1] = h5[state[1]];
	h[2] = h5[state[2]];
	int sc = 0;
	if (h[0].lv == 2) {
		sc += h[0].vec[0]-5;
	} else if (h[0].lv == 4) {
		sc += h[0].vec[0] + 8;
	}

	if (h[1].lv == 10) sc += 50;
	if (h[1].lv == 9) sc += 30;
	if (h[1].lv == 8) sc += 20;
	if (h[1].lv == 7) sc += 12;
	if (h[1].lv == 6) sc += 8;
	if (h[1].lv == 5) sc += 4;
	if (h[1].lv == 4) sc += 2;

	if (h[2].lv == 10) sc += 25;
	if (h[2].lv == 9) sc += 15;
	if (h[2].lv == 8) sc += 10;
	if (h[2].lv == 7) sc += 6;
	if (h[2].lv == 6) sc += 4;
	if (h[2].lv == 5) sc += 2;

	if (sc <= ans) return;

	if (h[0] > h[1]) return;
	if (h[1] > h[2]) return;

	ans = max(ans, sc);
}
void DFS(int i) {
	if (i >= 14) {
		calc();
		return;
	}
	if (ban[i]) DFS(i+1);
	else {
		REP(j,3) {
			if ((j == 0 and stCnt[j] < 3) or (j != 0 and stCnt[j] < 5)) {
				state[j] |= 1<<i;
				stCnt[j]++;
				if (!(j <= 1 and stCnt[0] == 3 and stCnt[1] == 5 and h3[state[0]] > h5[state[1]]) and
					!(j >= 1 and stCnt[1] == 5 and stCnt[2] == 5 and h5[state[1]] > h5[state[2]]))
				DFS(i+1);
				state[j] -= 1<<i;
				stCnt[j]--;
			}
		}
	}
}
void solve() {
	sort(ALL(ip),[](string a, string b) { return get_rank(a) < get_rank(b); });

	vector<string> vec;
	REP1(i,0,13) REP1(j,i+1,13) REP1(k,j+1,13) {
		vec.clear();
		vec.PB(ip[i]);
		vec.PB(ip[j]);
		vec.PB(ip[k]);
		h3[(1<<i)|(1<<j)|(1<<k)] = verify3(vec);
	}
	REP1(i,0,13) REP1(j,i+1,13) REP1(k,j+1,13) REP1(a,k+1,13) REP1(b,a+1,13) {
		vec.clear();
		vec.PB(ip[i]);
		vec.PB(ip[j]);
		vec.PB(ip[k]);
		vec.PB(ip[a]);
		vec.PB(ip[b]);
		h5[(1<<i)|(1<<j)|(1<<k)|(1<<a)|(1<<b)] = verify5(vec);
	}
	ans = 0;
	REP(i,14) {
		ban[i] = 1;
		REP(j,3) stCnt[j] = state[j] = 0;
		DFS(0);
		ban[i] = 0;
	}
}
int main() {
	predo();
	IOS;
	int nt;
	cin >> nt;
	REP1(t,1,nt) {
		input();
		solve();
		cout << "Case #" << t << ": " << ans << endl;
	}
	cerr << counter << endl;

	return 0;
}

