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

const int MAXN = 30101;

int N, E;
int fval[MAXN];
int C = 0;
int es[MAXN], et[MAXN];
double ew[MAXN];
int layer[MAXN];
double val[MAXN];
vector<int> edges[MAXN];

int addnode(int x)
{
  C++;
  layer[C] = x;
  return C;
}

void addedge(int u, int v, double w)
{
  assert(layer[u] <= layer[v]);
  es[E] = u;
  et[E] = v;
  ew[E] = w;
  edges[v].PB(E);
  E++;
}

double eval()
{
  for(int i=N+1; i<=C; i++)
  {
    double x = 0;
    for(auto e: edges[i])
    {
      int u = es[e];
      double z = ew[e];
      x += val[u] * z;
    }
    val[i] = 1. / (1. + exp(-x));
    if(-x < -500) val[i] = 0;
  }

  return val[C];
}

int main() {
  IOS;
  cout<<fixed<<setprecision(2);

  cin>>N;
  string s;
  cin>>s;
  for(int i=0; i<(1<<N); i++)
    fval[i] = (s[i] == '1');

  int pos[150], neg[150], half;
  
  for(int i=1; i<=N; i++)
    pos[i] = addnode(1);
  for(int i=1; i<=N; i++)
  {
    neg[i] = addnode(2);
    addedge(pos[i], neg[i], -100);
  }
  half = addnode(3);
  //addedge(neg[1], half, 0);

  vector<int> cnd;

  for(int i=0; i<(1<<N); i++)
  {
    if(!fval[i]) continue;
    int nd = addnode(3);
    cnd.PB(nd);
    //addedge(pos[1], nd, 0);
    for(int j=0; j<N; j++)
    {
      if(i&(1<<j))
        addedge(neg[N-j], nd, -100);
      else
        addedge(pos[N-j], nd, -100);
    }
  }

  int nans = addnode(4);
  //addedge(pos[1], nans, 0);
  for(auto nd: cnd)
    addedge(nd, nans, -100);

  int ans = addnode(5);
  addedge(nans, ans, -200);
  addedge(half, ans, 100);

  assert(C <= 10000 and E <= 30000);

  int L = 5;
  cout<<L<<" "<<C<<endl;
  for(int i=1; i<=C; i++)
    cout<<layer[i]<<(i==C ? "\n" : " ");

  cout<<E<<endl;
  for(int i=0; i<E; i++)
    cout<<es[i]<<" "<<et[i]<<" "<<ew[i]<<endl;

  //cout<<setprecision(10);
  //for(int i=0; i<(1<<N); i++)
  //{
    //for(int j=0; j<N; j++)
      //val[N-j] = !!(i&(1<<j));
    //double x = eval();
    ////assert(!isnan(x));
    ////cout<<x<<endl;
    //assert(abs(x - fval[i]) <= 1E-10);
  //}

  return 0;
}

