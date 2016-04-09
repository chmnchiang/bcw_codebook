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

const int MX = 666666;
const int INF = 1029384756;
struct Lisan {
  vector<int> seq;
  void add(int x) { seq.PB(x); }
  void build() {
    sort(ALL(seq));
    seq.resize(unique(ALL(seq)) - begin(seq));
  }
  int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq); }
}lisan;
struct BIT {
  int bit[MX];
  void init() {
    REP(i,MX) bit[i] = INF;
  }
  int lb(int x) { return x & -x; }
  void update(int p, int v) {
    p += 2;
    for (int i=p; i; i-=lb(i)) bit[i] = min(bit[i],v);
  }
  int qry(int p) {
    p += 2;
    int v = INF;
    for (int i=p; i<MX; i+=lb(i)) v = min(v, bit[i]);
    return v;
  }
}bit;

struct BIT2 {
  int bit[MX];
  void init() {
    REP(i,MX) bit[i] = INF;
  }
  int lb(int x) { return x & -x; }
  void update(int p, int v) {
    p += 2;
    for (int i=p; i<MX; i+=lb(i)) bit[i] = min(bit[i],v);
  }
  int qry(int p) {
    p += 2;
    int v = INF;
    for (int i=p; i; i-=lb(i)) v = min(v, bit[i]);
    return v;
  }
}bit2;

int N, M;
int ip[MX];
using vi = vector<int>;
using pii = pair<int, int>;
vector<pii> ran;
int nx[MX];

void build_range() {
  stack<pii> st;
  for (int i=0; i<N; i++) {
    int t = ip[i];
    while (SZ(st) and st.top().S < t) {
      st.pop();
    }
    if (SZ(st) and st.top().S == t) {
      nx[st.top().F] = i;
      st.top().F = i;
    } else {
      st.push({i,t});
    }
  }

}


bool us[MX];
struct Qry {
  int l, r;
  int id;
};
vector<Qry> qry;
vector<pii> dump;
int ans[MX];
vector<int> vl[MX];

int calc(int v, int l, int r) {
  auto z = upper_bound(ALL(vl[v]), r);
  --z;
  return *z - *lower_bound(ALL(vl[v]), l);
}

int main() {
  IOS;
  cin >>N>>M;
  for (int i=0; i<N; i++) {
    cin>>ip[i];
    lisan.add(ip[i]);
  }

  lisan.build();
  REP(i,N) {
    ip[i] = lisan.qry(ip[i]);
    vl[ip[i]].PB(i);
  }
  
  REP(i, N+5) nx[i] = -1;
  build_range();
  REP(i, N) {
    if (us[i]) continue;
    vector<int> t;
    int z = i;
    while (nx[z] != -1) {
      us[z] = 1;
      t.PB(z);
      z = nx[z];
    }
    us[z] = 1;
    t.PB(z);

    for (int j=0; j<SZ(t); j++) {
      ran.PB({t[0], t[j]});
      ran.PB({t[j], t[SZ(t)-1]});
    }
    dump.PB({t[0], t.back()});
  }
  dump.PB({-1, N});

  qry.resize(M);
  REP(i, M) {
    int a, b;
    cin >> a >> b;
    a--; b--;
    qry[i] = {a, b, i};

  }
  sort(ALL(ran));
  ran.resize(unique(ALL(ran)) - ran.begin());
  //cout << ran << endl;

  sort(ALL(qry), [](Qry p1, Qry p2) { return p1.r < p2.r; });
  sort(ALL(ran), [](pii p1, pii p2) { return p1.S < p2.S; });

  int j=0;
  bit.init();
  for (int i=0; i<M; i++) {
    int qid = qry[i].id;
    int ql = qry[i].l, qr = qry[i].r;
    while (j<SZ(ran) and ran[j].S <= qr) {
      //cout << "*" << ran[j] << endl;
      //cout << "Update = " << ran[j].F << ' ' << ran[j].F - ran[j].S << endl;
      bit.update(ran[j].F, ran[j].F - ran[j].S);
      j++;
    }
    //cout << ql << ' ' << qr << endl;
    int z = -bit.qry(ql);
    //cout << "Qry = " << ql << ' ' << z << endl;
    ans[qid] = z;
  }

  bit.init();
  sort(ALL(dump));

  sort(ALL(qry), [](Qry p1, Qry p2) { return p1.l < p2.l; });
  
  //cout << "-----" << endl;
  //cout << dump << endl;

  bit.init();
  j = 0;
  for (int i=0; i<M; i++) {
    int qid = qry[i].id;
    int ql = qry[i].l, qr = qry[i].r;
    while (j < SZ(dump) and dump[j].F <= ql) {
      //cout << dump[j].F << ' ' << dump[j].S << endl;
      bit.update(dump[j].S, dump[j].S);
      j++;
    }

    int z = bit.qry(qr);
    if (z == N) continue;
    int val = ip[z];
    //cout << "Z, val = " << z << ' ' << val << endl;
    //cout << calc(val, ql, qr) << endl;
    ans[qid] = max(calc(val, ql, qr), ans[qid]);
  }

  for (int i=0; i<M; i++) {
    cout << ans[i] << '\n';
  }



  return 0;
}

