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

const int MAX = 233333;

struct Trie {
	int ch[2],cnt;
} trie[MAX];

int N,M;
int root;
int mem;
vector<int> stk;
string s;

int gen() {
	stk.clear();
	int u = root;
	REP(i,M) {
		stk.PB(u);
		int a = s[i] - '0';
		if (trie[u].ch[a] == 0) {
			trie[u].ch[a] = mem++;
		}
		u = trie[u].ch[a];
	}
	return u;
}
int calc() {
	int res = 0;
	int u = root;
	REP(i,M) {
		int a = s[i] - '0';
		int l = trie[u].ch[0];
		int r = trie[u].ch[1];
		if (a == 1) {
			res += trie[r].cnt;
			u = l;
		} else {
			u = r;
		}
	}
	return res;
}
int main() {
	IOS;
	cin>>N>>M;
	root = 1;
	mem = 2;

	REP1(i,1,N) {
		cin>>s;
		int ans = calc();
		cout<<ans<<endl;

		int at = gen();
		trie[at].cnt++;
		for (auto u:stk)
			trie[u].cnt++;
	}



	return 0;
}

