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

const int MAXN = 10105;

int N, M, Q;
double px[MAXN], py[MAXN], pz[MAXN];
double qx[MAXN], qy[MAXN], qz[MAXN];

double wx, wy, wz, wb;

void PLA()
{
    wx = wy = wz = wb = 1;
    while(1)
    {
        bool ok = true;
        for(int i=0; i<N; i++)
        {
            double c = px[i] * wx + py[i] * wy + pz[i] * wz + wb;
            if(c <= 0)
            {
                ok = false;
                wx += px[i];
                wy += py[i];
                wz += pz[i];
                wb += 1;
            }
        }
        for(int i=0; i<M; i++)
        {
            double c = qx[i] * wx + qy[i] * wy + qz[i] * wz + wb;
            if(c >= 0)
            {
                ok = false;
                wx -= qx[i];
                wy -= qy[i];
                wz -= qz[i];
                wb -= 1;
            }
        }

        if(ok) break;
    }

}

int main() {
  IOS;
  FILEIO("war");

  cin>>N;
  for(int i=0; i<N; i++)
      cin>>px[i]>>py[i]>>pz[i];
  cin>>M;
  for(int i=0; i<M; i++)
      cin>>qx[i]>>qy[i]>>qz[i];

  PLA();

  cin>>Q;
  for(int i=0; i<Q; i++)
  {
      double x, y, z;
      cin>>x>>y>>z;
      double c = wx * x + wy * y + wz * z + wb;
      cout<<(c>0 ? '1' : '2');
  }
  cout<<endl;

  return 0;
}

