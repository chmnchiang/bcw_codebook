//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin);
//  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

const int MXN = 105;
struct KM{
// Maximum Bipartite Weighted Matching (Perfect Match)
	static const int INF = 2147483647; // long long
	int n,match[MXN],vx[MXN],vy[MXN];
	int edge[MXN][MXN],lx[MXN],ly[MXN],slack[MXN];
	// ^^^^ long long
	void init(int _n){
		n = _n;
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				edge[i][j] = 0;
	}
	void add_edge(int x, int y, int w){ // long long
    assert(w > 0);
		edge[x][y] = w;
	}
	bool DFS(int x){
		vx[x] = 1;
		for (int y=0; y<n; y++){
			if (vy[y]) continue;
			if (lx[x]+ly[y] > edge[x][y]){
				slack[y] = min(slack[y], lx[x]+ly[y]-edge[x][y]);
			} else {
				vy[y] = 1;
				if (match[y] == -1 || DFS(match[y])){
					match[y] = x;
					return true;
				}
			}
		}
		return false;
	}
	int solve(){
		fill(match,match+n,-1);
		fill(lx,lx+n,-INF);
		fill(ly,ly+n,0);
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				lx[i] = max(lx[i], edge[i][j]);
		for (int i=0; i<n; i++){
			fill(slack,slack+n,INF);
			while (true){
				fill(vx,vx+n,0);
				fill(vy,vy+n,0);
				if ( DFS(i) ) break;
				int d = INF; // long long
				for (int j=0; j<n; j++)
					if (!vy[j]) d = min(d, slack[j]);
				for (int j=0; j<n; j++){
					if (vx[j]) lx[j] -= d;
					if (vy[j]) ly[j] += d;
					else slack[j] -= d;
				}
			}
		}
		int res=0;
		for (int i=0; i<n; i++)
			res += edge[match[i]][i];
		return res;
	}
}graph;

int N,dp[MXN][MXN];
pii edge[MXN];
vector<int> E[MXN];
vector<int> trans[MXN][MXN];
int col[MXN][MXN];

void DFS(int u, int f) {
  REP(i,SZ(E[u])) {
    if (E[u][i] == f) {
      swap(E[u][i], E[u].back());
      E[u].pop_back();
      break;
    }
  }

  for (auto v:E[u]) {
    DFS(v,u);
  }

  const int mag = 1e5;
  int ok = 0;
  REP1(c,1,N) {
    if (ok) {
      dp[u][c] = dp[u][c-1];
      trans[u][c] = trans[u][c-1];
      continue;
    }
    graph.init(N);
    REP(i,SZ(E[u])) {
      int v = E[u][i];
      REP1(j,1,N) {
        if (j == c) continue;
        graph.add_edge(i,j-1,mag-(dp[v][j]+j));
      }
    }
    dp[u][c] = -(graph.solve()-mag*SZ(E[u]));
    trans[u][c].clear();
    int fail = 0;
    REP(i,SZ(E[u])) {
      REP(j,N) {
        if (graph.match[j] == i) {
          trans[u][c].PB(j+1);
          if (j+1 > c) fail = 1;
          break;
        }
      }
      assert(SZ(trans[u][c]) == i+1);
    }
    if (!fail) ok = 1;

  }
}
void gen_tbl(int u, int c) {
  REP(i,SZ(E[u])) {
    int v = E[u][i];
    int nc = trans[u][c][i];
    col[u][v] = col[v][u] = nc;
    gen_tbl(v,nc);
  }
}
int main() {
  IOS;
  FILEIO("coloring");
  cin >> N;
  REP(i,N-1) {
    cin >> edge[i].F >> edge[i].S;
    E[edge[i].F].PB(edge[i].S);
    E[edge[i].S].PB(edge[i].F);
  }
  DFS(1,1);
  int bestc = 1;
  REP1(i,1,N) {
    if (dp[1][i] < dp[1][bestc]) {
      bestc = i;
    }
  }
  cout << dp[1][bestc] << endl;
  gen_tbl(1,bestc);
  int tot = 0;
  REP(i,N-1) {
    int u = edge[i].F, v = edge[i].S;
    assert(col[u][v]);
    tot += col[u][v];
    cout << col[u][v] << " ";
  }
  cout << endl;
  assert(tot == dp[1][bestc]);
  

  return 0;
}

