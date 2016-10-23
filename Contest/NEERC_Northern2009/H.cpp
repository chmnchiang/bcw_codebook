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


int N;
int nid;
int cnt[100005];
int kind,two;
map<int,int> idx;

int getid(int v) {
	if (idx.count(v)) return idx[v];
	return idx[v]=nid++;
}
void add(int x) {
	if (cnt[x] >= 2) two--;
	if (cnt[x] == 0) kind++;
	cnt[x]++;
	if (cnt[x] >= 2) two++;
}
void sub(int x) {
	if (cnt[x] == 0) return;
	if (cnt[x] >= 2) two--;
	if (cnt[x] == 1) kind--;
	cnt[x]--;
	if (cnt[x] >= 2) two++;
}
int main() {
	FILEIO("homo");
	IOS;
	nid = 0;
	cin >> N;
	kind = two = 0;
	REP(i,N) {
		string s;
		int v;
		cin >> s >> v;
		v = getid(v);
		if (s == "insert") {
			add(v);
		} else {
			sub(v);
		}
		if (kind >= 2 and two >= 1) cout << "both\n";
		else if (two >= 1) cout << "homo\n";
		else if (kind >= 2) cout << "hetero\n";
		else cout << "neither\n";
	}

	return 0;
}
