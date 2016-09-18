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


struct Trie {
	int trie[10000],ban[10000];
	int fail(string s) {
		int v = 1;
		for (auto c:s) {
			if (c == '0') v = v * 2;
			else v = v * 2 + 1;
			if (trie[v]) return 1;
		}
		return ban[v];
	}
	void set(string s, int x) {
		int v = 1;
		for (auto c:s) {
			if (c == '0') v = v * 2;
			else v = v * 2 + 1;
			ban[v] += x;
		}
		trie[v] += x;
	}
}trie;

int done[26],dcnt,app,N;
string s,ip;
string e[26];

void go(int i, int j) {
	if (j >= N) {
		if (app != dcnt) return;
		REP(k,26) {
			if (done[k]) {
				cout << char(k+'a') << " " << e[k] << endl;
			}
		}
		string s2;
		for (auto c:s) s2 += e[c-'a'];
		assert(s2 == ip);
		exit(0);
	}

	int x = s[i] - 'a';
	if (done[x]) {
		int l = SZ(e[x]);
		if (j+l > N) return;
		for (int k=0; k<l; k++) {
			if (ip[j+k] != e[x][k]) {
				return;
			}
		}
		go(i+1,j+l);
	} else {
		REP1(l,1,10) {
			if (j+l > N) return;
			string ss = ip.substr(j,l);
			if (trie.fail(ss)) continue;
			done[x] = 1;
			dcnt++;
			e[x] = ss;
			trie.set(ss,1);

			go(i+1,j+l);

			done[x] = 0;
			dcnt--;
			e[x] = "";
			trie.set(ss,-1);
		}
	}
}

int main() {
	IOS;
	FILEIO("prefix");
	cin >> s;
	cin >> ip;
	for (auto c:s) {
		if (!done[c-'a']) {
			done[c-'a'] = 1;
			app++;
		}
	}
	REP(i,26) done[i] = 0;
	N = SZ(ip);
	go(0,0);
	assert(false);

	return 0;
}

