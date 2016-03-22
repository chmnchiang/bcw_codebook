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

struct mat {
  int v[6][6];
  int r;

  mat() { memset(v, 0, sizeof(v)); r=0; }

  mat operator * (const mat &m) const {
    mat ret;
    for (int i=0; i<6; i++) {
      for (int j=0; j<6; j++) {
        for (int k=0; k<6; k++) {
          ret.v[i][k] += v[i][j] * m.v[j][k];
        }
      }
    }
    ret.r = r + m.r;
    return ret;
  }

  friend ostream& operator << (ostream &o, const mat &m) {
    for (int i=0; i<6; i++) {
      for (int j=0; j<6; j++) {
        o << m.v[i][j] << ' ';
      } o << endl;
    }
    return o;
  }
};

mat cst(int a) {
  mat res;
  res.r = 1;
  res.v[5][5] = 1;
  for (int i=0; i<4; i++) {
    res.v[i+1][i] = 1;
  }
  res.v[0][5] = a;
  return res;
}

mat add() {
  mat res;
  res.r=-1;
  res.v[5][5] = 1;
  res.v[0][0] = 1;
  res.v[0][1] = 1;
  for (int i=1; i<4; i++) {
    res.v[i][i+1] = 1;
  }
  return res;
}

mat mns() {
  mat res;
  res.r=-1;
  res.v[5][5] = 1;
  res.v[0][0] = -1;
  res.v[0][1] = 1;
  for (int i=1; i<4; i++) {
    res.v[i][i+1] = 1;
  }
  return res;
}

typedef map<char, mat> Context;

mat parse(Context con) {
  mat res;
  for (int i=0; i<6; i++) 
    res.v[i][i] = 1;
  char c = getchar();

  while (c != ']' and c != '\n' and c != EOF) {
    if (isdigit(c)) {
      res = cst(c-'0') * res;
    } else if (c == '+') {
      res = add() * res;
    } else if (c == '-') {
      res = mns() * res;
    } else if (c == '[') {
      auto x = parse(con);
      c = getchar();
      con[c] = x;
    } else {
      assert(con.count(c));
      res = con[c] * res;
    }
    c = getchar();
  }
  return res;
}

int32_t main() {
  //IOS;

  auto ans = parse(Context());
  cout << ans.r << endl;
  for (int i=0; i<ans.r; i++) {
    cout << ans.v[i][5] << " \n"[i==ans.r-1];
  }

  return 0;
}

