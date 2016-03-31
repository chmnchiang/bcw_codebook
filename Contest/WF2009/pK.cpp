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

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<string,string> pss;
const ll INF = 1152921504606846976LL;
const int MXN = 405;

int N,R,done[MXN];
ll dis[21][MXN][MXN];
string S,T;
vector<string> str[21];
pss rule[105];
vector<int> moid[21];

inline int id(string s) {
	int l = SZ(s);
	int id = lower_bound(ALL(str[l]),s)-begin(str[l]);
	if (id == SZ(str[l]) or str[l][id] != s) return -1;
	return id;
}
inline void add_str(string s) {
	REP(i,SZ(s)) {
		string t = s.substr(i);
		str[SZ(t)].PB(t);
	}
}
int main() {
	IOS;
	int cas = 0;
	while (true) {
		cin >> S;
		if (S == ".") break;
		cin >> T >> R;
		REP1(i,1,R) cin >> rule[i].F >> rule[i].S;

		N = SZ(S);
		REP1(i,1,N) str[i].clear();
		add_str(S);
		add_str(T);
		REP1(i,1,R) {
			if (SZ(S) < SZ(rule[i].F)) continue;
			add_str(rule[i].F);
			add_str(rule[i].S);
		}

		REP1(i,1,N) {
			sort(ALL(str[i]));
			str[i].resize(unique(ALL(str[i])) - begin(str[i]));
			assert(SZ(str[i]) < MXN);
			int len = SZ(str[i]);
			REP(j,len) {
				REP(k,len) dis[i][j][k] = INF;
				dis[i][j][j] = 0;
			}
			moid[i].resize(len);
			REP(j,len) {
				moid[i][j] = id(str[i][j].substr(1));
				if (i != 1 and moid[i][j] == -1) {
					assert(moid[i][j] != -1);
				}
			}
		}

		REP1(k,1,N) {
			int n = SZ(str[k]);
			REP1(i,1,R) {
				if (SZ(rule[i].F) == k) {
					int x = id(rule[i].F);
					int y = id(rule[i].S);
					dis[k][x][y] = min(dis[k][x][y],1LL);
				}
			}
			REP(i,n) REP(j,n) {
				if (i == j) dis[k][i][j] = 0;
				else if (str[k][i][0] == str[k][j][0]) {
					int x = moid[k][i];
					int y = moid[k][j];
					if (x != -1 and y != -1)
						dis[k][i][j] = min(dis[k][i][j], dis[k-1][x][y]);
				}
			}
			REP(l,n) REP(i,n) REP(j,n)
				dis[k][i][j] = min(dis[k][i][j], dis[k][i][l] + dis[k][l][j]);
		}
		cas++;
		cout << "Case " << cas << ": ";
		int st = id(S), ed = id(T);
		if (dis[N][st][ed] == INF) cout << "No solution\n";
		else cout << dis[N][st][ed] << "\n";
	}

	return 0;
}


