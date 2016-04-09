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

typedef long double ld;

const int MAXN = 1010101;
const ld l2 = logl(2);

int W, H, N;
ld logfact[MAXN];

void pre()
{
  logfact[0] = 0;
  for(int i=1; i<MAXN; i++)
    logfact[i] = logfact[i-1] + logl(i);
}

ld comb(int n, int m)
{
  return expl(logfact[n] - logfact[m] - logfact[n-m] - n * l2);
}

ld calc()
{
  ld ans = 0;
  for(int i=0; i<=N; i++)
    ans += comb(N, i) / ((ld)(i+1) * (i+1) * (N-i+1) * (N-i+1));

  ans *= W * H;

  return ans;
}

int main() {
  IOS;
  pre();

  cin>>W>>H>>N;
  ld ans = calc();
  cout<<fixed<<setprecision(50)<<ans<<endl;

  return 0;
}

