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


int N;
string ip,s;
char trans[255];
int dpE[33][33], dpT[33][33], dpF[33][33], dpN[33][33], dpB[33][33];
ll valE[33][33], valT[33][33], valF[33][33], valN[33][33], valB[33][33];
vector<int> cset = {'=', '+', '-', '*', '(', ')', '0', '1'};

bool isc(char x) {
  return find(ALL(cset),x) != end(cset);
}

int main() {
  IOS;
  cin>>ip;
  N = SZ(ip);
  vector<int> vec;
  REP(i,N) {
    if (!isc(ip[i])) vec.PB(ip[i]);
  }

  sort(ALL(vec));
  vec.resize(unique(ALL(vec))-begin(vec));
  if (SZ(vec) > SZ(cset)) {
    cout<<0<<endl;
  } else {
    sort(ALL(cset));

    int ans = 0;
    vector<int> prv = {-1,-1};
    do {
      {
        auto tmp = cset;
        tmp.resize(SZ(vec));
        if (tmp == prv) continue;
        prv = tmp;
      }
      REP(i,SZ(vec)) {
        trans[vec[i]] = cset[i];
      }
      s = ip;
      REP(i,N) {
        if (!isc(s[i])) s[i] = trans[(int)s[i]];
      }

      if (count(ALL(s), '=') != 1) continue;

      memset(dpE,0,sizeof(dpE));
      memset(dpT,0,sizeof(dpT));
      memset(dpF,0,sizeof(dpF));
      memset(dpN,0,sizeof(dpN));
      memset(dpB,0,sizeof(dpB));

      dpB[N][N] = 1;
      valB[N][N] = 0;
      REP(len,N + 1) REP(i,N) {
        int j = i + len;
        if (j>N) continue;
        if (i == j) {
          dpB[i][j] = 1;
          valB[i][j] = 0;
        }
        if (j > i and (s[i] == '0' or s[i] == '1') and dpB[i+1][j]) {
          dpB[i][j] = 1;
          valB[i][j] = (((s[i]-'0') * 1LL) << (len-1)) + valB[i+1][j];
        }

        if (s[i] == '0' and i == j-1) {
          dpN[i][j] = 1;
          valN[i][j] = 0;
        }
        if (j > i and s[i] == '1' and dpB[i+1][j]) {
          dpN[i][j] = 1;
          valN[i][j] = (1LL << (len - 1)) + valB[i+1][j];
        }

        if (dpN[i][j]) {
          dpF[i][j] = 1;
          valF[i][j] = valN[i][j];
        }
        if (j > i and s[i] == '-' and dpF[i+1][j]) {
          dpF[i][j] = 1;
          valF[i][j] = -valF[i+1][j];
        }
        if (j - i > 2 and s[i] == '(' and s[j-1] == ')' and dpE[i+1][j-1]) {
          dpF[i][j] = 1;
          valF[i][j] = valE[i+1][j-1];
        }

        if (dpF[i][j]) {
          dpT[i][j] = 1;
          valT[i][j] = valF[i][j];
        }
        REP1(k,i,j-1) {
          if (s[k] == '*' and dpT[i][k] and dpF[k+1][j]) {
            dpT[i][j] = 1;
            valT[i][j] = valT[i][k] * valF[k+1][j];
          }
          if (dpT[i][j]) break;
        }

        if (dpT[i][j]) {
          dpE[i][j] = 1;
          valE[i][j] = valT[i][j];
        }
        REP1(k,i,j-1) {
          if ((s[k] == '+' or s[k] == '-') and dpE[i][k] and dpT[k+1][j]) {
            dpE[i][j] = 1;
            if (s[k] == '+') valE[i][j] = valE[i][k] + valT[k+1][j];
            if (s[k] == '-') valE[i][j] = valE[i][k] - valT[k+1][j];
          }
          if (dpE[i][j]) break;
        }
      }

      int ok = 0;
      REP1(i,1,N-1) {
        if (s[i] == '=' and dpE[0][i] and dpE[i+1][N]) {
          ll A = valE[0][i];
          ll B = valE[i+1][N];
          if (A != B) continue;
          ok = 1;
          break;
        }
      }

      if (ok) ans++;

    } while (next_permutation(ALL(cset)));

    cout<<ans<<endl;
  }

  return 0;
}

