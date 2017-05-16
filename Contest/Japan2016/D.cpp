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

#define int long long
const int P[2] = {938241347, 1000000007};
int Q[2][30];

static void init() {
  for (int i=0; i<26; i++) {
    Q[0][i] = abs(rand() * 32768 + rand()) % P[0];
    Q[1][i] = abs(rand() * 32768 + rand()) % P[1];
  }
}

string S, T;
int N, M;
using pii = pair<int, int>;

set<pii> st;

inline void add(int &x, int y, int p) {
  x += y;
  if (x >= p) x -= p;

}
bool check(int l) {
  st.clear();

  int sm[2] = {};
  for (int i=0; i<l-1; i++) {
    int c = S[i] - 'a';
    for (int j=0; j<2; j++) {
      add(sm[j], Q[j][c], P[j]);
    }
  }

  for (int i=l-1; i<N; i++) {
    for (int j=0; j<2; j++) {
      add(sm[j], Q[j][S[i] - 'a'], P[j]);
    }
    st.insert({sm[0], sm[1]});

    for (int j=0; j<2; j++) {
      add(sm[j], P[j] - Q[j][S[i-l+1] - 'a'], P[j]);
    }
  }

  sm[0] = sm[1] = 0;
  for (int i=0; i<l-1; i++) {
    int c = T[i] - 'a';
    for (int j=0; j<2; j++) {
      add(sm[j], Q[j][c], P[j]);
    }
  }

  for (int i=l-1; i<M; i++) {
    for (int j=0; j<2; j++) {
      add(sm[j], Q[j][T[i] - 'a'], P[j]);
    }
    if (st.count({sm[0], sm[1]})) return 1;

    for (int j=0; j<2; j++) {
      add(sm[j], P[j] - Q[j][T[i-l+1] - 'a'], P[j]);
    }
  }
  return 0;
}
int32_t main() {
  IOS;
  init();
  cin >> S >> T;
  N = SZ(S); M = SZ(T);
  for (int i=min(N, M); i>=0; i--) {
    if (check(i)) {
      cout << i << endl;
      return 0;
    }
  }
  cout << 0 << endl;

  return 0;
}

