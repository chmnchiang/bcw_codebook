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

#define int long long
int A, B;
vector<int> ans;

void go(int z) {
  if (z == 1) return;

  int aa = z/2;
  int a1=aa*2, a2=a1+1;
  ans.PB(a1 == z ? a2 : a1);
  return go(aa);
}

void go(int a, int b) {
  if (a == b) return;
  if (a < b) return go(b, a);
  if (__lg(a) == __lg(b)) {
    int z = a / 2;
    if (z*2+1 == a and z*2 == b) return go(z);
  }

  int aa = a / 2;
  int a1 = aa*2, a2=aa*2+1;
  ans.PB(a1 == a ? a2 : a1);
  return go(aa, b);
}
bool judge(int a, int b) {
  if (a > b) swap(a, b);
  while (b) {
    if (b == a) return false;
    b/=2;
  }
  return true;
}

int32_t main() {
  IOS;
  cin >> A >> B;
  if (!judge(A, B)) {
    cout << -1 << endl;
    return 0;
  }
  go(A, B);
  ans.PB(A);
  ans.PB(B);
  sort(ALL(ans));

  for (auto x: ans) {
    cout << x << " ";
  }
  cout << endl;


  return 0;
}

