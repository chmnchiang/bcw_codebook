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

const int MAXN = 1010;

int N;
string cs;
string _s;
bool dif[MAXN];

void swap(string &s, int pos)
{
  if(s[pos] == '1') s[pos] = '0';
  else s[pos] = '1';
}

bool query(string s)
{
  int res = 0;
#ifdef HAO123
  for(int i=0; i<N; i++)
    if(s[i] == _s[i])
      res++;
  if(res != N and res != N/2)
    res = 0;
  if(res == N) cout<<"Hao123"<<endl;
#else
  cout<<s<<endl;
  cin>>res;
#endif
  if(res == N) exit(0);
  return res;
}

int main() {
  IOS;
  srand(time(0));
  cin>>N;

#ifdef HAO123
  for(int i=0; i<N; i++)
    _s.PB(rand()%2 ? '1' : '0');
#endif

  int cnt = 0;
  while(1)
  {
    cs.clear();
    for(int i=0; i<N; i++)
      cs.PB(rand()%2 ? '1' : '0');
    bool ok = false;
    for(int i=0; i<1; i++)
    {
      cnt++;
      swap(cs, i);
      int res = query(cs);
      if(res)
      {
        ok = true;
        break;
      }
    }
    if(ok) break;
  }

  for(int i=1; i<N; i++)
  {
    string s = cs;
    swap(s, 0);
    swap(s, i);
    int res = query(s);
    dif[i] = (res > 0);
  }

  for(int i=0; i<N; i++)
    if(dif[i])
      swap(cs, i);
  query(cs);

  for(int i=0; i<N; i++)
    swap(cs, i);
  query(cs);

  return 0;
}

