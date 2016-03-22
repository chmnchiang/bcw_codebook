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

const int MX = (1<<20)+1;



int N,S,A[21];
int trans[MX];
pii dp[MX];

void output() {
  vector<int> ord;
  int s = (1<<N)-1;
  while (s) {
    ord.PB(trans[s]);
    s -= 1<<trans[s];
  }
  reverse(ALL(ord));
  vector<vector<int>> ans;
  vector<int> vec;
  int cost = 0;
  for (auto i:ord) {
    if (cost + A[i] <= S) {
      cost += A[i];
      vec.PB(i);
    } else {
      ans.PB(vec);
      cost = A[i];
      vec = {i};
    }
  }
  ans.PB(vec);

  cout << SZ(ans) << endl;
  for (auto v:ans) {
    cout << SZ(v);
    for (auto it:v) cout << " " << (it+1);
    cout << endl;
  }
}
int main() {
  IOS;
  int nT;
  cin >> nT;
  while (nT--) {
    cin >> N >> S;
    REP(i,N) {
      cin >> A[i];
    }
    dp[0] = {0,0};
    REP1(s,1,(1<<N)-1) {
      dp[s] = {N,S};
      REP(i,N) {
        if ((1<<i) & s) {
          pii tmp = dp[s-(1<<i)];
          tmp.S += A[i];
          if (tmp.S > S) {
            tmp.S = A[i];
            tmp.F++;
          }
          if (tmp < dp[s]) {
            dp[s] = tmp;
            trans[s] = i;
          }
        }
      }
      //cout << s << " " << dp[s] << " " << trans[s] << endl;
    }
    output();
  }

  return 0;
}

