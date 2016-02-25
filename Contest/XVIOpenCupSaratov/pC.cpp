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

pii operator + (const pii &a, const pii &b) {
  return {a.F+b.F, a.S+b.S};
}
struct State {
  unsigned short wb;
  int s;
  bitset<101> ans;
  State () {
    ans.reset();
    s = wb = 0;
  }
  inline int operator [] (int p) const {
    int res = s >> (p * 3);
    res &= 0x7;
    return res;
  }
  void set(int p, int x) {
    s &= ~(0x7 << (p * 3));
    s |= x << (p * 3);
    assert(x < 8);
  }
  void addw() {
    setw(getw()+1);
  }
  void addb() {
    setb(getb()+1);
  }
  int getw() const {
    return wb & 0xFF;
  }
  int getb() const {
    return (wb >> 8) & 0xFF;
  }
  void setw(ll w) {
    wb &= ~0xFF;
    wb |= w;
  }
  void setb(ll b) {
    wb &= ~0xFF00;
    wb |= b << 8;
  }
  bool operator < (const State &he) const {
    return make_tuple(s, getw(), getb()) < make_tuple(he.s, he.getw(), he.getb());
  }
  bool operator == (const State &he) const {
    return make_tuple(s, getw(), getb()) == make_tuple(he.s, he.getw(), he.getb());
  }
  bool operator != (const State &he) const {
    return make_tuple(s, getw(), getb()) != make_tuple(he.s, he.getw(), he.getb());
  }
};
#ifdef DARKHH
ostream& operator << (ostream &s, const State &st) {
  s << "{ ";
  //s << st.i << " " << st.j << " " << ", ";
  s << "w : " << st.getw() << ", ";
  s << "con : [ ";
  for (int i=0; i<10; i++)
    s << st[i] << " ";
  cout << "] ";
  s << "ans : " << st.ans;
  s << " }";
  return s;
}
#endif

int N,M,K,valid[55][55];
pii tar,sum[55][55];
int out[55][55];

inline void reorder_vec(int &s) {
  int idx[12] = {0};
  int id = 0;
  REP(i,M) {
    int v = (s >> (i * 3)) & 0x7;
    if (v) {
      if (!idx[v]) idx[v] = ++id;
      s &= ~(0x7 << (i * 3));
      s |= ll(idx[v]) << (i * 3);
      assert(idx[v] < 8);
    }
  }
}
inline pii next_position(int i, int j) {
  j++;
  if (j >= M) {
    i++;
    j = 0;
  }
  return {i, j};
}

int solve() {
  State finState;
  vector<State> v[2];
  int u = 0;
  v[0].PB(State());
  if (valid[0][0]) {
    State s = State();
    s.set(0, 1);
    s.addw();
    s.ans[0] = 1;
    v[0].PB(s);
  }
  int ci = 0;
  int cj = -1;
  int ok = 0;
  int tot = 0;
  while (!ok && !v[u].empty()) {
    
    sort(ALL(v[u]));
    //v[u].resize(unique(ALL(v[u])) - begin(v[u]));
    
//    cout << SZ(v[u]) << endl;
    tot += SZ(v[u]);
    //cout << v[u] << endl;

    tie(ci, cj) = next_position(ci, cj);
    v[u^1].clear();
    int s1 = -1;
    int s2 = -1;
    State lstState;
    REP(curi,SZ(v[u])) {
      if (curi && v[u][curi] == v[u][curi-1]) continue;
      State st = v[u][curi];
      if (pii(st.getw(), st.getb()) == tar) {
        int fail=0;
        REP(i,M) {
          if (st[i] > 1) {
            fail = 1;
            break;
          }
        }
        if (fail) continue;
        finState = st;
        ok = 1;
        break;
      }
      if (ci >= N) continue;
      int kw = tar.F - st.getw();
      int kb = tar.S - st.getb();
      if (kw <= M/2 && kb >= M+5) continue;
      if (kb <= M/2 && kw >= M+5) continue;

      int i,j;
      tie(i, j) = next_position(ci, cj);

      // dont choose
      if (curi && st.s == lstState.s) {
        if (s1 != -1) {
          State nxt = st;
          auto tmp = next_position(i, j);
          if (nxt.getw() + sum[tmp.F][tmp.S].F >= tar.F and
              nxt.getb() + sum[tmp.F][tmp.S].S >= tar.S) {
            nxt.s = s1;
            v[u^1].PB(nxt);
          }
        }

      } else {
        int cnt = 0;
        REP(k,M) {
          if (st[k] == st[j])
            cnt++;
        }
        if (!st[j] || cnt >= 2) {
          State nxt = st;
          nxt.set(j, 0);
          reorder_vec(nxt.s);

          auto tmp = next_position(i, j);
          if (nxt.getw() + sum[tmp.F][tmp.S].F >= tar.F and
              nxt.getb() + sum[tmp.F][tmp.S].S >= tar.S) {
            v[u^1].PB(nxt);
          }
          s1 = nxt.s;
        } else {
          s1 = -1;
        }
      }
      // chooose (i, j)
      if (valid[i][j]) {
        if (curi && st.s == lstState.s) {
          if (s2 != -1) {
            State nxt = st;
            if ((i + j) % 2 == 0) nxt.addw();
            else nxt.addb();
            nxt.ans[i*M+j] = 1;
            nxt.s = s2;
            v[u^1].PB(nxt);
          }
        } else {
          State nxt = st;
          nxt.set(j, 7);
          if (j && nxt[j-1]) nxt.set(j, nxt[j-1]);
          int lst = st[j];
          if (lst) {
            int cur = nxt[j];
            REP(k,M) {
              if (nxt[k] == lst) nxt.set(k, cur);
            }
          }
          reorder_vec(nxt.s);
          nxt.ans[i*M+j] = 1;

          if ((i + j) % 2 == 0) nxt.addw();
          else nxt.addb();
          if (nxt.getw() <= tar.F && nxt.getb() <= tar.S) {
            v[u^1].PB(nxt);
            s2 = nxt.s;
          } else {
            s2 = -1;
          }
        }
      } else {
        s2 = -1;
      }

      lstState = st;
    }
    u ^= 1;
  }
  //cout << "TOTAL " << tot << endl;
  
  memset(out, 0, sizeof(out));
  
  for (int it = 0; it <= 100; it++) {
    if (finState.ans[it]) {
      int i = it / M;
      int j = it % M;
      out[i][j] = 1;
    }
  }

  return ok;
}
void output() {
  //cout << "=D" << endl;
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
int main() {
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

  if (solve()) output();
  else cout << ":-(" << endl;

  return 0;
}
