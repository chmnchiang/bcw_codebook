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
typedef pair<pll, ll> ppl;

const int MAXN = 3030;

int N, M;
pll pt[MAXN];
map<ppl, int> mp;

ll dis(ll x, ll y)
{
	return x*x+y*y;
}

int main(){
	IOS;
	FILEIO("astronomy");

	while(cin>>N && N)
	{
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;
		mp.clear();
		for(int i=0; i<N; i++)
		{
			for(int j=i+1; j<N; j++)
			{
				ll a = dis(pt[i].F, pt[i].S);
				ll b = dis(pt[j].F, pt[j].S);
				ll c = dis(pt[i].F-pt[j].F, pt[i].S-pt[j].S);
				if(a > b) swap(a, b);
				ppl alpha = ppl(pll(a, b), c);
				mp[alpha]++;
			}
		}
		
		cin>>M;
		for(int i=0; i<M; i++)
		{
			ll a, b, c;
			cin>>a>>b>>c;
			if(a > b) swap(a, b);
			cout<<mp[ppl(pll(a, b), c)]<<"\n";
		}
	}

	return 0;
}

