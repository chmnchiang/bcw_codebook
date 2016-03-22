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


int N;

int qry(int a) {
  cout << "? " << a+1 << endl;
  int t; cin >> t;
  return t;
}


/*
vector<int> vec={1, 1, 2, 2, 3};

int qry(int a) {
  //cout << a << endl;
  return vec[a];
}*/

int main() {
  IOS;

  cin>>N; //N = SZ(vec);

  int l=-1, r=N/2-1;
  while (l<r) {
    int md=(l+r+1)/2;
    int t1=qry(md*2), t2=qry(md*2+1);
    if (t1 == t2) {
      l = md;
    } else r = md - 1;
  }
  if (l == N/2-1) {
    int z = qry(l*2+2);
    cout << "! " << z << endl;
    return 0;
  }
  int z1 = qry(l*2+2);
  int z2 = qry(l*2+3);
  int z3 = qry(l*2+4);
  cout << "! " << (z1^z2^z3) << endl;

  return 0;
}

