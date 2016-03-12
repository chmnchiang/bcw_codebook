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
  freopen(name".in", "r", stdin);
//  freopen(name".out", "w", stdout);
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

typedef pair<int, int> pii;
typedef vector<pii> vpii;

vpii ip, op;
int N;
vpii tp[3];
bool hentsan;
int hao0tip, hao1tip;

int type(pii p1) {
  if (p1.F == 10) return 0;
  if (p1.F + p1.S == 10) return 1;
  return 2;
}

int calcSpare(vpii spare, vpii usual) {
  sort(ALL(spare), [](pii p1, pii p2) { return p1.F > p2.F; });
  sort(ALL(usual), [](pii p1, pii p2) { return p1.F > p2.F; });

  int bv = 0;
  int sz = SZ(spare);
  int nw = 0;
  for (int i=0; i<sz-1; i++) {
    nw += spare[i].F;
  }
  bv = max(bv, nw);
  nw += spare.back().F;

  for (int i=0, j=sz-1; i<min(sz, SZ(usual)); i++, j--) {
    nw += usual[i].F;
    nw -= spare[j].F;
    bv = max(bv, nw);
  }

  //cout << "bv = " << bv << endl;

  return bv;
}

inline int val(pii p) {
    return p.F+p.S;
}

int hao0() {
    int sz0 = SZ(tp[0]);
    int sz1 = SZ(tp[1]);
    //cout << "SZ = " << endl;
    //cout << sz0 << ' ' << sz1 << endl;

    if (sz1 <= sz0) {
        int ans = (sz1 + sz0 - 1)*10;
        //cout << "ANS = " << ans << endl;
        return ans;
    } else {
        sort(ALL(tp[1]), [](pii p1, pii p2) { return p1.F > p2.F; });
        sort(ALL(tp[2]), [](pii p1, pii p2) { return p1.F > p2.F; });
        int k = sz1 - sz0;

        vpii usu = tp[2];
        usu.PB(tp[1][0]);
        vpii sp;
        for (int i=1; i<=k; i++) {
            sp.PB(tp[1][i]);
        }
        int ans = (sz0 * 2 - 1) * 10;
        ans += calcSpare(sp, usu);
        //cout << "AA = " << ans << endl;
        return ans;
    }
}

int hao1() {
    int sz0 = SZ(tp[0]);
    int sz1 = SZ(tp[1]);

    if (sz1 <= sz0+1) {
        int ans = (sz1 + sz0 - 1)*10;
        return ans;
    } else {
        sort(ALL(tp[1]), [](pii p1, pii p2) { return p1.F > p2.F; });
        sort(ALL(tp[2]), [](pii p1, pii p2) { return p1.F > p2.F; });
        int k = sz1 - sz0 - 1;
        //cout << k << endl;
        //cout << sz1 << ' ' << sz0 << endl;

        //cout << "tp = " << tp[2] << endl;
        vpii usu = tp[2];
        usu.PB(tp[1][0]);
        //cout << tp[1] << endl;
        vpii sp;
        for (int i=1; i<=k; i++) {
            sp.PB(tp[1][i]);
        }
        int ans = (sz0*2) * 10;
        ans += calcSpare(sp, usu);
        return ans;
    }
}

int solve() {
    tp[0].clear();
    tp[1].clear();
    tp[2].clear();
    for (auto x: op) {
        int t = type(x);
        tp[t].PB(x);
    }

    int ans = 0;
    if (SZ(tp[0])) ans = max(ans, hao0()+hao0tip);
    if (SZ(tp[1])) ans = max(ans, hao1()+hao1tip);
    //cout << hao1tip << endl;
    //cout << hao0tip << endl;
    //cout << "ans = " << ans << endl;
    return ans;
}

int main() {
  IOS;
  FILEIO("bowling");

  cin >> N;
  for (int i=0; i<N; i++) {
      int a, b; cin >> a >> b;
      ip.PB({a, b});
  }

  hentsan = false;

  if (type(ip.back()) == 0) {
      int a, b; cin >> a >> b;
      ip.PB({a, b});
      hentsan = true;
  }
  int S = SZ(ip);

  int ans = 0;
  for (int i=0; i<S; i++) {
      if (not hentsan and type(ip[i]) == 0) continue;
      int a = 0;
      op.clear();
      for (int j=0; j<S; j++) {
          a += val(ip[j]);
          if (i == j) continue;
          op.PB(ip[j]);
      }
      hao0tip = val(ip[i]);
      hao1tip = hentsan ? -102938475 : ip[i].F;

      a += solve();
      //cout << i << ' ' << a << endl;
      ans = max(ans, a);
  }
  cout << ans << endl;
  return 0;
}

