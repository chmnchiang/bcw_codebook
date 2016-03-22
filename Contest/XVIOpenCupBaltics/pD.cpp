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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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
typedef pair<ll, ll> pll;

pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}

const int MAXN = 101010;

int N;
pll pt[MAXN][3];
multimap<pll, int> mp;

void calc()
{
  for(int i=0; i<N; i++)
  {
    pll da = pt[i][1] - pt[i][0];
    pll db = pt[i][2] - pt[i][0];
    if(cross(da, db) < 0)
      swap(pt[i][1], pt[i][2]);

    while(true)
    {
      da = pt[i][1] - pt[i][0];
      db = pt[i][2] - pt[i][0];
      if(dot(da, db) != 0)
      {
        swap(pt[i][0], pt[i][1]);
        swap(pt[i][1], pt[i][2]);
      }
      else break;
    }

    ll disa = dot(da, da), disb = dot(db, db);
    mp.insert({{disa, disb}, i+1});
  }

  vector<pll> vans;
  while(!mp.empty())
  {
    auto it1 = mp.begin();
    pll p1 = it1->F;
    int i1 = it1->S;
    mp.erase(it1);

    pll p2 = {p1.S, p1.F};
    int i2 = 0;
    if(mp.count(p2))
    {
      auto it2 = mp.lower_bound(p2);
      i2 = it2->S;
      mp.erase(it2);
    }
    vans.PB({i1, i2});
  }

  cout<<vans.size()<<"\n";
  for(auto p: vans)
    cout<<p.F<<"-"<<p.S<<"\n";
}

int main() {
  IOS;
  FILEIO("kites");
  cin>>N;
  for(int i=0; i<N; i++)
    for(int j=0; j<3; j++)
      cin>>pt[i][j].F>>pt[i][j].S;

  calc();

  return 0;
}

