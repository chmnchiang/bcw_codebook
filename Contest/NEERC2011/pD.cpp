#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

const int MX = 10101;

struct Trie {
	struct Node {
		int go[26];
		Node () {
			FZ(go);
		}
	};

	vector<Node> ls;
	int root = 0;
	int dp[26];
	int cnt;

	void insert(string s) {
		int id = root;
		for (int i=0; i<(int)s.length(); i++) {
			int c = s[i] - 'a';
			if (ls[id].go[c]) {
				id = ls[id].go[c];
			} else {
				int nid = ls.size();
				ls.PB(Node());
				ls[id].go[c] = nid;
				id = nid;
			}
		}
	}

	void init() {
		ls.clear();
		ls.PB(Node());
		root = 0;
		cnt = 0;
	}


	void dfs(int id) {
		cnt += 1;
		for (int i=0; i<26; i++) {
			if (ls[id].go[i]) {
				dp[i] += 1;
				dfs(ls[id].go[i]);
			}
		}
	}

	void calc() {
		for (int i=0; i<26; i++) {
			if (ls[root].go[i]) {
				dfs(ls[root].go[i]);
			}
		}
	}
	
}pref, post;

int N;
string ip[MX];
long long ans;

void dfs(int v) {
	for (int i=0; i<26; i++) {
		if (pref.ls[v].go[i]) {
			ans += post.cnt - post.dp[i];
			dfs(pref.ls[v].go[i]);
		}
	}
}

void calc() {
	int id = pref.root;
	for (int i=0; i<26; i++) {
		if (pref.ls[id].go[i]) {
			ans += post.cnt;
			dfs(pref.ls[id].go[i]);
		}
	}
}

bool us[26];

int main() {
	FILEIO("dictionary");

	pref.init(); post.init();
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> ip[i];
		if (ip[i].length() == 1) {
			int c = ip[i][0] - 'a';
			if (not us[c]) {
				us[c] = true;
				ans += 1;
			}
		}
	}

	for (int i=0; i<N; i++) {
		string rev = ip[i];
		reverse(ALL(rev));
		pref.insert(ip[i]);
		post.insert(rev);
	}

	post.calc();

	calc();

	cout << ans << endl;
	

    return 0;
}
