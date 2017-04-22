//a34021501 {{{
#include<bits/stdc++.h>/*{{{*//*}}}*//*{{{*//*}}}*//*{{{*//*}}}*/
#include<unistd.h>
using namespace std;/*{{{*//*}}}*/
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

#ifdef HAO123
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#endif

#ifdef HAO123
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif
// }}}
// Let's Fight! !111111111!


typedef pair<long long, long long> pll;
struct CostFlow {
	static const int MXN = 205;
	static const long long INF = 102938475610293847LL;
	struct Edge {
		int v, r;
		long long f, c;
	};
	int n, s, t, prv[MXN], prvL[MXN], inq[MXN];
	long long dis[MXN], fl, cost;
	vector<Edge> E[MXN];
	void init(int _n, int _s, int _t) {
		n = _n; s = _s; t = _t;
		for (int i=0; i<n; i++) E[i].clear();
		fl = cost = 0;
	}
	void add_edge(int u, int v, long long f, long long c) {
    //cout << u << ' ' << v << ' ' << f << endl;
		E[u].PB({v, SZ(E[v])  , f,  c});
		E[v].PB({u, SZ(E[u])-1, 0, -c});
	}
	pll flow() {
		while (true) {
			for (int i=0; i<n; i++) {
				dis[i] = INF;
        inq[i] = 0;
			}
			dis[s] = 0;
			queue<int> que;
			que.push(s);
			while (!que.empty()) {
				int u = que.front(); que.pop();
				inq[u] = 0;
				for (int i=0; i<SZ(E[u]); i++) {
					int v = E[u][i].v;
					long long w = E[u][i].c;
					if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
						prv[v] = u; prvL[v] = i;
						dis[v] = dis[u] + w;
						if (!inq[v]) {
							inq[v] = 1;
							que.push(v);
						}
					}
				}
			}
			if (dis[t] == INF) break;
			long long tf = INF;
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				tf = min(tf, E[u][l].f);
			}
			for (int v=t, u, l; v!=s; v=u) {
				u=prv[v]; l=prvL[v];
				E[u][l].f -= tf;
				E[v][E[u][l].r].f += tf;
			}
			cost += tf * dis[t];
			fl += tf;
		}
		return {fl, cost};
	}
}flow;

const int MX = 333;
int N, M, X;
char ip[MX][MX];
using pii = pair<int, int>;
vector<pii> doms;
const int INF = 1029384756;

static void pre() {
  for (int i=0; i<=6; i++) {
    for (int j=0; j<=i; j++) {
      doms.PB({i, j});
    }
  }
}

int us[88][88][88];
int mem[88][88][88];
int dp(int x, int y, int i) {
  if (!x and !y) return 0;
  if (i >= SZ(doms)) return -INF;

  if (us[x][y][i]) return mem[x][y][i];

  us[x][y][i] = 1;
  int &ans = mem[x][y][i];
  ans = dp(x, y, i+1);

  if (x) {
    ans = max(dp(x-1, y, i+1) + max(doms[i].F, doms[i].S), ans);
  }

  if (y) {
    ans = max(dp(x, y-1, i+1) + doms[i].F + doms[i].S, ans);
  }
  
  return ans;
}

const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

inline bool inr(int x, int y) {
  return x >= 0 and x < N and y >= 0 and y < M;
}

int calc(int hao) {
  int S = N*M, U = S+1, V = U+1;
  flow.init(V, S, U);

  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      if (ip[i][j] == 'W' || ip[i][j] == 'G') {
        int t = i*M + j;
        int x = i+j;
        if (x%2 == 0) {
          flow.add_edge(S, t, 1, 0);
        } else {
          flow.add_edge(t, U, 1, 0);
        }

        if (x%2 == 0) {
          for (int d=0; d<4; d++) {
            int ni = i + dir[d][0], nj = j+dir[d][1];
            if (!inr(ni, nj)) continue;
            int nt = ni * M + nj;
            if (ip[ni][nj] == 'G' and ip[i][j] == 'G') {
              flow.add_edge(t, nt, 1, hao);
            } else {
              flow.add_edge(t, nt, 1, 0);
            }
          }
        }
      }
    }
  }


  auto p = flow.flow();
 // cout << p << endl;
  if (p.F != X/2) return -INF;

  return p.S;
}

int main() {

  pre();

  int cas = 0;
  while (cin >> N >> M) {
    if (!N and !M) break;

    cas++;
    cout << "Case " << cas << ": ";


    X = 0;
    int Z = 0;
    for (int i=0; i<N; i++) {
      cin >> ip[i];
      for (int j=0; j<M; j++) {
        X += ip[i][j] != 'B';
        Z += ip[i][j] == 'G';
      }
    }


    if (X%2 || X>28*2) {
      cout << "No solution" << endl;
      continue;
    }
    
    int lb = calc(1);
    if (lb == -INF) {
      cout << "No solution" << endl;
      continue;
    }

    int rb = -calc(-1);



    int ans = -INF;
    for (int i=lb; i<=rb; i++) {
      ans = max(ans, dp(Z-i*2, i, 0));
    }
    cout << ans << endl;
  }

  return 0;
}

