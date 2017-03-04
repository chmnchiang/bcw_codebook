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
int N, K;
const int MX = 3e5;
const int INF = 2.1e18;
int ans[MX];
bool eDie, oDie;
int eF, oF;
int eN, oN;
int pw[MX];

bool _eDie, _oDie;
int _eF, _oF, _eN, _oN;
void save() {
	_eDie = eDie;
	_oDie = oDie;
	_eF   = eF;
	_oF   = oF;
	_eN   = eN;
	_oN   = oN;
}

void resume() {
	eDie = _eDie;
	oDie = _oDie;
	eF   = _eF;
	oF   = _oF;
	eN   = _eN;
	oN   = _oN;
}

static void init() {
	pw[0] = 1;
	for (int i=1; i<MX; i++) {
		pw[i] = min(pw[i-1] * 2, INF);
	}
}

int fp(int x) {
	int z = N-1;
	if (x % 2) {
		if (z % 2) z++;
		return z - x;
	}
	if (z % 2) z--;
	return z - x;
}

int check(int pos) {
	save();

	//cout << oN << ' ' << eN << ' ' << oF << ' ' << eF << endl;

	int fpos = fp(pos);
	bool isO = pos%2;

	if (isO) oN --;
	else eN --;

	if (fpos >= pos) {
		if (isO) oF --;
		else eF --;
	} else {
		if (ans[fpos]) {
			if (isO) oDie = 1;
			else eDie = 1;
		}
	}

	//cout << oN << ' ' << eN << ' ' << oF << ' ' << eF << endl;
	int ret = 0;
	if (!oDie) ret += pw[oF + eN];
	if (!eDie) ret += pw[eF + oN];
	if (!oDie and !eDie) ret -= pw[oF + eF];

	resume();

	return ret;
}

void fl(int pos, int x) {
	int fpos = fp(pos);
	bool isO = pos%2;
	if (isO) oN--;
	else eN--;

	if (fpos >= pos) {
		if (isO) oF --;
		else eF --;
	} else {
		if (ans[fpos] != x) {
			if (isO) oDie = 1;
			else eDie = 1;
		}
	}

	ans[pos] = x;
}

int32_t main() {
	IOS;
	init();
	int T;
	cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cin >> N >> K;
		K--;

		eDie = oDie = 0;
		eF = oF = N-1;
		if (oF%2 == 0) oF--;
		if (eF%2 == 1) eF--;
		oF = (oF + 3) / 4;
		eF = (eF + 4) / 4;
		oN = N/2;
		eN = N - N/2;

		for (int i=0; i<N; i++) {
			int t = check(i);
//			cout << i << ' ' << t << endl;

			if (K < t) {
				fl(i, 0);
			} else {
				K -= t;
				fl(i, 1);
			}
		}

		cout << "Case #" << cas << ": ";
		if (K) {
			cout << "NOT FOUND!" << endl;
		} else {
			for (int i=0; i<N; i++) cout << ans[i];
			cout << endl;
		}
	}

	return 0;
}

