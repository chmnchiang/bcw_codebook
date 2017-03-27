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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<ll, pii> umap_t;

const int MAXN = 101010;


int N, T;
ll P;
ll TI;
string S;
int arr[MAXN];
ll tipow[MAXN];
ll x[MAXN];
ll ans[MAXN];
int bx[MAXN], by[MAXN];
//unordered_map<ll, vector<int>> mp;
umap_t mp;

ll lpow(ll a, ll p)
{
  ll ret = 1, cur = a%P;
  while(p)
  {
    if(p&1LL) ret = ret * cur % P;
    cur = cur * cur % P;
    p >>= 1;
  }
  return ret;
}

ll linv(ll a)
{
  return lpow(a, P-2);
}

void calc()
{
  mp.clear();
  for(int i=0; i<T; i++)
  {
    bx[i] = -1;
    by[i] = 0;
  }

  ll s = 0;
  for(int i=0; i<=N; i++)
  {
    for(int j=0; j<T; j++)
    {
      ll val = ((s - x[j] + P) * tipow[i]) % P;
      auto it = mp.find(val);
      if(it != mp.end())
      {
        ans[j] += it->S.F;
        bx[j] = it->S.S;
        by[j] = i;
      }
    }

    if(i == N) break;
    auto &p = mp[(s * tipow[i]) % P];
    p.F++;
    p.S = i;
    s = (s * 10 + arr[i]) % P;
  }

  for(int i=0; i<T; i++)
    cout<<ans[i]<<" "<<bx[i]+1<<" "<<by[i]<<"\n";
}

int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;

  cin>>S>>T>>P;
  N = SZ(S);

  for(int i=0; i<N; i++)
    arr[i] = S[i] - '0';
  TI = linv(10);
  tipow[0] = 1;
  for(int i=1; i<=N; i++)
    tipow[i] = (tipow[i-1] * TI) % P;

  for(int i=0; i<T; i++)
    cin>>x[i];

  calc();

  return 0;
}

