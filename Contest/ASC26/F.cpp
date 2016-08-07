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


vector<string> tokens;
void tokenize() {
	string cur = "";
	char c;
	c = getchar();
#define _pu if(SZ(cur)) tokens.PB(cur)
	while (c != EOF) {
		if (c == ' ' or c == '\n' or c == '\t') {
			_pu;
			cur = "";
		} else if (c == '(' or c == ')' or c == '{' or c == '}' or c == ',') {
			_pu;
			if (c != ',')
				tokens.PB(string("") + c);
			cur = "";
		} else if (c == '+' or c == '-') {
			char d = getchar();
			assert(d == c);
			_pu;
			tokens.PB(string("") + c + d);
			cur = "";
		} else {
			cur += c;
		}
		c = getchar();
	}
	if (SZ(cur))
		tokens.PB(cur);
}

const int BLK = 1;
const int IF = 2;
const int PLUS = 3;
const int FC = 4;

const int MMM = 1<<15;
const int MV = MMM*20;

vector<string> funs;
map<string, int> funID;



int getID(string fn, int state) {
	return funID[fn] * MMM + state;
}
struct Stat;
struct Fun {
	vector<string> args;
	map<string, int> argm;
	Stat *stat;

};
map<string, Fun> funMap;

struct Stat {
	/*
	enum {
		BLK, 
		IF,
		PLUS,
		FC,
	} typ;
	*/

	int typ;

	vector<Stat*> stats;
	string var;
	vector<string> args;
	int add;

	void sim(int &state, map<string, int> &varMap, vector<int> &call) {
		//cout << "type = " << typ << endl;
		if (typ == BLK) {
			for (auto x: stats) {
				x->sim(state, varMap, call);
			}
		} else if (typ == IF) {
			int t = (1<<varMap[var]) & state;
			if (t) {
				stats[0]->sim(state, varMap, call);
			} else {
				stats[1]->sim(state, varMap, call);
			}
		} else if (typ == PLUS) {
			if (add == 1) {
				state |= (1<<varMap[var]);
			} else {
				if (state & (1<<varMap[var]))
					state ^= (1<<varMap[var]);
			}
		} else if (typ == FC) {
			//auto &fun = funMap[var];
			int t = 0;
			int i = 0;
			for (auto a: args) {
				int vid = varMap[a];
				if ((1<<vid) & state) {
					t |= (1<<i);
				}
				i++;
			}
			call.PB(getID(var, t));
			//cout << "push " << var << " " << t << endl;
		}
	}
};


vector<string> parseArgs(int &id) {
	assert(tokens[id] == "(");
	id++;

	vector<string> res;

	while (tokens[id] != ")") {
		res.PB(tokens[id++]);
	}
	id++;
	return res;
}

Stat* parseStat(int &id) {
	string tok = tokens[id];
	Stat *sta = new Stat();
	if (tok == "{") {
		sta->typ = BLK;
		id++;
		while (tokens[id] != "}") {
			auto *z = parseStat(id);
			sta->stats.PB(z);
		}
		assert(tokens[id] == "}");
		id++;
	} else if (tok == "if") {
		sta->typ = IF;
		id++;
		assert(tokens[id] == "(");
		id++;
		sta->var = tokens[id];
		id++;
		assert(tokens[id] == ")");
		id++;
		auto *z = parseStat(id);
		sta->stats.PB(z);
		assert(tokens[id] == "else");
		id++;
		z = parseStat(id);
		sta->stats.PB(z);
	} else {
		string nm = tokens[id++];
		sta->var = nm;
		if (tokens[id] == "(") {
			sta->typ = FC;
			sta->args = parseArgs(id);
		} else if (tokens[id] == "++") {
			sta->typ = PLUS;
			sta->add = 1;
			id++;
		} else if (tokens[id] == "--") {
			sta->typ = PLUS;
			sta->add = -1;
			id++;
		} else assert(false);
	}

	return sta;
}


void parseFn(int &id) {
	string name = tokens[id++];
	auto &fun = funMap[name];
	funID[name] = SZ(funs);
	funs.PB(name);

	auto ret = parseArgs(id);
	for (int i=0; i<SZ(ret); i++) {
		fun.args.PB(ret[i]);
		fun.argm[ret[i]] = i;
	}

	fun.stat = parseStat(id);

}

void parseFns() {
	int id = 0;
	while (id < SZ(tokens)) {
		parseFn(id);
	}
}

vector<int> E[MV];

int cycf;
int vst[MV],ins[MV];

void DFS(int u) {
	vst[u] = 1;
	ins[u] = 1;
	for (auto v:E[u]) {
		if (!vst[v]) {
			DFS(v);
		} else if (ins[v]) {
			cycf = 1;
		}
	}
	ins[u] = 0;
}
void calc() {
	tokenize();
//	cout<<tokens << endl;
	parseFns();



	for (int i=0; i<SZ(funs); i++) {
		auto &fun = funMap[funs[i]];
		int argv = SZ(fun.args);
		for (int j=0; j<(1<<argv); j++) {
			//cout << funs[i] << ' ' << j << endl;
			int jj = j;
			int id = getID(funs[i], j);
			vector<int> ret;
			fun.stat->sim(jj, fun.argm, ret);
			E[id] = ret;
			//cout << ret << endl;
		}
	}
	cycf = 0;
	REP(i,MV) {
		if (vst[i]) continue;
		DFS(i);
	}
	if (cycf) cout << "YES" << endl;
	else cout << "NO" << endl;

}

int main() {
	FILEIO("recursion");

	calc();


    return 0;
}

