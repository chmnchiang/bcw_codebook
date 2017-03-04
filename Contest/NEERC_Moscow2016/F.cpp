#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

using pii = pair<int,int>; 

int ok[256];
string an;

string solve() {
  string res;
  vector<pii> vec;
  int st;
  st = -1;
  REP(i,256) {
    if (!ok[i]) {
      if (st != -1) {
        vec.PB({st, i-1});
      }
      st = -1;
    } else {
      if (st == -1) st = i;
    }
  }
  assert(st == -1);

  for (auto it:vec) {
    int l = it.F;
    int r = it.S;
    vector<int> vvv;
    REP1(i,l,r) {
      if (ok[i] == 1) {
        vvv.PB(i);
      }
    }
    if (SZ(vvv) <= 2) {
      for (auto c:vvv)
        res += char(c);
    } else {
      res += char(l);
      res += "-";
      res += char(vvv.back());
    }
  }

  return res;
}
int main() {
  IOS;
  string s;
  getline(cin,s);

  REP(i,256) ok[i] = 2;
  REP(i,32) ok[i] = 0;
  REP1(i,127,255) ok[i] = 0;
  // ok['-'] = ok['^'] = ok[']'] = 0;
  an += ' ';
  REP1(i,'0','9') an += char(i);
  REP1(i,'A','Z') an += char(i);
  REP1(i,'a','z') an += char(i);

  for (auto i:an) ok[(int)i] = 0;
  for (auto c:s) ok[(int)c] = 1;

  string s1 = solve();

  for (auto i:an) ok[(int)i] ^= 1;
  string s2 = "^" + solve();

  if (s2 == "^") {
    cout << "%[^!]" << endl;
    return 0;
  }
  s1 += "]";
  s2 += "]";

  string ans = s1;
  if (SZ(ans) > SZ(s2) or (SZ(ans) == SZ(s2) and ans > s2))
    ans = s2;

  cout << "%[" << ans << endl;

  return 0;
}
