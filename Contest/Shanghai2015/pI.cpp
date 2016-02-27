#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
  return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1010;
const ll MOD = 1000000007;

pii operator+(pii a, pii b){return {a.F+b.F, a.S+b.S};}
pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}
pii operator-(pii a){return {-a.F, -a.S};}
int dot(pii a, pii b){return a.F*b.F+a.S*b.S;}
int cross(pii a, pii b){return a.F*b.S-a.S*b.F;}

int N;
pii pt[MAXN];
pii rpt[MAXN];
int ord[MAXN];
pii slope[MAXN];
ll comb[MAXN][MAXN];

void make_comb()
{
  comb[0][0] = 1;
  for(int i=1; i<MAXN; i++)
  {
    comb[i][0] = comb[i][i] = 1;
    for(int j=1; j<i; j++)
      comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
  }
}

ll inv(ll x)
{
  ll p = MOD-2, cur = x%MOD, ret = 1;
  while(p)
  {
    if(p&1LL)
      ret = (ret * cur) % MOD;
    cur = (cur * cur) % MOD;
    p >>= 1;
  }
  return ret;
}

ll calc1()
{
  ll ans = 0;
  ll ret = 1;
  for(int i=0; i<4; i++)
  {
    ret = (ret * (N-i)) % MOD;
    ret = (ret * inv(i+1)) % MOD;
    ans = (ans + ret) % MOD;
  }
  return ans;
}

int sg(pii x)
{
  return x.S>0 || (x.S == 0 && x.F>0);
}

bool cmp(pii pa, pii pb)
{
  //pii pa = rpt[a], pb = rpt[b];
  //int sa = sg(pa), sb = sg(pb);
  //if(sa != sb) return sa > sb;
  return cross(pa, pb) > 0;
}

ll calc2()
{
  ll ans = 0;
  for(int i=0; i<N; i++)
  {
    vector<pii> vec1, vec2;
    for(int j=0; j<N; j++)
    {
      rpt[j] = pt[j] - pt[i];
      if(j == i) continue;
      int g = __gcd(abs(rpt[j].F), abs(rpt[j].S));
      slope[j] = {rpt[j].F / g, rpt[j].S / g};
      if(sg(slope[j])) vec1.PB(slope[j]);
      else vec2.PB(-slope[j]);
    }
    sort(ALL(vec1), cmp);
    sort(ALL(vec2), cmp);
    int V1 = vec1.size(), V2 = vec2.size();

    int lb1 = 0, lb2 = 0, rb1 = 0, rb2 = 0;
    vector<pii> pslope;
    for(auto x: vec1)
      pslope.PB(x);
    for(auto x: vec2)
      pslope.PB(x);
    sort(ALL(pslope), cmp);
    int P = unique(ALL(pslope)) - pslope.begin();
    pslope.resize(P);
    for(int j=0; j<P; j++)
    {
      pii sl = pslope[j];
      lb1 = lower_bound(ALL(vec1), sl, cmp) - vec1.begin();
      rb1 = upper_bound(ALL(vec1), sl, cmp) - vec1.begin();
      lb2 = lower_bound(ALL(vec2), sl, cmp) - vec2.begin();
      rb2 = upper_bound(ALL(vec2), sl, cmp) - vec2.begin();

      ll lnum = V1 - rb1 + lb2;
      ll rnum = V2 - rb2 + lb1;
      ll cnum = rb1 - lb1 + 1;
      //cout<<i<<" SL "<<sl<<" : L "<<lnum<<" R "<<rnum<<" C "<<cnum<<endl;

      ll crs = lnum * rnum;
      for(int k=3; k<=cnum; k++)
      {
        ll num = comb[cnum-1][k-1];
        if(k == 4) crs += lnum + rnum;
        if(k == 5) crs += 1;
        ans = (ans + num * crs) % MOD;
      }
    }
    vector<ll> vn1, vn2;
    vn1.resize(P);
    vn2.resize(P);
    for(auto x: vec1)
    {
      int p = lower_bound(ALL(pslope), x, cmp) - pslope.begin();
      vn1[p]++;
    }
    for(auto x: vec2)
    {
      int p = lower_bound(ALL(pslope), x, cmp) - pslope.begin();
      vn2[p]++;
    }
    for(int j=0; j<P; j++)
      vn1[j] *= vn2[j];

    ll sum = 0, ls = 0;
    for(int j=0; j<P; j++)
    {
      ls += sum * vn1[j];
      sum += vn1[j];
    }
    ls %= MOD;
    ans = (ans + MOD - ls) % MOD;
  }

  //cout<<"A2 = "<<ans<<endl;

  return ans;
}

ll calc()
{
  ll ans = 0;
  ans += calc1();
  ans += calc2();
  ans %= MOD;

  return ans;
}

int main() {
  make_comb();
  IOS;
  int T;
  cin>>T;
  for(int t=1; t<=T; t++)
  {
    cin>>N;
    for(int i=0; i<N; i++)
      cin>>pt[i].F>>pt[i].S;

    ll ans = calc();
    cout<<"Case #"<<t<<": "<<ans<<endl;
  }

  return 0;
}
