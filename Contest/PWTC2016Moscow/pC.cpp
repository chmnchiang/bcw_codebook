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

const int MAXN = 1296000;
const double PI = acos(-1);

int N;
int alpha[MAXN], phi[MAXN];

int event[MAXN+1];

void calc()
{
  for(int i=0; i<N; i++)
  {
    int lb = alpha[i], rb = (alpha[i] + phi[i]) % MAXN;
    if(lb < rb)
    {
      event[lb]++;
      event[rb]--;
    }
    else
    {
      event[0]++;
      event[rb]--;
      event[lb]++;
    }
  }

  int cur = 0;
  for(int i=0; i<MAXN; i++)
  {
    cur += event[i];
    if(cur == 0)
    {
      cout<<"YES"<<endl;
      double th = (i + 0.5) / MAXN * 2 * PI;
      double R = 9e8;
      int x = R * cos(th), y = R * sin(th);
      cout<<x<<" "<<y<<endl;
      return;
    }
  }
}

int main() {
  IOS;

  cin>>N;
  int x, y;
  for(int i=0; i<N; i++)
    cin>>x>>y>>phi[i]>>alpha[i];

  calc();

  return 0;
}

