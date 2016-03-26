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

#define au auto
template<typename T>
using vec = vector<T>;
#define loop(i, a, b) for (auto (i)=(a); (i)!=(b); (i)+=((a)>(b)?-1:1))
#define int long long

void Z_value(int *s, int *z, int len) {
	int i,j,left,right;
	left=right=0; z[0]=len;
	for(i=1;i<len;i++) {
		j=max(min(z[i-left],right-i),0LL);
		for(;i+j<len&&s[i+j]==s[j];j++);
		z[i]=j;
		if(i+z[i]>right) {
			right=i+z[i];
			left=i;
		}
	}
}

const int MX = 101010;
int ip[MX];
int N;
int s[MX];
int Z[MX];

int32_t main() {
    FILEIO("stocks");
  IOS;

  cin >> N;
  loop (i, 0, N) {
      cin >> ip[i];
  }
  loop (i, 0, N-1) {
      s[i] = ip[N-i-1] - ip[N-i-2];
  }

  Z_value(s, Z, N-1);
  Z[0] = 0;
  
  vector<int> ans;
  int bv = 0;
  loop (i, 0, N-1) {
      int t = Z[i];
      if (t > 0 and t > bv) {
          ans.clear();
          bv = t;
          ans.PB(s[i-1]);
      } else if (t > 0 and t == bv) {
          ans.PB(s[i-1]);
      }
  }

  if (bv == 0) {
      cout << "impossible" << endl;
      return 0;
  }

  int q = SZ(ans), p = ip[N-1]*q;
  for (auto x: ans) p += x;
  int g = __gcd(abs(p), abs(q));
  p /= g, q/=g;
  cout << p << "/" << q << endl;

  return 0;
}

