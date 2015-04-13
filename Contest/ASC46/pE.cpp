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

const int MAXN = 3030;
const ll INF = 1LL<<60;

int N;
ll arr[MAXN];
ll sum[MAXN];
ll dp[MAXN];

int main(){
	FILEIO("ebola");

	while(cin>>N && N>0)
	{
		for(int i=0; i<N; i++)
			cin>>arr[i];
		sum[N] = 0;
		for(int i=N-1; i>=0; i--)
			sum[i] = sum[i+1] + arr[i];

		for(int i=0; i<N; i++)
		{
			dp[i] = INF;
			ll cur = 0;
			for(int k=i; k>=0; k--)
			{
				if(k<i)
				{
					ll dif = 3 * (i-k) * arr[k] - (sum[k+1] - sum[i+1]);
					if(dif < 0)
						cur += dif;
				}
				dp[i] = min(dp[i], dp[k-1] + cur + 2 * (i-k) * sum[i+1]);
			}
		}

		ll ans = dp[N-1];
		for(int i=0; i<N; i++)
			ans += 2 * i * arr[i];

		cout << ans << endl;
	}

	return 0;
}

