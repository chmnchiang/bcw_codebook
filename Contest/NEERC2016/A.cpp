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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<int,int> umap_t;

struct Token {
	string s;
	int sep;
};

string ip;
vector<Token> vec;
vector<string> stk;

int isletter(int a) {
	return ('a'<=a and a<='z') or ('A'<=a and a<='Z');
}
int good(string &s) {
	if (SZ(s) <= 1) return 0;
	if (!('A' <= s[0] and s[0] <= 'Z')) return 0;
	REP1(i,1,SZ(s)-1)
		if (isupper(s[i])) return 0;

	return 1;
}
void clear() {
	if (stk.empty()) return;
	if (SZ(stk) == 1) {
		cout<<stk[0];
		stk.clear();
		return;
	}
	string s;
	for (auto ss:stk) {
		s += ss[0];
	}
	cout<<s<<" (";
	int sz = SZ(stk);
	REP(i,sz) {
		cout<<stk[i]<<" )"[i==sz-1];
	}
	stk.clear();

}
int main() {
	FILEIO("abbreviation");
	IOS;
	while (getline(cin,ip)) {
		int len = SZ(ip);
		string s;
		vec.clear();
		REP(i,len) {
			if (isletter(ip[i])) {
				if (!s.empty() and !isletter(s[0])) {
					vec.PB({s,1});
					s = "";
				}
			} else {
				if (!s.empty() and isletter(s[0])) {
					vec.PB({s,0});
					s = "";
				}
			}
			s += ip[i];
		}

		if (!s.empty()) vec.PB({s,!isletter(s[0])});


		assert(stk.empty());
		for (auto it:vec) {
			s = it.s;
			if (it.sep) {
				if (!stk.empty() and s == " ") {
					continue;
				} else {
					clear();
					cout<<s;
				}
			} else {
				if (good(s)) {
					stk.PB(s);
				} else if (!stk.empty()) {
					clear();
					cout<<" "<<s;
				} else {
					cout<<s;
				}
			}
		}
		clear();
		cout<<endl;
		
	}

	return 0;
}

