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

int arr[6][6], brr[6][6];
int rperm[6], cperm[6];

bool dfs(int x, int y)
{
  if(y == 6)
  {
    for(int i=0; i<x; i++)
    {
      int cnt = 0;
      for(int j=0; j<6; j++)
        cnt += (arr[i][j] != arr[x][j]);
      if(cnt < 3) return false;
    }
    return dfs(x+1, 0);
  }
  if(x == 6) 
  {
    for(int i=0; i<6; i++)
    {
      for(int j=i+1; j<6; j++)
      {
        int cnt = 0;
        for(int k=0; k<6; k++)
          cnt += (arr[k][i] != arr[k][j]);
        if(cnt < 3) return false;
      }
    }
    return true;
  }

  arr[x][y] = 0;
  if(dfs(x, y+1)) return true;
  arr[x][y] = 1;
  if(dfs(x, y+1)) return true;
  return false;
}

void pre()
{
  dfs(0, 0);
  for(int i=0; i<6; i++)
  {
    for(int j=0; j<6; j++)
      cout<<(arr[i][j] ? 'B' : 'A');
    cout<<endl;
  }
}

bool check_row()
{
  for(int i=0; i<6; i++)
  {
    rperm[i] = -1;
    for(int j=0; j<6; j++)
    {
      int cnt = 0;
      for(int k=0; k<6; k++)
        cnt += (brr[i][k] != arr[j][k]);
      if(cnt <= 1)
        rperm[i] = j;
    }
    if(rperm[i] == -1) return false;
  }
  for(int i=0; i<6; i++)
    for(int j=i+1; j<6; j++)
      if(rperm[i] == rperm[j])
        return false;
  return true;
}

bool check_col()
{
  for(int i=0; i<6; i++)
  {
    cperm[i] = -1;
    for(int j=0; j<6; j++)
    {
      int cnt = 0;
      for(int k=0; k<6; k++)
        cnt += (brr[k][i] != arr[k][j]);
      if(cnt <= 1)
        cperm[i] = j;
    }
    if(cperm[i] == -1) return false;
  }
  for(int i=0; i<6; i++)
    for(int j=i+1; j<6; j++)
      if(cperm[i] == cperm[j])
        return false;
  return true;
}

int main() {
  IOS;

  pre();

  while(1)
  {
    string op;
    cin>>op;
    if(op == "Accepted") break;

    string s;
    for(int i=0; i<6; i++)
    {
      cin>>s;
      for(int j=0; j<6; j++)
        brr[i][j] = (s[j] == 'B');
    }

    bool row_ok = check_row();
    bool col_ok = check_col();

    if(row_ok and col_ok) cout<<0<<endl;
    else if(row_ok) cout<<1<<endl;
    else if(col_ok) cout<<2<<endl;
    else assert(false);

    if(row_ok)
    {
      for(int i=0; i<6; i++)
        cout<<(rperm[i]+1)<<(i==5 ? "" : " ");
      cout<<endl;
    }
    if(col_ok)
    {
      for(int i=0; i<6; i++)
        cout<<(cperm[i]+1)<<(i==5 ? "" : " ");
      cout<<endl;
    }
  }

  return 0;
}

