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
// Let's Fight! ~OAO~~

using Arr = array<int, 4>;
using pii = pair<int, int>;

vector<Arr> possible, temp;

pii AB(Arr ans, Arr my) {
  int A = 0, B = 0;
  for (int i=0; i<4; i++) A += ans[i] == my[i];

  for (int i=0; i<4; i++)
    for (int j=0; j<4; j++) if (my[i] == ans[j]) {
      B++; break;
    }

  B -= A;
  return {A, B};
}

void filt(Arr ar, int a, int b) {
  temp.clear();
  for (auto x: possible) {
    if (AB(ar, x) == pii{a, b}) temp.PB(x);
  }
}

int qq[5][5];
int clas(Arr ar) {
  for (int i=0; i<=4; i++)
    for (int j=0; j<=4; j++) qq[i][j] = 0;

  for (auto x: possible) {
    auto t = AB(ar, x);
    qq[t.F][t.S]++;
  }

  int mx = 0;
  for (int i=0; i<=4; i++)
    for (int j=0; j<=4; j++) mx = max(mx, qq[i][j]);
  return mx;
}

void push(Arr res) {
  auto hao = res;
  sort(ALL(hao));
  for (int i=0; i<3; i++) if (hao[i] == hao[i+1]) return;

  possible.PB(res);
}


void answer(Arr a) {
  for (int i=0; i<4; i++) cout << a[i];
  cout << endl;

  string res; cin >> res;
  int A = res[0] - '0', B = res[1] - '0';
  if (res == "40") exit(0);
  filt(a, A, B);

  possible = temp;
}

int main() {
  IOS;

  for (int i=0; i<=9; i++)
  for (int j=0; j<=9; j++)
  for (int k=0; k<=9; k++)
  for (int l=0; l<=9; l++) push({i, j, k, l});

  answer(possible[0]);

  while (true) {
    int bv = 123123123;
    Arr bs;
    for (auto x: possible) {
      int t = clas(x);
      if (t < bv) {
        bv = t;
        bs = x;
      }
    }

    answer(bs);
  }
  

  return 0;
}

