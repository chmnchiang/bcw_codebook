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

const int MX = 55555;
vector<int> el[MX];

using pii = pair<int, int>;
const int MD = 5;

int id(pii p) {
  return p.S*MD + p.F;
}

pii topr(int id) {
  return {id%MD, id/MD};
}

void add_edge(pii p1, pii p2) {
  int u = id(p1), v = id(p2);
  el[u].PB(v);
  el[v].PB(u);
}

bool vt[MX];
vector<pii> ans;

void dfs(int u, int fa) {
  if (vt[u]) {
    assert(u == id({1, 1}));
    return;
  }
  ans.PB(topr(u));

  vt[u] = 1;

  for (auto v: el[u]) {
    if (v == fa) continue;
    return dfs(v, u);
  }
}

pii tr(pii p) {
  return {5 - p.F, p.S};
}

pii sh(pii p, int s) {
  return {p.F, p.S+s};
}

const pii Z1[] = {
  {1, 1}, {2, 3}, {4, 2}, {3, 4}
};
const pii Z2[] = {
  {3, 2}, {1, 3}
};
void build(int s) {
  for (int i=0; i<3; i++) {
    add_edge(sh(Z1[i], s), sh(Z1[i+1], s)); 
    add_edge(tr(sh(Z1[i], s)), tr(sh(Z1[i+1], s))); 
  }
  add_edge(sh(Z2[0], s), sh(Z2[1], s)); 
  add_edge(tr(sh(Z2[0], s)), tr(sh(Z2[1], s))); 
}


int main() {
  IOS;

  int N;
  cin >> N;

  if (N == 2) {
    const pii Ps[] = {
      {1, 1}, {3, 2}, {1, 1}
    };

    for (int i=0; i<2; i++) {
      add_edge(Ps[i], Ps[i+1]);
    }
  } else if (N == 3) {
    const pii Ps[] = {
      {1, 1}, {2, 3}, {3, 1}, {4, 3}, {2, 2},
      {4, 1}, {3, 3}, {2, 1}, {1, 3}, {3, 2}, {1, 1}
    };

    for (int i=0; i<10; i++) {
      add_edge(Ps[i], Ps[i+1]);
    }
  } else if (N % 2 == 0) {
    const pii Ps[] = {
      {1, 3}, {3, 2}, {1, 1}, {2, 3}, {3, 1}, {1, 2}, {2, 4}
    };
    
    for (int i=0; i<6; i++) {
      add_edge(Ps[i], Ps[i+1]);
      add_edge(tr(Ps[i]), tr(Ps[i+1]));
      //add_edge(Qs[i], Qs[i+1]);
      //add_edge(tr(Qs[i]), tr(Qs[i+1]));
    }

    for (int i=2; i<N-2; i+=2) {
      build(i);
    }
    add_edge({2, N}, {4, N-1});
    add_edge({3, N}, {1, N-1});
  } else {

    const pii Ps[] = {
      {1, 4}, {3, 3}, {4, 1}, {2, 2}, {3, 4}, {4, 2}, {2, 1}, {1, 3}, {2, 5}
    };
    
    for (int i=0; i<8; i++) {
      add_edge(Ps[i], Ps[i+1]);
      add_edge(tr(Ps[i]), tr(Ps[i+1]));
    }

    for (int i=3; i<N-2; i+=2) {
      build(i);
    }
    add_edge({2, N}, {4, N-1});
    add_edge({3, N}, {1, N-1});
  }

  dfs(id({1, 1}), -1);
  assert(N == 2 or SZ(ans) == 4*N-2);

  cout << SZ(ans) << endl;
  for (auto p: ans) {
    cout << p.F << ' ' << p.S << ' ';
  }
  cout << 1 << ' ' << 1 << endl;

  return 0;
}

