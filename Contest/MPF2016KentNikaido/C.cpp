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

ll C[7], x[7];
bool vis[7];
vector<int> edge[7];

void dfs(int v)
{
  if(vis[v]) return;
  vis[v] = true;
  for(auto e: edge[v])
    dfs(e);
}

bool calc()
{
  for(int i=0; i<7; i++)
  {
    edge[i].clear();
    vis[i] = false;
  }
  if(C[0] == 0) return false;
  C[0]--;

  x[0] = C[0] - C[6] + C[5] - C[4] + C[3] - C[2] + C[1];
  for(int i=1; i<7; i++)
    x[i] = 2 * C[i] - x[i-1];

  for(int i=0; i<7; i++)
    if(x[i] < 0)
      return false;

  for(int i=0; i<7; i++)
  {
    int j = (i+1)%7;
    if(x[i] > 0)
    {
      edge[i].PB(j);
      edge[j].PB(i);
    }
  }

  dfs(0);
  for(int i=0; i<7; i++)
    if(!edge[i].empty() and !vis[i])
      return false;

  return true;
}

int main() {
  IOS;

  while(cin>>C[0])
  {
    for(int i=1; i<7; i++)
      cin>>C[i];

    bool ans = calc();
    cout<<(ans ? "YES" : "NO")<<endl;
  }

  return 0;
}


