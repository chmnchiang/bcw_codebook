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

using Arr = array<int,3>;
int N,M,K,c[514][514],done[514][514];
string mp[514];

int main() {
  IOS;
  cin>>N>>M>>K;
  REP(i,N) {
    cin>>mp[i];
  }
  REP(i,N) REP(j,M) c[i][j] = -1, done[i][j] = 0;
  priority_queue<Arr> pq;
  REP(_,K) {
    int x,y,z;
    cin>>x>>y>>z;
    x--; y--;
    c[x][y] = z;
    pq.push(Arr{z,x,y});
  }

  const int dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};
  while (!pq.empty()) {
    int x = pq.top()[1];
    int y = pq.top()[2];
    pq.pop();
    if (done[x][y]) continue;
    done[x][y] = 1;
    if (c[x][y] == 0) continue;
    REP(d,4) {
      int nx = x + dir[d][0];
      int ny = y + dir[d][1];
      if (nx < 0 or nx >= N or ny < 0 or ny >= M) continue;
      if (done[nx][ny]) continue;
      if (mp[nx][ny] == 'X') continue;
      if (c[nx][ny] < c[x][y] - 1) {
        c[nx][ny] = c[x][y] - 1;
        pq.push(Arr{c[nx][ny],nx,ny});
      }
    }
  }

  int ans = 0;
  REP(i,N) REP(j,M)
    if (c[i][j] >= 0) ans++;
  cout<<ans<<endl;

  return 0;
}

