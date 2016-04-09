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

const int MAXN = 505;

typedef pair<int, int> pii;

int K, N;
vector<pii> tree[MAXN];

void calc()
{
  N = 2 * K;
  for(int i=0; i<K; i++)
    tree[i].PB({2*i, 2*i+1});
  for(int i=0; i<K; i++)
  {
    for(int j=i+1; j<K; j++)
    {
      tree[i].PB({2*i, 2*j});
      tree[i].PB({2*i+1, 2*j+1});
      tree[j].PB({2*i+1, 2*j});
      tree[j].PB({2*i, 2*j+1});
    }
  }
}

int main() {
  IOS;

  cin>>K;
  calc();

  cout<<N<<endl;
  for(int i=0; i<K; i++)
    for(auto x: tree[i])
      cout<<x.F+1<<" "<<x.S+1<<"\n";

  return 0;
}

