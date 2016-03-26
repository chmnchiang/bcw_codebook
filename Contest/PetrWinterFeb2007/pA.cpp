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

pii operator+(pii a, pii b){return {a.F+b.F, a.S+b.S};}
pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}
int cross(pii a, pii b){return a.F*b.S-a.S*b.F;}

const int MAXN = 51;
const int INF = 1029384756;
int N;
pii pt[MAXN];
int dp[2][MAXN][MAXN][MAXN][2];

int calc()
{
    sort(pt, pt+N);
    for(int z=0; z<2; z++)
        for(int i=0; i<N; i++)
            for(int j=0; j<N; j++)
                for(int k=0; k<N; k++)
                    for(int l=0; l<2; l++)
                        dp[z][i][j][k][l] = -INF;

    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            dp[0][i][i][j][0] = dp[1][i][i][j][0] = 2;
        }
    }

    for(int i=0; i<N; i++)
    {
        for(int j=i; j<N; j++)
        {
            for(int k=j+1; k<N; k++)
            {
                for(int l=0; l<2; l++)
                {
                    for(int z=0; z<2; z++)
                    {
                        if(dp[z][i][j][k][l] == -INF) continue;
                        pii d1 = pt[k] - pt[j];
                        for(int x=k+1; x<N; x++)
                        {
                            pii d2 = pt[x] - pt[k];
                            int crs = cross(d1, d2);
                            if(z == 0 && crs > 0) continue;
                            if(z == 1 && crs < 0) continue;
                            int nc = l | (crs != 0);
                            dp[z][i][k][x][nc] = max(dp[z][i][k][x][nc], dp[z][i][j][k][l] + 1);
//                            cout<<z<<","<<i<<","<<j<<","<<k<<","<<l<<" => "<<z<<","<<i<<","<<k<<","<<x<<","<<nc<<endl;
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            for(int k=0; k<N; k++)
                ans = max(ans, dp[0][i][j][k][0]);

    for(int i=0; i<N; i++)
    {
        for(int j=i+1; j<N; j++)
        {
            int a1 = -INF, a2 = -INF;
            int b1 = -INF, b2 = -INF;
            for(int k=i; k<j; k++)
            {
                a1 = max(a1, dp[0][i][k][j][1]);
                b1 = max(b1, dp[0][i][k][j][0]);
                a2 = max(a2, dp[1][i][k][j][1]);
                b2 = max(b2, dp[1][i][k][j][0]);
            }
            b1 = max(b1, a1);
            b2 = max(b2, a2);

            int zz = -INF;
            zz = max(zz, a1 + a2);
            zz = max(zz, a1 + b2);
            zz = max(zz, b1 + a2);

//            cout<<i<<"~"<<j<<" : "<<a1<<" "<<a2<<" / "<<b1<<" "<<b2<<endl;
            ans = max(ans, zz - 2);
        }
    }

//    for(int i=0; i<N; i++) cout<<pt[i]<<endl;

    return ans;
}

int main() {
  IOS;
  FILEIO("convex");

  cin>>N;
  for(int i=0; i<N; i++)
      cin>>pt[i].F>>pt[i].S;

  int ans = calc();
  cout<<ans<<endl;

  return 0;
}

