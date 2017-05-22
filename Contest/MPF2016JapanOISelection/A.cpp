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

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

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

const int MAXN = 808080;

struct Lisan {
  vector<int> seq;
  void init() { seq.clear(); }
  void add(int x) {
    seq.PB(x);
  }
  void make() {
    sort(ALL(seq));
    seq.resize(unique(ALL(seq))-begin(seq));
  }
  int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq); }
} ls;

struct BIT {
  int val[MAXN];
  void init() {
    memset(val,0,sizeof(val));
  }
  void upd(int x, int v) {
    x += 2;
    for (int i=x; i>0; i-=i&-i) val[i] = max(val[i], v);
  }
  int qry(int x) {
    x += 2;
    int res = 0;
    for (int i=x; i<MAXN; i+=i&-i) res = max(res, val[i]);
    return res;
  }
} bit;

int N,Q,dp[MAXN],qord[MAXN],ans[MAXN];
vector<pii> ip;
vector<pii> qry;

int main() {
  IOS;
  while (cin>>N>>Q) {
    ls.init();
    ip.resize(N);
    REP(i,N) {
      cin>>ip[i].F>>ip[i].S;
      ls.add(ip[i].F);
      ls.add(ip[i].S);
    }
    qry.resize(Q);
    REP(i,Q) {
      cin>>qry[i].F>>qry[i].S;
      ls.add(qry[i].F);
      ls.add(qry[i].S);
      qord[i] = i;
    }
    ls.make();
    for (auto &i:ip) {
      i.F = ls.qry(i.F);
      i.S = ls.qry(i.S);
    }
    for (auto &i:qry) {
      i.F = ls.qry(i.F);
      i.S = ls.qry(i.S);
    }
    sort(ALL(ip), [](pii a, pii b) { return make_tuple(a.S, -a.F) < make_tuple(b.S, -b.F); });
    sort(qord,qord+Q, [&](int a, int b) { return make_tuple(qry[a].S, -qry[a].F) < make_tuple(qry[b].S, -qry[b].F); });

    int pos = 0;
    bit.init();
    REP(i,N) {
      while (pos < Q and ip[i].S > qry[qord[pos]].S) {
        int qid = qord[pos];
        ans[qid] = bit.qry(qry[qid].F);
        //cout<<"QUERY ("<<ls.seq[qry[qid].F]<<","<<ls.seq[qry[qid].S]<<") "<<ans[qid]<<endl;
        pos++;
      }
      dp[i] = bit.qry(ip[i].F) + 1;
      bit.upd(ip[i].F, dp[i]);
      //cout<<"("<<ls.seq[ip[i].F]<<","<<ls.seq[ip[i].S]<<") "<<dp[i]<<endl;
    }
    while (pos < Q) {
      int qid = qord[pos];
      ans[qid] = bit.qry(qry[qid].F);
      //cout<<"QUERY ("<<ls.seq[qry[qid].F]<<","<<ls.seq[qry[qid].S]<<") "<<ans[qid]<<endl;
      pos++;
    }

    REP(i,Q) cout<<ans[i]<<"\n";
  }

  return 0;
}

