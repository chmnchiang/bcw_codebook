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

const int MAXN = 100005;
struct Item {
  int lis, id;
  ld cost;
};

bool operator < (const Item &a, const Item &b) {
  return make_tuple(a.lis,a.cost,a.id) < make_tuple(b.lis,b.cost,b.id);
}
bool operator > (const Item &a, const Item &b) {
  return make_tuple(a.lis,a.cost,a.id) > make_tuple(b.lis,b.cost,b.id);
}
struct BIT {
  Item bit[MAXN];
  void init() {
    REP(i,MAXN) bit[i] = {0,0,0};
  }
  void upd(int x, int lis, ld c, int id) {
    x++;
    Item it = {lis, id, c};
    for (int i=x; i<MAXN; i+=i&-i)
      bit[i] = max(bit[i], it);
  }
  Item qry(int x) {
    x++;
    Item res = {0,0,0};
    for (int i=x; i>0; i-=i&-i) {
      res = max(res, bit[i]);
    }
    return res;
  }
} bit;

int N,Y[MAXN];
vector<int> seq;
int dplis[MAXN];
ld dpcost[MAXN];
int prv[MAXN];
int gg[MAXN];
pii ip[MAXN];
ld ws360[MAXN], hao123[MAXN], JSDB[MAXN];
ll A,B;

void calc_JSDB() {
  REP1(i,1,N) ws360[i] = min(ip[i].F+ip[i].S+B, 2*A-ip[i].F-ip[i].S+B);
  REP1(i,1,N) hao123[i] = hypot(B, ip[i].F-ip[i].S);
  REP1(i,1,N) JSDB[i] = ws360[i] - hao123[i];
}
void calc_LIS() {
  bit.init();
  REP1(i,1,N) {
    int y = Y[i];
    Item it = bit.qry(y);
    dplis[i] = it.lis + 1;
    dpcost[i] = it.cost + JSDB[i];
    prv[i] = it.id;
    bit.upd(y, dplis[i], dpcost[i], i);
  }
}
int main() {
#ifndef HAO123
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
#endif
  IOS;
  cin>>A>>B>>N;
  REP1(i,1,N) cin>>ip[i].F;
  REP1(i,1,N) cin>>ip[i].S;

  sort(ip+1,ip+1+N);
  calc_JSDB();
  REP1(i,1,N) seq.PB(ip[i].S);
  sort(ALL(seq));
  seq.resize(unique(ALL(seq))-begin(seq));
  REP1(i,1,N) {
    Y[i] = lower_bound(ALL(seq),ip[i].S) - begin(seq) + 1;
  }

  reverse(Y+1,Y+1+N);
  calc_LIS();
  int lds = 0;
  REP1(i,1,N) {
    lds = max(lds, dplis[i]);
  }
  if (lds > 2) {
    cout<<-1<<endl;
    return 0;
  }
  reverse(Y+1,Y+1+N);

  ld ans = 0;
  int cur = 0;
  int mx = 0;
  while(cur < N)
  {
    int lst = cur + 1;
    while(1)
    {
      cur++;
      mx = max(mx, Y[cur]);
      if(cur == mx)
        break;
    }

    ld l1 = 0, l2 = 0;
    int c = 0;
    for(int i=lst; i<=cur; i++)
    {
      if(Y[i] > c)
      {
        c = Y[i];
        l1 += JSDB[i];
      }
    }
    c = 123467283;
    for(int i=cur; i>=lst; i--)
    {
      if(Y[i] < c)
      {
        c = Y[i];
        l2 += JSDB[i];
      }
    }

    ans += max(l1, l2);
  }

  ld aa = 0;
  for(int i=1; i<=N; i++)
    aa += ws360[i];
  aa -= ans;
  cout<<fixed<<setprecision(15)<<aa<<endl;

  return 0;
}

