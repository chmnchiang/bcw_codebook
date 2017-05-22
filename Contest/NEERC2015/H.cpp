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

typedef array<int, 4> Point;

const int MAXN = 8;

Point operator+(Point a, Point b){
  Point c;
  for(int i=0; i<4; i++)
    c[i] = a[i] + b[i];
  return c;
}
Point operator-(Point a, Point b){
  Point c;
  for(int i=0; i<4; i++)
    c[i] = a[i] - b[i];
  return c;
}
int abs(Point a)
{
  int res = 0;
  for(int i=0; i<4; i++)
    res += abs(a[i]);
  return res;
}

int A, B, C;
int N;
Point pt[MAXN];
vector<int> edge[MAXN];
Point pset[MAXN][MAXN], qset[MAXN][MAXN];

vector<Point> intersect(Point *a, Point *b)
{
  vector<Point> res;
  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++)
      if(a[i] == b[j])
        res.PB(a[i]);
  return res;
}

void get_subtree(int v, int p, vector<int> &vec)
{
  vec.PB(v);
  for(auto c: edge[v])
  {
    if(c == p) continue;
    get_subtree(c, v, vec);
  }
}

bool dfs(int v, int p)
{
  for(auto c: edge[v])
  {
    if(c == p) continue;
    vector<int> st;
    get_subtree(c, v, st);
    //cout<<v<<" "<<c<<" SUBTREE "<<st<<endl;

    vector<Point> face = intersect(pset[v], pset[c]);
    assert(SZ(face) == 4);
    vector<int> axes;
    Point off;
    //cout<<face<<endl;
    for(int i=0; i<4; i++)
    {
      bool g = true;
      for(int j=1; j<4; j++)
        if(face[0][i] != face[j][i])
          g = false;
      if(g)
      {
        axes.PB(i);
        off[i] = face[0][i];
      }
      else
        off[i] = 0;
    }

    //cout<<"AXES "<<axes<<endl;
    assert(SZ(axes) == 2);
    int a = axes[0], b = axes[1];

    bool ok = false;
    for(int i=0; i<2; i++)
    {
      for(auto z: st)
      {
        for(int j=0; j<8; j++)
        {
          qset[z][j] = pset[z][j];
          qset[z][j] = qset[z][j] - off;
          swap(qset[z][j][a], qset[z][j][b]);
          if(i == 0)
            qset[z][j][a] *= -1;
          else
            qset[z][j][b] *= -1;
          qset[z][j] = qset[z][j] + off;
        }
      }

      bool good = true;
      for(int j=0; j<8; j++)
        for(int k=0; k<4; k++)
          if(qset[c][j][k] != 0 and qset[c][j][k] != 1)
            good = false;

      if(good)
      {
        ok = true;
        break;
      }
    }

    if(!ok) return false;
    for(auto z: st)
      for(int j=0; j<8; j++)
        pset[z][j] = qset[z][j];

    bool res = dfs(c, v);
    if(!res) return false;
  }

  return true;
}

int main() {
#ifndef HAO123
  FILEIO("hypercube");
#endif
  IOS;

  while(cin>>C>>B>>A)
  {
    N = 0;
    for(int i=0; i<A; i++)
    {
      for(int j=0; j<B; j++)
      {
        string s;
        cin>>s;
        for(int k=0; k<C; k++)
        {
          if(s[k] == 'x')
          {
            pt[N] = Point{i, j, k, 0};
            N++;
          }
        }
      }
    }

    for(int i=N-1; i>=0; i--)
      pt[i] = pt[i] - pt[0];

    for(int i=0; i<N; i++)
      edge[i].clear();

    for(int i=0; i<N; i++)
    {
      for(int j=i+1; j<N; j++)
      {
        if(abs(pt[i] - pt[j]) == 1)
        {
          edge[i].PB(j);
          edge[j].PB(i);
        }
      }
    }

    for(int i=0; i<N; i++)
    {
      for(int j=0; j<8; j++)
      {
        pset[i][j] = pt[i];
        if(j&1) pset[i][j][0]++;
        if(j&2) pset[i][j][1]++;
        if(j&4) pset[i][j][2]++;
      }
    }

    bool res = dfs(0, -1);

    for(int i=0; i<N; i++)
      for(int j=i+1; j<N; j++)
        if(SZ(intersect(pset[i], pset[j])) == 8)
          res = false;

    cout<<(res ? "Yes" : "No")<<endl;
  }

  return 0;
}

