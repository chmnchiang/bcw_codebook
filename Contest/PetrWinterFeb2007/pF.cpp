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

const int MX = 1010101;
int N, M;
string ip;
vector<int> pos;
int pw[MX];
deque<int> ls, rs;

int sss() {
    return SZ(ls) + SZ(rs);
}

void pop_once() {
    if (not SZ(ls)) {
        rs.pop_front();
    } else if (not SZ(rs)) {
        ls.pop_front();
    } else {
        int r = rs.front(), l = ls.front();
        if (l < r) {
            ls.pop_front();
        } else rs.pop_front();
    }
}

int main() {
  FILEIO("soldiers");
  IOS;

  pw[0] = 1;
  for (int i=1; i<MX; i++)
      pw[i] = pw[i-1]*2%2007;

  cin >> N >> M >> ip;
  for (int i=0; i<N; i++) {
      bool isr = (ip[i] == 'r');
      if (isr) {
          if (SZ(ls)) {
              ls.pop_back();
              rs.PB(i);
          } else {
              rs.PB(i);
              if (sss() > M) pop_once();
          }
      } else {
          int a = i - SZ(rs);
          pos.PB(a);
          ls.PB(i);
          if (sss() > M) pop_once();
      }
  }

  int ans = 0;
  for (auto x: pos) {
//      cout << x << ' ';
      ans += pw[N-x-1];
      ans %= 2007;
  }
  cout << ans << endl;


  return 0;
}

