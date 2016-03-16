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

const int MXN = 2050; 
const double PI = acos(-1);
const double INF = 1e9;

struct Point {
  double ang;
  int id;
  bool operator < (const Point &he) const { return tie(ang,id) < tie(he.ang,he.id); }
}pt[MXN];
struct Answer {
  double area;
  vector<int> used;
};

int N,K,A[MXN][MXN];
double dp[MXN][MXN],sn[MXN][MXN];

Answer solve(int base) {
  REP(i,K) REP(j,N) {
    dp[i][j] = -INF;
    A[i][j] = 0;
  }
  dp[0][0] = 0;
  for (int j=1; j<N; j++) {
    for (int i=K-1; i>=1; i--) {
      if (i > j) i = j;
      int lt = A[i][j-1];
      int rt = A[i+1][j];
      if (i+1 > j or i == K-1) rt = j-1;
      REP1(k,lt,rt) {
        double area = dp[i-1][k] + sn[j+base][k+base];
        if (dp[i][j] < area) {
          dp[i][j] = area;
          A[i][j] = k;
        }
      }
    }
  }

  REP1(j,1,N-1) {
    dp[K-1][j] += sn[N+base][j+base];
  }
  int best = 0;
  REP(i,N) {
    if (dp[K-1][best] < dp[K-1][i]) best = i;
  }
  Answer res;
  res.area = dp[K-1][best];
  for (int i=K-1; i>0; i--) {
    res.used.PB(best+base);
    best = A[i][best];
  }
  res.used.PB(base);
  reverse(ALL(res.used));
  return res;
}
bool check_fail(vector<int> vec) {
  REP1(i,1,SZ(vec)-1) {
    if (pt[vec[i]].ang - pt[vec[i-1]].ang >= PI) return true;
  }
  return pt[vec[0]+N].ang - pt[vec.back()].ang >= PI;
}
int main() {
#ifndef DARKHH
  freopen("post.in", "r", stdin);
#endif

  IOS;
  cin >> N >> K;
  REP(i,N) {
    cin >> pt[i].ang;
    pt[i].id = i+1;
    pt[i+N] = pt[i];
    pt[i+N].ang += 2 * PI;
  }
  sort(pt,pt+2*N);
  REP(i,2*N) REP1(j,i+1,2*N-1)
    sn[j][i] = sin(pt[j].ang - pt[i].ang);

  Answer ans = solve(0);
  int lt = 0;
  int rt = N-1;
  REP1(i,1,SZ(ans.used)-1) {
    if (ans.used[i] - ans.used[i-1] < rt - lt) {
      rt = ans.used[i];
      lt = ans.used[i-1];
    }
  }
  REP1(i,lt,rt) {
    Answer tmp = solve(i%N);
    if (tmp.area > ans.area) ans = tmp;
  }
  if (check_fail(ans.used)) {
    cout << "0" << endl;
  } else {
    vector<Point> vec;
    for (auto it:ans.used) {
      vec.PB(pt[it]);
      if (vec.back().ang >= 2 * PI)
        vec.back().ang -= 2 * PI;
    }
    sort(ALL(vec));
    for (auto it:vec) cout << it.id << " ";
    cout << endl;
  }

  return 0;
}

