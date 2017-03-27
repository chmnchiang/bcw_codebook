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

string S;
int L;

struct Sent {
	string cont;
	set<string> words;
};
vector<Sent> sents;

bool kuo(int id) {
	char c = S[id];
	if (c == '?' or c == '!') return true;
	if (c != '.') return false;

	for (int jd = id+1; jd<L; jd++) {
		char d = S[jd];
		if (d != ' ') {
			if ('a' <= d and d <= 'z') return false; 
			else return true;
		}
	}
	return true;
}

bool isalpha(char c) {
	return ('A' <= c and c <= 'Z') or ('a' <= c and c <= 'z');
}

string lower(string s) {
	for (auto &c: s) {
		if ('A' <= c and c <= 'Z') c += 'a' - 'A';
	}
	return s;
}

set<string> wd(string s) {
	int id = 0;
	int l = SZ(s);
	set<string> st;
	while (id < l) {
		while (id < l and not isalpha(s[id])) id++;
		if (id >= l) break;

		int jd = id;
		while (jd < l and isalpha(s[jd])) jd++;
		string t = lower(s.substr(id, jd-id));
		st.insert(t);
		id = jd;
	}
	return st;
}

void parse() {
	int id = 0;
	L = SZ(S);
	while (id < L) {
		while (id < L and S[id] == ' ') id++;

		if (id >= L) {
			sents.PB({"", {}});
			break;
		}

		int jd = id;
		while (jd < L and not kuo(jd)) jd++;
		auto wds = wd(S.substr(id, jd-id));
		if (jd < L) jd++;

		string s = S.substr(id, jd-id);
		id = jd;

		sents.PB({s, wds});
	}
}

string trim(string s) {
	int id = SZ(s);
	while (id and s[id-1] == ' ') id--;
	return s.substr(0, id);
}

int main() {
	IOS;
	getline(cin, S);
	
	parse();
	int Q; cin >> Q;
	string ss;
	getline(cin, ss);
	for (int i=0; i<Q; i++) {
		string s; getline(cin, s);
		auto z = wd(s);
		cout << "Search results for \"" << s << "\":\n";
		for (auto x: sents) {
			bool fg = 1;
			for (auto _y: z) {
				auto y = lower(_y);
				if (x.words.find(y) == x.words.end()) {
					fg = 0; break;
				}
			}
			if (fg) cout << "- \"" << trim(x.cont) << "\"" << endl;
		}
	}

	return 0;
}

