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

const int MAXN = 333333;
const int BLK = 1024;
const int INF = 1029384756;

typedef bitset<BLK> BS;

int R, C, N;
string arr[444];
int ans[444][444];
int deg[MAXN];
vector<int> edge[MAXN], rdge[MAXN];
BS vis[MAXN];
int cnt[MAXN];

int get_idx(int i, int j, int k){return 2*C*i+2*j+k;}
bool inrange(int i, int j){return i>=0 and i<R and j>=0 and j<C;}

void calc()
{
  N = 2*R*C;
  for(int i=0; i<N; i++)
  {
    edge[i].clear();
    rdge[i].clear();
    deg[i] = 0;
    cnt[i] = 0;
  }

  for(int i=0; i<R; i++)
  {
    for(int j=0; j<C; j++)
    {
      for(int k=0; k<2; k++)
      {
        int v = get_idx(i, j, k);
        if(k == 0)
        {
          if(inrange(i-1, j)) edge[v].PB(get_idx(i-1, j, 0));
        }
        else
        {
          if(inrange(i+1, j)) edge[v].PB(get_idx(i+1, j, 1));
        }

        if((k == 0) ^ (arr[i][j] == 'Z'))
        {
          if(inrange(i, j+1)) edge[v].PB(get_idx(i, j+1, arr[i][j+1] == 'Z'));
        }
        else
        {
          if(inrange(i, j-1)) edge[v].PB(get_idx(i, j-1, arr[i][j-1] == 'N'));
        }
      }
    }
  }

  for(int i=0; i<N; i++)
  {
    deg[i] = SZ(edge[i]);
    for(auto c: edge[i])
    {
      rdge[c].PB(i);
    }
  }

  queue<int> q;
  for(int i=0; i<N; i++)
    if(deg[i] == 0)
      q.push(i);

  vector<int> vec;

  while(!q.empty())
  {
    int v = q.front();
    q.pop();
    vec.PB(v);
    for(auto c: rdge[v])
    {
      deg[c]--;
      if(deg[c] == 0)
        q.push(c);
    }
  }

  int V = SZ(vec);

  for(int lb=0; lb<V; lb+=BLK)
  {
    int rb = min(lb+BLK, V);
    for(int i=0; i<N; i++)
      vis[i].reset();

    for(int i=lb; i<rb; i++)
      vis[vec[i]].set(i-lb);

    for(auto v: vec)
    {
      for(auto e: edge[v])
        vis[v] |= vis[e];
      cnt[v] += vis[v].count();
    }
  }

  for(int i=0; i<R; i++)
  {
    for(int j=0; j<C; j++)
    {
      ans[i][j] = INF;
      int c1 = cnt[get_idx(i, j, 0)];
      if(c1 > 0) ans[i][j] = min(ans[i][j], c1);
      int c2 = cnt[get_idx(i, j, 1)];
      if(c2 > 0) ans[i][j] = min(ans[i][j], c2);
      if(ans[i][j] == INF)
        ans[i][j] = -1;
      else
        ans[i][j] *= 2;
    }
  }
}

int main() {
  IOS;

  while(cin>>R>>C)
  {
    for(int i=0; i<R; i++)
      cin>>arr[i];

    calc();
    for(int i=0; i<R; i++)
      for(int j=0; j<C; j++)
        cout<<ans[i][j]<<" \n"[j==C-1];
  }

  return 0;
}

