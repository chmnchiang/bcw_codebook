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


typedef pair<int,int> pii;
const int MX = 10005;

int N,M;
int ans;
bitset<MX> vst[MX];
vector<int> E[MX];
vector<pii> vec;

void DFS(int a, int b, int d) {
	vst[a][b] = 1;
	ans++;
	if (d >= 2*MX) {
		vec.PB(pii(a,b));
		return;
	}
	for (auto v:E[a]) {
		if (vst[v][b]) continue;
		DFS(v,b,d+1);
	}
	for (auto v:E[b]) {
		if (vst[a][v]) continue;
		DFS(a,v,d+1);
	}
}
int main() {
	IOS;
	cin >> N >> M;
	REP1(i,1,M) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
	}
	REP1(i,1,N) {
		if (!vst[i][i]) DFS(i,i,0);
	}
	while (!vec.empty()) {
		vector<pii> v1;
		v1 = vec;
		vec.clear();
		for (auto it:v1) {
			ans--;
			DFS(it.F,it.S,0);
		}
	}
	cout << ans << endl;

	return 0;
}

