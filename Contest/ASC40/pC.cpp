//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ld;

const int MAXN = 101010;
const ll INF = 1LL<<62;

int N;
vector<int> vec[4]; // N, S, E, W
pll pt[MAXN], tmp[MAXN];
int group[MAXN];
vector<int> vsort;

ll ans;
int ansx, ansy;
ld anst;
ll sort_x, sort_y;
ll dis_ratio;

pll operator- (pll a, pll b) { return MP(a.F-b.F, a.S-b.S);}
ll abs2(pll a) { return a.F*a.F + a.S*a.S; }

void update_ans(ll d, int x, int y, ld t)
{
  if(d < ans)
  {
    ans = d;
    ansx = x;
    ansy = y;
    anst = t;
  }
}

bool cmp(int a, int b)
{
  return tmp[a] < tmp[b];
}

void osort()
{
  for(auto v: vsort)
  {
    tmp[v] = MP(pt[v].F * sort_x + pt[v].S * sort_y, -pt[v].F * sort_y + pt[v].S * sort_x);
  }
  sort(vsort.begin(), vsort.end(), cmp);
}

void shortest_pair()
{
  vsort.clear();
  for(int i=0; i<N; i++)
    vsort.PB(i);
  sort_x = 1;
  sort_y = 0;
  dis_ratio = 2;
  osort();

  int L = vsort.size();
  for(int i=0; i<L; i++)
  {
    int v = vsort[i];
    for(int j=i+1; j<L; j++)
    {
      int u = vsort[j];
      ll xdiff = tmp[u].F - tmp[v].F;
      if(xdiff * xdiff >= ans) break;
      ll dis2 = abs2(tmp[u] - tmp[v]);
      update_ans(dis2 * dis_ratio, u, v, 0.);
    }
  }
}

void check_pair(int c1, int c2, ll sx, ll sy, ll drat, ld vel)
{
  sort_x = sx;
  sort_y = sy;
  dis_ratio = drat;

  vsort.clear();
  for(auto v: vec[c1]) vsort.PB(v);
  for(auto v: vec[c2]) vsort.PB(v);
  osort();

  map<ll, int> mp;
  for(auto v: vsort)
  {
    ll x = tmp[v].F, y = tmp[v].S;
    if(group[v] == c1)
    {
      mp[y] = v;
    }
    else
    {
      if(mp.empty()) continue;
      auto it = mp.lower_bound(y);
      if(it == mp.end()) it--;
      int u = it->S;
      ll dis = (it->F-y) * (it->F-y);
      if(it != mp.begin())
      {
        it--;
        ll dis2 = (it->F-y) * (it->F-y);
        if(dis2 < dis)
        {
          dis = dis2;
          u = it->S;
        }
      }
      ll dx = x - tmp[u].F;
      ld dt = dx / vel;
      update_ans(dis * drat, v, u, dt);
    }
  }
}

int main(){
  IOS;
  FILEIO("collision");

  while(cin>>N && N)
  {
    for(int i=0; i<4; i++)
      vec[i].clear();
    ans = INF;
    
    for(int i=0; i<N; i++)
    {
      char c;
      cin>>pt[i].F>>pt[i].S>>c;
      if(c == 'N') vec[0].PB(i);
      else if(c == 'S') vec[1].PB(i);
      else if(c == 'E') vec[2].PB(i);
      else if(c == 'W') vec[3].PB(i);
    }

    for(int i=0; i<4; i++)
      for(auto v: vec[i]) group[v] = i;

    shortest_pair();

    check_pair(0, 1, 0, 1, 2, 2);
    check_pair(2, 3, 1, 0, 2, 2);
    check_pair(0, 2,-1, 1, 1, 2);
    check_pair(0, 3, 1, 1, 1, 2);
    check_pair(1, 2,-1,-1, 1, 2);
    check_pair(1, 3, 1,-1, 1, 2);


    ld rans = sqrt(ans * 2) / 2;
    cout<<fixed<<setprecision(15)<<rans<<endl;
    cout<<ansx+1<<" "<<ansy+1<<endl;
    cout<<fixed<<setprecision(15)<<anst<<endl;
  }

	return 0;
}

