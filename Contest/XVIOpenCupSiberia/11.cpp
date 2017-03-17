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



const int MAXN = 100005;

int N,K,M,col[MAXN],vst[MAXN];
int ans;
vector<int> E[MAXN];

void DFS(int u) {
	col[u] = 1;
	ans++;
	for (auto v:E[u]) {
		if (!col[v]) {
			DFS(v);
		}
	}
}
int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;
	cin>>N>>K>>M;
	REP(_,K) {
		int v;
		cin>>v;
		col[v] = 1;
	}

	ans = K;
	REP(_,M) {
		int u,v;
		cin>>u>>v;
		E[v].PB(u);
		if (col[v] and !col[u]) DFS(u);
		cout<<ans<<endl;
	}

	return 0;
}

