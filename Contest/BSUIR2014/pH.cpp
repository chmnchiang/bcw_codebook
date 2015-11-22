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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;

const int MAXN = 101010;
const ll MOD = 1000000007;

int N;

ll krr[MAXN], arr[MAXN];

ll f(ll s, ll k, ll a)
{
	ll x = 2 * s + (k+1) * a;
	ll y = k;
	if(x % 2 == 0) x /= 2;
	else y /= 2;
	return x * y;
}

ll g(ll s, ll l, ll a)
{
	if(a < 0)
	{
		s = -s;
		a = -a;
	}
	if(a == 0)
	{
		return abs(s) * l;
	}
	if(s >= 0)
	{
		return f(s, l, a);
	}
	else
	{
		ll k = (-s) / a;
		k = min(k, l);
		return -f(s, k, a) + f(s+k*a, l-k, a);
	}
}

int main() {
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>krr[i]>>arr[i];

	ll sum = 0;
	ll ans = 0;

	ll average = 0;
	ll total = 0;
	for(int i=0; i<N; i++)
	{
		average += krr[i] * arr[i];
		total += krr[i];
	}
	average /= total;

	for(int i=0; i<N; i++)
	{
		ans += g(sum, krr[i], arr[i] - average);
		ans %= MOD;
		sum += krr[i] * (arr[i] - average);
	}

	cout<<ans<<endl;

	return 0;
}

