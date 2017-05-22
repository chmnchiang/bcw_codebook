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
typedef pair<int, pii> pip;

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

const int MAXN = 101010;
const int INF = 1029384756;

int N, Q;
int ans[MAXN];
vector<int> E[MAXN];
int disa[MAXN], disb[MAXN];

bool inr(int x, int a, int b)
{
  return a <= x and x <= b;
}

void calc_dis(int n, int r, int *dis)
{
  for(int i=0; i<n; i++)
    dis[i] = INF;
  dis[r] = 0;
  queue<int> q;
  q.push(r);
  while(!q.empty())
  {
    int v = q.front();
    q.pop();
    for(auto c: E[v])
    {
      if(dis[c] == INF)
      {
        dis[c] = dis[v] + 1;
        q.push(c);
      }
    }
  }
}


void calc(int n, vector<pii> &edge, vector<pip> &qry)
{
  if(n == 3)
  {
    for(auto p: qry)
    {
      int id = p.F;
      if(p.S.F == p.S.S) ans[id] = 0;
      else ans[id] = 1;
    }
    return;
  }
  int mxdis = 0;
  int a = -1, b = -1;
  for(auto e: edge)
  {
    int x, y;
    tie(x, y) = e;
    int dis = min(y - x, n + x - y);
    if(dis > mxdis)
    {
      mxdis = dis;
      a = x;
      b = y;
    }
  }

  for(int i=0; i<n; i++)
    E[i].clear();
  for(int i=0; i<n; i++)
  {
    int j = (i+1) % n;
    E[i].PB(j);
    E[j].PB(i);
  }
  for(auto e: edge)
  {
    E[e.F].PB(e.S);
    E[e.S].PB(e.F);
  }

  calc_dis(n, a, disa);
  calc_dis(n, b, disb);

  int nl = b-a+1, nr = a+n-b+1;
  vector<pii> el, er;
  vector<pip> ql, qr;

  for(auto e: edge)
  {
    int x = e.F, y = e.S;
    if(inr(x, a, b) and inr(y, a, b))
      el.PB({x-a, y-a});
    else
    {
      x = (x+n-b) % n;
      y = (y+n-b) % n;
      if(x > y) swap(x, y);
      er.PB({x, y});
    }
  }

  for(auto q: qry)
  {
    int id = q.F, x = q.S.F, y = q.S.S;
    if(y == a or y == b)
      swap(x, y);
    if(x == a)
    {
      ans[id] = disa[y];
      continue;
    }
    if(x == b)
    {
      ans[id] = disb[y];
      continue;
    }
    bool i1 = inr(x, a, b), i2 = inr(y, a, b);
    if(i1 ^ i2)
    {
      ans[id] = min(disa[x] + disa[y], disb[x] + disb[y]);
      continue;
    }

    if(i1)
      ql.PB({id, {x-a, y-a}});
    else
      qr.PB({id, {(x+n-b)%n, (y+n-b)%n}});
  }

  calc(nl, el, ql);
  calc(nr, er, qr);
}

int main() {
#ifndef HAO123
  FILEIO("distance");
#endif
  IOS;

  cin>>N;
  vector<pii> edge;
  for(int i=0; i<N-3; i++)
  {
    int x, y;
    cin>>x>>y;
    x--;
    y--;
    if(x > y) swap(x, y);
    edge.PB({x, y});
  }
  cin>>Q;
  vector<pip> qry;
  for(int i=0; i<Q; i++)
  {
    int x, y;
    cin>>x>>y;
    x--;
    y--;
    qry.PB({i, {x, y}});
  }

  calc(N, edge, qry);

  for(int i=0; i<Q; i++)
    cout<<ans[i]<<"\n";

  return 0;
}

