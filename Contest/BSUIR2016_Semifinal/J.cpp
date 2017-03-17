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

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAXN = 305;

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
pll operator*(pll a, ll b){return {a.F*b, a.S*b};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
ll abs2(pll a){return dot(a, a);}
double abs(pll a){return sqrt(abs2(a));}

int N;
pll pt[MAXN];
pll rpt[MAXN];
int ord[MAXN*2];
int bel[MAXN][MAXN];

bool cmp(int a, int b)
{
  int pa = (rpt[a].S < 0 or (rpt[a].S == 0 and rpt[a].F < 0));
  int pb = (rpt[b].S < 0 or (rpt[b].S == 0 and rpt[b].F < 0));
  if(pa != pb) return pa < pb;
  return cross(rpt[a], rpt[b]) > 0;
}

void calc()
{
  for(int v=0; v<N; v++)
  {
    for(int i=0; i<N; i++)
      rpt[i] = pt[i] - pt[v];

    for(int i=0; i<N; i++)
      ord[i] = i;
    swap(ord[v], ord[N-1]);
    sort(ord, ord+N-1, cmp);
    for(int i=0; i<N-1; i++)
      ord[i+N-1] = ord[i];

    for(int i=0; i<N-1; i++)
    {
      int p = ord[i];
      int lb = i;
      while(lb < i+N-1 and cross(rpt[p], rpt[ord[lb]]) >= 0) lb++;
      int rb = lb;

      bel[p][v] = 0;
      for(int j=i+1; j<i+N-1; j++)
      {
        int a = ord[j];
        if(cross(rpt[p], rpt[ord[j]]) <= 0) continue;
        while(rb < i+N-1 and cross(rpt[a], rpt[ord[rb]]) > 0) rb++;

        int num = rb - lb;
        bel[p][v] += num;
      }
    }
  }
}

double get_ans(int v)
{
  int tot = 0;
  double totdis = 0;
  for(int i=0; i<N; i++)
  {
    if(i == v) continue;
    tot += bel[v][i];
    totdis += bel[v][i] * abs(pt[i] - pt[v]);
    //cout<<"BEL "<<v<<" "<<i<<" = "<<bel[v][i]<<endl;
  }

  if(tot == 0) return -1;
  double ret = totdis / tot;
  return ret;
}

int main() {
  IOS;

  cin>>N;
  for(int i=0; i<N; i++)
    cin>>pt[i].F>>pt[i].S;

  calc();

  cout<<fixed<<setprecision(10);
  for(int i=0; i<N; i++)
  {
    double ans = get_ans(i);
    if(ans < -0.5) cout<<-1<<endl;
    else cout<<ans<<endl;
  }


  return 0;
}

