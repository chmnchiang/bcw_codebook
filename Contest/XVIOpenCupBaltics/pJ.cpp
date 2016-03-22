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

struct Lisan {
  vector<int> seq;
  void add(int x) { seq.PB(x); }
  void build() {
    sort(ALL(seq));
    seq.resize(unique(ALL(seq))-begin(seq));
  }
  int qry(int x) {
    return lower_bound(ALL(seq),x)-begin(seq);
  }
}lisan;

int N,M;
vector<int> ip,_at,ch[2],dep;
vector<int> bound;
vector<string> str;
set<int> lt,rt;
vector<vector<pii>> db;

void input() {
  int v;
  while (cin >> v) {
    ip.PB(v);
    lisan.add(v);
  }
  N = SZ(ip);
}
inline int at(int v) {
  return _at[lisan.qry(v)];
}
void prt_tree(int u) {
  if (u == -1) return;
  prt_tree(ch[0][u]);
  cout << ip[u] << " ";
  prt_tree(ch[1][u]);
}
int DFS(int u, int d) {
  if (u == -1) return 0;
  dep[u] = d;
  int b = SZ(str[u]);
  b += DFS(ch[0][u],d+1);
  b += DFS(ch[1][u],d+1);
  bound[u] = b;
  return b;
}
int go(int u, int base) {
  if (u == -1) return 0;
  int d = dep[u];
  base += go(ch[0][u],base);
  db[d].PB({base,u});
  base += SZ(str[u]);
  go(ch[1][u],base);
  return bound[u];
}
void calc() {
  lisan.build();
  str.resize(N);
  ch[0].resize(N);
  ch[1].resize(N);
  _at.resize(N);
  REP(i,N) {
    str[i] = to_string(ip[i]);
    _at[lisan.qry(ip[i])] = i;
    ch[0][i] = ch[1][i] = -1;
  }

  lt.insert(ip[0]);
  rt.insert(ip[0]);
  REP1(i,1,N-1) {
    int v = ip[i];
    auto it = lt.lower_bound(v);
    if (it != end(lt)) {
      ch[0][at(*it)] = i;
      lt.erase(it);
    } else {
      it = rt.lower_bound(v);
      assert(it != begin(rt));
      it--;
      ch[1][at(*it)] = i;
      rt.erase(it);
    }
    lt.insert(v);
    rt.insert(v);
  }
  // prt_tree(0);
  // cout << endl;
  bound.resize(N);
  dep.resize(N);
  DFS(0,0);
  M = 0;
  REP(i,N) M = max(M,dep[i]);
  M++;
  db.resize(M);
  go(0,0);
  // REP(i,N) cout << bound[i] << endl;
}
void draw() {
  REP(i,M) {
    int cur = 0;
    for (auto it:db[i]) {
      assert(cur <= it.F);
      while (cur < it.F) {
        cout << " ";
        cur++;
      }
      cout << str[it.S];
      cur += SZ(str[it.S]);
    }
    cout << "\n";
  }
}
int main() {
  IOS;
  input();
  calc();
  draw();

  return 0;
}

