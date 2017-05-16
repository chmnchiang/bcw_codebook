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

const int MAXN = 2000005;
const int MID = MAXN/2;

int psum[MAXN], ss[MAXN], at[MAXN];
string s;

int score(int l, int r) {
  if (l>r) return 0;
  if (l == 0) return ss[r];
  return ss[r] - ss[l-1];
}
int main() {
  IOS;
  cin>>s;
  int n = SZ(s);
  REP(i,n) {
    if (s[i] == 'M') ss[i]++;
    else if (s[i] == 'H') psum[i]=1;
    else psum[i]=-1;
  }
  for (int i=1; i<n; i++) {
    psum[i] += psum[i-1];
    ss[i] += ss[i-1];
  }
  //REP(i,n) cout<<i<<" "<<psum[i]<<endl;
  REP(i,MAXN) at[i] = n;

  /* 
     REP(i,n) {
     int q = 0;
     int z = 0;
     REP1(j,i,n-1) {
     if (s[j] == 'H') q++;
     else if (s[j] == 'M') z++;
     else q--;
     if (q < 0) break;
     if (z == 3) {
     cout<<i<<" "<<j<<endl;
     REP1(k,i,j) cout<<psum[k]<<" ";
     cout<<endl;
     }
     }
     }

*/
  int ans = 0;
  for (int i=n-1; i>=0; i--) {
    at[psum[i]+MID] = i;
    if (s[i] == 'K') continue;
    int k = at[MID+(i ? psum[i-1] : 0)-1];
    k--;

    /*
       int q = 0;
       REP1(j,i,k) {
       if (s[j] == 'H') q++;
       else if (s[j] == 'K') q--;
       cout<<i<<" "<<k<<" "<<j<<" "<<q<<endl;
       assert(q >= 0);
       }
       cout<<i<<" "<<k<<" "<<score(i,k)<<endl;
       */

    ans = max(ans, score(i,k));
  }
  cout<<ans<<endl;

  return 0;
}

