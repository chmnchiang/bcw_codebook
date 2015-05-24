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
typedef long double ld;

const int MAXN = 111;

int N;

ld a[MAXN], b[MAXN];
ll S, L, U;

vector<ll> gotograd(ld g)
{
  vector<ll> vec;
  for(int i=0; i<N; i++)
    vec.PB(min(U, max(L, ll(b[i]+g))));
  return vec;
}

ll calc_sum(vector<ll> &vec)
{
  ll ans = 0;
  for(auto i: vec)
    ans += i;
  return ans;
}

void xassert(bool x)
{
  if(!x) while(1);
}

int main(){
  IOS;
  FILEIO("exam");

  while(cin>>N>>S && N)
  {
    for(int i=0; i<N; i++)
      cin>>a[i];
    cin>>L>>U;
    ld sinva = 0;
    for(int i=0; i<N; i++)
      sinva += 1/a[i];
    for(int i=0; i<N; i++)
      b[i] = S / (a[i] * sinva);
    //for(int i=0; i<N; i++)
    //  cout<<b[i]<<" ";
    //cout<<endl;

    ld lb = -S, rb = S;
    vector<ll> vec;
    while(rb - lb > 1E-10)
    {
      ld mb = (lb + rb) / 2;
      vec = gotograd(mb);
      ll sum = calc_sum(vec);
      if(sum >= S)
        rb = mb;
      else
        lb = mb;
    }

    vec = gotograd(rb+1E-10);
    ll sum = calc_sum(vec);
    //cout<<sum<<endl;

    ld maxval = -1E20;
    for(int i=0; i<N; i++)
      if(vec[i] > L)
        maxval = max(maxval, vec[i]-b[i]);

    int cnt = sum - S;
    xassert(cnt >= 0);
    for(int i=0; i<N; i++)
    {
      if(cnt <= 0) break;
      if(vec[i]-b[i] >= maxval - 1E-7 && vec[i] > L)
      {
        cnt--;
        vec[i]--;
      }
    }

    //xassert(cnt == 0);

    //for(int i=0; i<N; i++)
      //xassert(vec[i] >= L && vec[i] <= U);
    for(auto i: vec) cout<<i<<" ";cout<<endl;
  }

	return 0;
}

