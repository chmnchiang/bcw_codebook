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

const int MAXN = 11;
const int MAXL = 1<<MAXN;

int N, M;
double p1[MAXN], p2[MAXN], q[MAXN][MAXN];
double z2[MAXN];

double calc2(int lv, double pr, double qr)
{
    if(lv == M)
        return pr * (1 - qr);

    double a1 = calc2(lv+1, pr * (1-p2[lv]), qr);
    double a2 = calc2(lv+1, pr * p2[lv], qr * z2[lv]);
    return a1 + a2;
}

double calc()
{
    double ans = 0;

    for(int i=0; i<(1<<N); i++)
    {
        double curprob = 1;
        for(int j=0; j<M; j++)
            z2[j] = 1;
        for(int j=0; j<N; j++)
        {
            if(i&(1<<j))
            {
                curprob *= p1[j];
                for(int k=0; k<M; k++)
                    z2[k] *= 1 - q[j][k];
            }
            else
            {
                curprob *= 1 - p1[j];
            }
        }

        ans += calc2(0, curprob, 1);
    }

    return ans;
}

int main() {
  IOS;
  FILEIO("way");

  cin>>N>>M;
  for(int i=0; i<N; i++)
      cin>>p1[i];
  for(int i=0; i<M; i++)
      cin>>p2[i];
  for(int i=0; i<N; i++)
      for(int j=0; j<M; j++)
          cin>>q[i][j];

  double ans = calc();
  cout<<fixed<<setprecision(10)<<ans<<endl;

  return 0;
}

