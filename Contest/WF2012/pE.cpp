#include<bits/stdc++.h>/*{{{*/
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
}/*}}}*/
// Let's Fight!

int N;
bitset<80> edge[80],goal;
vector<int> ans,vec;
int tot;

bool DFS(int cur, int lst, bitset<80> ok, int lim) {
	tot++;
	if (cur >= lim) {
		if (ok == goal) {
			ans = vec;
			return true;
		}
		return false;
	}
	if (N-lst-1 + cur < lim) return false;

	bitset<80> bt;
	REP1(i,lst+1,N-1) {
//		if (ok[i]) continue;
		bt = edge[i] | ok;
		bt[i] = 1;
		vec.PB(i);
		if (DFS(cur+1,i,bt,lim)) return true;
		vec.pop_back();
	}
	return false;
}

int main() {
	IOS;
	int cas = 0;
	while (cin >> N) {
    goal.reset();
		REP(i,N) {
      goal[i] = 1;
			string s;
			cin >> s;
			edge[i].reset();
			REP(j,N) {
				if (s[j] == '1') edge[i][j] = 1;
			}
		}
		bitset<80> ok;
		REP1(i,1,6) {
			ans.clear();
			vec.clear();
			ok.reset();
			if (DFS(0,-1,ok,i)) break;
		}
		if (ans.empty()) {
			ok.reset();
			int cnt = 0;
			while (cnt < N) {
				int best = -1;
				int cover = 0;
				REP(i,N) {
					if (ok[i]) continue;
					int c = 1;
					REP(j,N) {
						if (edge[i][j] and !ok[j])
							c++;
					}
					if (c > cover) {
						cover = c;
						best = i;
					}
				}
				assert(best != -1);
				ans.PB(best);
				ok[best] = 1;
				cnt++;
				REP(i,N) {
					if (edge[best][i] and !ok[i]) {
						ok[i] = 1;
						cnt++;
					}
				}
			}
		}
		cas++;
		cout << "Case " << cas << ": ";
		cout << SZ(ans);
		for (auto it:ans) cout << " " << it+1;
		cout << "\n";
	}

	return 0;
}

