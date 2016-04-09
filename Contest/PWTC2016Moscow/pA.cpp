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

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

typedef long long ll;

const int MAXN = 204;
const ll MOD = 1234567891;

int N, M;
ll arr[MAXN][MAXN];

ll pinv(ll a)
{
  ll cur = a, ret = 1, p = MOD-2;
  while(p)
  {
    if(p&1LL)
      ret = (ret * cur) % MOD;
    cur = (cur * cur) % MOD;
    p >>= 1;
  }
  return ret;
}

int calc()
{
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      arr[i][j] = (arr[i][j] + MOD) % MOD;

  int rank = 0;

  for(int i=0; i<M; i++)
  {
    int piv = -1;
    for(int j=rank; j<N; j++)
      if(arr[j][i] != 0)
        piv = j;
    if(piv == -1) continue;
    swap(arr[rank], arr[piv]);

    ll rat = pinv(arr[rank][i]);
    for(int j=0; j<M; j++)
      arr[rank][j] = (arr[rank][j] * rat) % MOD;
    for(int j=0; j<N; j++)
    {
      if(j == rank) continue;
      rat = (MOD - arr[j][i]) % MOD;
      for(int k=0; k<M; k++)
        arr[j][k] = (arr[j][k] + rat * arr[rank][k]) % MOD;
    }

    rank++;
  }

  return rank;
}

int main() {
  IOS;

  cin>>N>>M;
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      cin>>arr[i][j];

  int ans = calc();
  cout<<ans<<endl;

  return 0;
}

