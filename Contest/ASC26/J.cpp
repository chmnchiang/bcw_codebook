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
const int MX = 205;
const int MXM = 1005;

int N,M,T,ac[MX];
vector<pii> E[MX];
vector<int> path[MX];
int dp[MX][MX];
pii nxt[MX][MX];
int fa[MXM],bln[MXM];

int f(int x) { return fa[x] == x ? x : fa[x]=f(fa[x]); }
void uni(int x, int y) { fa[f(y)] = f(x); }

int go(int i, int rem) {
	if (rem == 0) return ac[i];
	if (dp[i][rem] != -1) return dp[i][rem];
	for (auto it:E[i]) {
		int s = it.F;
		if (go(s,rem-1)) {
			nxt[i][rem] = it;
			return dp[i][rem] = 1;
		}
	}
	return dp[i][rem] = 0;
}

int main() {
	FILEIO("suffix");
	cin >> N >> M >> T;
	REP(i,T) {
		int u;
		cin >> u;
		ac[u] = 1;
	}
	REP1(i,1,M) {
		int u,v;
		cin >> u >> v;
		E[u].PB(pii(v,i));
	}
	FMO(dp);
	int L = -1;
	REP1(i,1,N) {
		path[i].clear();
		if (go(1,i)) {
			int s = 1, rem = i;
			while (rem) {
				path[i].PB(nxt[s][rem].S);
				s = nxt[s][rem].F;
				rem--;
			}
		} else {
			L = i-1;
			break;
		}
	}

	REP1(i,1,M) fa[i] = i;
	REP1(i,1,L) {
		REP1(j,i+1,L) {
			int x = path[i][0];
			int y = path[j][SZ(path[j])-i];
			uni(x,y);
		}
	}
	int K = 0;
	REP1(i,1,M) if (fa[i] == i) {
		bln[i] = ++K;
	}

	cout << L << " " << K << endl;
	for (auto i:path[L])
		cout << bln[f(i)] << " ";
	cout << endl;
	REP1(i,1,M) {
		cout << bln[f(i)] << " ";
	}
	cout << endl;

    return 0;
}

