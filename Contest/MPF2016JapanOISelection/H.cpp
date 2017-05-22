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

using A34 = array<int,3>;
const int MAXN = 1024;
const int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
const int INF = 1029384756;

int N,M,stx,sty,edx,edy,done[MAXN][MAXN];
int dis[MAXN][MAXN];
pii dp[MAXN][MAXN][4];
string mp[MAXN];

pii go(int x, int y, int d) {
  int nx = x + dir[d][0];
  int ny = y + dir[d][1];
  assert(0 <= nx and nx < N);
  assert(0 <= ny and ny < M);
  if (mp[nx][ny] == '#') return pii{x,y};
  if (dp[x][y][d].F != -1) return dp[x][y][d];
  return dp[x][y][d] = go(nx,ny,d);
}
int main() {
  IOS;
  while (cin>>N>>M) {
    REP(i,N) {
      cin>>mp[i];
      REP(j,M) {
        REP(d,4) {
          dp[i][j][d] = pii(-1,-1);
        }
        dis[i][j] = INF;
        done[i][j] = 0;
      }
    }
    cin>>stx>>sty;
    cin>>edx>>edy;
    stx--; sty--;
    edx--; edy--;

    priority_queue<A34> pq;
    pq.push(A34{0,stx,sty});
    dis[stx][sty] = 0;

    while (!pq.empty()) {
      int x = pq.top()[1];
      int y = pq.top()[2];
      pq.pop();
      if (done[x][y]) continue;
      done[x][y] = 1;
      REP(d,4) {
        auto z = go(x,y,d);
        int nx = z.F;
        int ny = z.S;
        if (!done[nx][ny] and dis[nx][ny] > dis[x][y] + 1) {
          dis[nx][ny] = dis[x][y] + 1;
          pq.push(A34{-dis[nx][ny],nx,ny});
        }
        nx = x + dir[d][0];
        ny = y + dir[d][1];
        if (mp[nx][ny] != '#' and !done[nx][ny] and dis[nx][ny] > dis[x][y] + 2) {
          dis[nx][ny] = dis[x][y] + 2;
          pq.push(A34{-dis[nx][ny],nx,ny});
        }
      }
    }
    int res = dis[edx][edy];
    if (res == INF) cout<<-1<<endl;
    else cout<<(res)<<endl;
  }

  return 0;
}

