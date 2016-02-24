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
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
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

int N,M,K,valid[55][55],out[55][55];
pii tar,sum[55][55];
vector<pii> trans[11];
vector<int> stateVec, nCon;
set<int> dp[10][10][51][51];
vector<pii> use;

inline pii next_position(int i, int j) {
  if (++j >= M) {
    i++;
    j = 0;
  }
  return {i, j};
}
inline int getv_state(int s, int p) {
  assert(p < M);
  return (s >> (3 * p)) & 0x7;
}
inline int setv_state(int s, int p, int x) {
  s &= ~(0x7 << (3 * p));
  s |= x << (3 * p);
  assert(x < 8);
  return s;
}
inline int reorder_vec(int s) {
  int id = 0, idx[8] = {0};
  REP(i,M) {
    int v = getv_state(s, i);
    if (v && !idx[v]) idx[v] = ++id;
    s = setv_state(s, i, idx[v]);
  }
  return s;
}
inline int get_trans_dont_choose(int s, int j) {
  int v = getv_state(s, j);
  if (!v) return s;
  int cnt = 0;
  REP(k,M) {
    if (getv_state(s, k) == v) cnt++;
  }
  if (cnt <= 1) return -1;
  int ns = setv_state(s, j, 0);
  return reorder_vec(ns);
}
inline int get_trans_choose_j(int s, int j) {
  int ns = setv_state(s, j, 7);
  if (j && getv_state(ns, j-1))
    ns = setv_state(ns, j, getv_state(ns, j-1));
  int lst = getv_state(s, j);
  if (lst) {
    int cur = getv_state(ns, j);
    REP(k,M) {
      if (getv_state(ns, k) == lst)
        ns = setv_state(ns, k, cur);
    }
  }
  return reorder_vec(ns);
}
void output(int id) {
  REP(i,M)
    cout << getv_state(stateVec[id], i) << " ";
}
void gen_state(int pos, int mx, int s) {
  if (pos >= M) {
    stateVec.PB(s);
    return;
  }
  REP1(i,0,mx+1) {
    if (mx >= 6) break;
    gen_state(pos+1, max(mx,i), setv_state(s, pos, i));
  }
}
void predo() {
  // gen states
  gen_state(0, 0, 0);
  sort(ALL(stateVec));
  nCon.resize(SZ(stateVec));
  REP(i,SZ(stateVec)) {
    nCon[i] = 0;
    REP(j,M) nCon[i] = max(nCon[i], getv_state(stateVec[i], j));
  }

  REP(j,M){
    trans[j].resize(SZ(stateVec));
    REP(i,SZ(stateVec)) {
      trans[j][i] = {-1, -1};
      int ns = get_trans_dont_choose(stateVec[i], j);
      if (ns != -1) {
        if (ns == stateVec[i]) trans[j][i].F = i;
        else trans[j][i].F = lower_bound(ALL(stateVec), ns) - begin(stateVec);
      }
      ns = get_trans_choose_j(stateVec[i], j);
      trans[j][i].S = lower_bound(ALL(stateVec), ns) - begin(stateVec);
    }
  }

  memset(sum, 0, sizeof(sum));
  sum[N-1][M-1] = {0, 0};
  if (valid[N-1][M-1]) {
    if ((N-1+M-1) % 2) sum[N-1][M-1].S++;
    else sum[N-1][M-1].F++;
  }
  for (int i=N-1; i>=0; i--) {
    for (int j=M-1; j>=0; j--) {
      if (i==N-1 and j==M-1) continue;
      pii tmp = next_position(i, j);
      sum[i][j] = sum[tmp.F][tmp.S];
      if (!valid[i][j]) continue;
      if ((i+j)%2) sum[i][j].S++;
      else sum[i][j].F++;
    }
  }
  REP(i,N) sum[i][M] = sum[i+1][0];
}

bool go(int i, int j, int w, int b, int s) {
  assert(s < SZ(stateVec));
  if (pii(w, b) == tar && nCon[s] == 1) return true;
  if (w > tar.F || b > tar.S) return false;
  if (w + sum[i][j].F < tar.F || b + sum[i][j].S < tar.S) return false;
  if (i >= N) return false;
  if (dp[i][j][w][b].count(s)) return false;
  dp[i][j][w][b].insert(s);
  
  int ni, nj;
  tie(ni, nj) = next_position(i, j);
  int nw = w, nb = b;
  if ((i + j) % 2 == 0) nw++;
  else nb++;

  if (valid[i][j] && go(ni, nj, nw, nb, trans[j][s].S)) {
    use.PB({i, j});
    return true;
  }
  
  if (trans[j][s].F != -1) {
    if (go(ni, nj, w, b, trans[j][s].F))
      return true;
  }

  return false;
}
void output() {
  //cout << "=D" << endl;
  for (auto it:use) out[it.F][it.S] = 1;
  REP(i,N) {
    REP(j,M) {
      if (out[i][j]) {
        if ((i + j) % 2) cout << "X";
        else cout << "O";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
}

int main(int argc, char** argv) {
  IOS;
  cin >> N >> M >> K;
  REP(i,N) REP(j,M) valid[i][j] = 1;
  REP(i,K) {
    int u,v;
    cin >> u >> v;
    u--; v--;
    valid[u][v] = 0;
  }
  cin >> tar.F >> tar.S;

  predo();

  if (go(0, 0, 0, 0, 0)) output();
  else cout << ":-(" << endl;

  return 0;
}
