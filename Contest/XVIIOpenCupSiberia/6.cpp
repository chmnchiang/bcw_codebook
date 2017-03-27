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

const int MX = 123123;
int B, M;
pii st[MX];
map<pii, int> mp;
map<pii, int> sid;

int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;

  cin >> B >> M;

  vector<pii> now;
  for (int i=0; i<M; i++) now.PB({i, i});
  
  int rnd = 0;
  int hao = 1;
  vector<pii> states;
  while (SZ(now)) {
    //cout << now << endl;
    vector<pii> nx;
    for (auto p: now) {
      int x = p.F, i = p.S;
      if ((M-x) % M < hao) {
        st[i] = {rnd, x};
        if (!mp.count(st[i])) {
          mp[st[i]] = i;
          int t = SZ(sid);
          sid[st[i]] = t;
          states.PB(st[i]);
        }
      } else {
        nx.PB({x*B % M, i});
      }
    }
    now = nx;
    hao *= B;
    rnd++;
  }

  int n = SZ(states);
  cout << n << ' ' << 0 << endl;
  cout << "G";
  for (int i=1; i<n; i++) {
    cout << " B";
  }
  cout << endl;
  for (auto s: states) {
    int x = mp[s];
    for (int i=0; i<B; i++) {
      int y = x * B + i;
      y %= M;
      int z = sid[st[y]];
      cout << z << " \n"[i == B-1];
    }
  }


  return 0;
}

