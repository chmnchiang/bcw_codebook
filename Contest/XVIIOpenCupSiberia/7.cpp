//a34021501 {{{
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

struct LISAN {
  vector<int> dt;

  void PB(int x) {
    dt.PB(x);
  }

  void make() {
    sort(ALL(dt));
    dt.resize(unique(ALL(dt)) - begin(dt));
  }

  int operator () (int x) {
    return lower_bound(ALL(dt), x) - dt.begin();
  }
} lisan;

const int MX = 222222;
struct Node {
  int fa;
  set<int> ch;
} nds[MX];
int R;
set<int> root;

int N;

void connect(int f, int c) {
  auto &fa = nds[f], &ch = nds[c];
  fa.ch.insert(c);
  ch.fa = f;
}

void disconnect(int f, int c) {
  auto &fa = nds[f], &ch = nds[c];
  fa.ch.erase(c);
  ch.fa = -1;
}

void dfs0(int me) {
  root.insert(me);
  for (auto he: nds[me].ch) {
    dfs0(he);
  }
}

void input() {
  cin >> N;
  for (int i=0; i<N; i++) {
    nds[i].fa = -1;
  }
  vector<vector<int>> vec(N);
  for (int i=0; i<N; i++) {
    int t; cin >> t;
    vec[i].PB(t);
    lisan.PB(t);
    int x; cin >> x;
    for (int j=0; j<x; j++) {
      int k; cin >> k;
      vec[i].PB(k);
    }
  }
  lisan.make();

  for (int i=0; i<N; i++) {
    int me = lisan(vec[i][0]);
    for (int j=1; j<SZ(vec[i]); j++) {
      int he = lisan(vec[i][j]);
      connect(me, he);
    }
  }

  for (int i=0; i<N; i++) {
    if (nds[i].fa == -1) {
      R = i;
      break;
    }
  }

  dfs0(R);
}

vector<int> mod;

void add(int f, int c) {
  mod.PB(c);
  connect(f, c);
}

void remove(int f, int c) {
  mod.PB(c);
  disconnect(f, c);
}

vector<int> ans[3];
int rid;
int vt[MX];

void dfs(int me, bool ins) {
  if (vt[me] == rid) return;
  vt[me] = rid;


  bool prv = root.count(me);
  if (prv and ins) {
    ans[2].PB(me);
  } else if (ins) {
    root.insert(me);
    ans[0].PB(me);
  } else if (prv) {
    root.erase(me);
    ans[1].PB(me);
  } else {
    return;
  }

  for (auto he: nds[me].ch) {
    dfs(he, ins);
  }
}

void render() {
  for (int i=0; i<3; i++) ans[i].clear();
  rid++;
  for (auto x: mod) {
    int f = x;
    while (nds[f].fa != -1) {
      f = nds[f].fa;
    }
    bool ins = f == R;
    dfs(x, ins);
  }

  mod.clear();
  for (int i=0; i<3; i++) {
    sort(ALL(ans[i]));

    if (i == 0) cout << "added";
    else if (i == 1) cout << "removed";
    else cout << "modified";

    cout << ' ' << SZ(ans[i]);
    for (auto x: ans[i]) {
      cout << ' ' << lisan.dt[x];
    }
    cout << "\n";
  }
}

int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;

  input();

  int Q; cin >> Q;
  for (int i=0; i<Q; i++) {
    string op; cin >> op;
    if (op == "add") {
      int f, c; cin >> f >> c;
      f = lisan(f); c = lisan(c);
      add(f, c);
    } else if (op == "remove") {
      int f, c; cin >> f >> c;
      f = lisan(f); c = lisan(c);
      remove(f, c);
    } else if (op == "modify") {
      int c; cin >> c;
      c = lisan(c);
      mod.PB(c);
    } else {
      render();
    }
  }

  return 0;
}

