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

const int MX = 333333;
int N;
using pii = pair<int, int>;
vector<pii> ip;
double ans[MX];

int main() {
  IOS;
  cin >> N;
  N *= 2;
  for (int i=0; i<N; i++) {
    string s; cin >> s;
    int t; cin >> t;
    ip.PB({s == "+" ? 1 : -1, t});
  }

  int j = N/2-1;
  double cocona = 0.0;
  int papika = 0;
  for (int i=N-1; i>=0; i--) {
    pii p = ip[i];
    if (p.F == -1) {
      cocona += p.S;
      papika += 1;
    } else {
      ans[j--] = cocona*1.0/papika - p.S;
      cocona -= cocona / papika;
      papika --;
    }
  }

  cout << fixed << setprecision(10);
  for (int i=0; i<N/2; i++)
    cout << ans[i] << endl;

  return 0;
}
