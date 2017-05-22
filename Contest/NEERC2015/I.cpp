//a34021501 {{{
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

#ifdef HAO123
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef HAO123
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif
// }}}
// Let's Fight! !111111111!

#define int long long
struct Buy {
  int id, p, v, tv, cv, pr;

  bool operator < (const Buy &b) const {
    return make_tuple(p, -pr) < make_tuple(b.p, -b.pr);
  }

  void nextcv() {
    assert(!cv);
    int t = min(tv, v);
    cv = t;
  }
};

struct Sell {
  int id, p, v, tv, cv, pr;

  bool operator < (const Sell &b) const {
    return make_tuple(-p, -pr) < make_tuple(-b.p, -b.pr);
  }

  void nextcv() {
    assert(!cv);
    int t = min(tv, v);
    cv = t;
  }
};

struct Final {
  int id, t, p, v, tv, cv, pr;
  bool operator < (const Final &f) const {
    //return id < f.id;
    return make_tuple(p, pr) < make_tuple(f.p, f.pr);
  }
};

const int BUY = 1;
const int SELL = 2;

using pii = pair<int, int>;
map<pii, int> ansP;
map<pii, int> ansV;

const int MX = 111111;
priority_queue<Buy> buys[MX];
priority_queue<Sell> sells[MX];
priority_queue<int> buypq, sellpq;
int GP;

template<typename T>
int nextp(priority_queue<T> *v, priority_queue<int> &pq) {
  while (SZ(pq)) {
    int t = pq.top(); pq.pop();
    t = abs(t);
    if (SZ(v[t])) return t;
  }
  return -1;
}

void add(int bid, int sid, int p, int t) {
  //cout << "[+]" << bid << ' ' << sid << ' ' << p << ' ' << t << endl;
  ansP[pii{bid, sid}] = p;
  ansV[pii{bid, sid}] += t;
}

void procBuyP(int p, Buy &buy) {
  vector<Sell> vec;
  auto &sl = sells[p];
  while (SZ(sl)) {
    Sell s = sl.top(); sl.pop();

    int t = min(buy.v, s.cv); 
    buy.v -= t;
    s.cv -= t;
    s.v -= t;
    add(buy.id, s.id, p, t);



    if (s.v) {
      if (!s.cv) {
        s.nextcv();
        s.pr = GP++;
      }
      vec.PB(s);
    }
    if (!buy.v) break;
  }
  for (auto s: vec) {
    sl.push(s);
  }
  if (SZ(sl)) {
    sellpq.push(p);
  }
}

Buy procBuy(Buy buy) {
  while (buy.v) {
    int p = nextp(sells, sellpq);
    if (p == -1 || p > buy.p) break;
    procBuyP(p, buy);
  }
  return buy;
}

void procSellP(int p, Sell &sell) {
  vector<Buy> vec;
  auto &bl = buys[p];
  while (SZ(bl)) {
    Buy b = bl.top(); bl.pop();

    int t = min(sell.v, b.cv); 
    sell.v -= t;
    b.cv -= t;
    b.v -= t;
    add(b.id, sell.id, p, t);

    if (b.v) {
      if (!b.cv) {
        b.nextcv();
        b.pr = GP++;
      }
      vec.PB(b);
    }
    if (!sell.v) break;
  }
  for (auto b: vec) {
    bl.push(b);
  }
  if (SZ(bl)) {
    buypq.push(p);
  }
}

Sell procSell(Sell sell) {
  while (sell.v) {
    int p = nextp(buys, buypq);
    if (p == -1 || p < sell.p) break;
    procSellP(p, sell);
  }
  return sell;
}

int32_t main() {
#ifndef HAO123
  FILEIO("iceberg");
#endif
  IOS;

  int Z; cin >> Z;
  for (int i=0; i<Z; i++) {
    int id, t, p, v, tv;
    cin >> id >> t >> p >> v >> tv;
    if (t == BUY) {
      Buy b = {id, p, v, tv, 0, 0};
      b = procBuy(b);
      if (b.v) {
        b.nextcv();
        b.pr = GP++;
        buys[p].push(b);
        buypq.push(p);
      }
    } else {
      Sell s = {id, p, v, tv, 0, 0};
      s = procSell(s);
      if (s.v) {
        s.nextcv();
        s.pr = GP++;
        sells[p].push(s);
        sellpq.push(-p);
      }
    }
  }

  for (auto p: ansP) {
    cout << p.F.F << ' ' << p.F.S << ' ' << p.S << ' ' << ansV[p.F] << endl;
  }

  vector<Final> vec;
  for (int i=0; i<MX; i++) {
    auto &pq = buys[i];
    while (SZ(pq)) {
      auto z = pq.top(); pq.pop();
      Final b = {z.id, 1, z.p, z.v, z.tv, z.cv, z.pr};
      vec.PB(b);
    }
  }

  for (int i=0; i<MX; i++) {
    auto &pq = sells[i];
    while (SZ(pq)) {
      auto z = pq.top(); pq.pop();
      Final b = {z.id, 2, z.p, z.v, z.tv, z.cv, z.pr};
      vec.PB(b);
    }
  }

  cout << endl;
  sort(ALL(vec));
  for (auto f: vec) {
    cout << f.id << ' ' << f.t << ' ' << f.p << ' ' << f.v << ' ' << f.tv << ' ' <<
      f.cv << endl;
  }

  return 0;
}

