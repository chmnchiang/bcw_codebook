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



const int MAXN = 205;
int N,vst[MAXN],col[MAXN],ban[MAXN];
vector<int> E[MAXN];

bool check_ok() {
	FZ(vst);
	REP1(i,1,N) {
		if (ban[i] or vst[i]) continue;
		queue<int> que;
		que.push(i);
		col[i] = 1;
		vst[i] = 1;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (auto v:E[u]) {
				if (ban[v]) continue;
				if (vst[v]) continue;
				col[v] = col[u] ^ 1;
				que.push(v);
				vst[v] = 1;
			}
		}
	}

	REP1(i,1,N) {
		if (ban[i]) continue;
		for (auto v:E[i]) {
			if (ban[v]) continue;
			if (col[i] == col[v]) return false;
		}
	}
	return true;
}
int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;
	cin>>N;
	REP1(i,1,N) {
		int m,v;
		cin>>m;
		REP(_,m) {
			cin>>v;
			E[i].PB(v);
			E[v].PB(i);
		}
	}

	int ok = 0;
	REP1(i,0,N) {
		REP(j,i) {
			ban[i] = ban[j] = 1;
			if (check_ok()) {
				ok = 1;
				break;
			}
			ban[i] = ban[j] = 0;
		}
		if (ok) break;
	}
	if (ok) cout<<"Hurrah!"<<endl;
	else cout<<"Fired."<<endl;

	return 0;
}

