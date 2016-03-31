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

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i)+= ((a) > (b) ? -1 : 1))

const int INF = 1029384756;
const int MX = 66666;
using pii=pair<int,int>;
int V, E;
int S, T;
vector<pii> el[MX];
vector<int> id[MX];
vector<pii> rel[MX];
vector<int> rid[MX];
bool vt[MX];
int ld[MX][2], rd[MX][2];
bool lg[MX], rg[MX];

void deinit() {
	loop(i, 0, V+5) {
		el[i].clear();
		rel[i].clear();
		id[i].clear();
		rid[i].clear();
		lg[i] = rg[i] = 0;
	}
}

void dfs(int u, int tar, vector<pii> e[], int d[][2]) {
	if (vt[u]) return;

	if (u == tar) {
		d[u][0] = 0;
		d[u][1] = 0;
		return;
	}

	d[u][0] = INF;
	d[u][1] = -INF;
	for (auto p: e[u]) {
		int v = p.F, c = p.S;
		dfs(v, tar, e, d);
		
		d[u][0] = min(d[u][0], d[v][0] + c);
		d[u][1] = max(d[u][1], d[v][1] + c);
	}
	vt[u] = 1;
}



int main() {
	IOS;
	
	int cas=0;
	while(1) {
		cin >> V >> E;
		if (!V and !E) break;
		S = 1, T = V;

		loop(i, 0, E) {
			int u, v, c; cin >> u >> v >> c;
			el[u].PB({v, c});
			id[u].PB(i+1);
			rel[v].PB({u, c});
			rid[u].PB(i+1);
		}


		fill(vt, vt+V+5, 0);
		dfs(S, T, el, ld);
		fill(vt, vt+V+5, 0);
		dfs(T, S, rel, rd);

		bool flag=1;
		loop(i, 1, V+1) {
			lg[i] = (ld[i][0] >= ld[i][1]);
			rg[i] = (rd[i][0] >= rd[i][1]);

			if (!lg[i] and !rg[i]) {
				flag=0;
				break;
			}
		}

		cas++;
		if (!flag)
			cout << "Case " << cas << ": No solution" << endl;
		else {
			cout << "Case " << cas << ": ";
			int dis = ld[S][1];
			vector<pii> ans;

			for (int i=1; i<=V; i++) {
				loop (j, 0, SZ(el[i])) {
					int eid = id[i][j];
					int u = i, v = el[i][j].F, c = el[i][j].S;
					bool tu = rg[u], tv = rg[v];
					if (tu != tv) {
						assert(tu);
						int d = rd[u][0] + ld[v][0] + c;
						int df = dis - d;
						if (df)
							ans.PB({eid, df});
					}
				}
			}
			cout << SZ(ans) << " " << dis << endl;
			for (auto p: ans) {
				cout << p.F << ' ' << p.S << endl;
			}
		}
		

		
		deinit();
	}

	return 0;
}


