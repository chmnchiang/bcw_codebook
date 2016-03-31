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

template<typename T, typename U>
ostream& operator <<(ostream &s, const map<T, U> &c) {
    s<<"{ ";
    for (auto it : c) s << it.F << ": " << it.S  << ", ";
    s<<"}";
    return s;
}
// Let's Fight!

template<typename T>
using vec = vector<T>;
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i)+= ((a) > (b) ? -1 : 1))

int I, G, O, P;
map<string, vec<string>> mp;
map<string, string> typ;
vec<string> outs;
vec<pair<vec<bool>, vec<bool>>> pats;
string curFG;
int curFT;
map<string, bool> ans;
vector<pair<string, int>> pos;
bool isOK;

void init() {
	mp.clear();
	typ.clear();
	outs.clear();
	pats.clear();
	ans.clear();
	pos.clear();
	isOK = false;
}

bool preform(string g, vec<bool> res) {
	string t = typ[g];
	if (t == "a") {
		for (auto x: res) {
			if (!x) return 0;
		}
		return 1;
	}
	if (t == "o") {
		for (auto x: res) {
			if (x) return 1;
		}
		return 0;
	}
	if (t == "n") {
		return !res[0];
	}
	if (t == "x") {
		bool ret = 0;
		for (auto x: res) {
			ret ^= x;
		}
		return ret;
	}
	assert(0);
}

bool dp(string g) {
	if (ans.find(g) != ans.end()) return ans[g];

	auto is = mp[g];
	vec<bool> res(SZ(is));
	loop (i, 0, SZ(is)) {
		res[i] = dp(is[i]);
	}
	bool ret = preform(g, res);
	if (g == curFG) {
		if (curFT == 1) ret = !ret;
		else if (curFT == 2) ret = 0;
		else ret = 1;
	}
//	cerr << g << " = " << ret << endl;
	return ans[g] = ret;
}


void calc(string fg, int ft) {
	curFG = fg;
	curFT = ft;

	for (auto p: pats) {
		ans.clear();
		const auto &in = p.F, &out = p.S;
		loop (i, 0, I) {
			string is = string("i") + to_string(i+1);
			ans[is] = in[i];
		}

//		cerr << p.F << endl;
		loop (i, 0, O) {
			string og = outs[i];
//			cerr << "Out" << i <<  " = " << dp(og) << endl;
			if (dp(og) != out[i]) {
				return;
			}
		}
	}
//	cerr << "push = " << fg << ' ' << ft << endl;
	pos.PB({fg, ft});
}

void calc() {
	calc("", 0);
	if (SZ(pos)) {
		isOK = true;
		return;
	}

	loop (i, 0, G) {
		string gs = string("g") + to_string(i+1);
		loop (j, 1, 3+1) {
			calc(gs, j);
		}
	}
}

int main() {
	IOS;
	int cas=0;
	while (true) {
		init();
		cin >> I >> G >> O;
		if(!I and !G and !O)
			break;

		loop (i, 0, G) {
			string tp;
			cin >> tp;
			string s = string("g") + to_string(i+1);
			typ[s] = tp;
			int c = (tp == "n" ? 1 : 2);
			loop (j, 0, c) {
				string ins; cin >> ins;
				mp[s].PB(ins);
			}
		}

		loop (i, 0, O) {
			int t; cin >> t;
			outs.PB(string("g") + to_string(t));
		}

		cin >> P;
		pats.resize(P);
		loop(i, 0, P) {
			pats[i].F.resize(I);
			pats[i].S.resize(O);
			loop (j, 0, I) {
				int t; cin >> t;
				pats[i].F[j] = (t == 1);
			}
			loop (j, 0, O) {
				int t; cin >> t;
				pats[i].S[j] = (t == 1);
			}
		}
//		cerr << mp << endl;
//		cerr << typ << endl;
//		cerr << pats << endl;
//		cerr << outs << endl;
		
		calc();
		
		cas++;
		cout << "Case " << cas << ": ";
		if (SZ(pos) >= 2) {
			cout << "Unable to totally classify the failure" << endl;
		} else {
			auto x = pos[0];
			if (isOK) {
				cout << "No faults detected" << endl;
			} else {
				int gi = atoi(x.F.substr(1).c_str());
				cout << "Gate " << gi << " is failing; ";
				cout << (x.S == 1 ? "output inverted" :
						 x.S == 2 ? "output stuck at 0" :
						 			"output stuck at 1") << endl;
			}
		}

	}

	return 0;
}


