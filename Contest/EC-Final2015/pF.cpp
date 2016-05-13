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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
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

const int MAXN = 1010101;
const ll MOD = 1000000007;

int N, K;
ll sum[MAXN];
ll dp[MAXN], dpsum[MAXN];
ll twopow[MAXN];
int les[MAXN];

void pre()
{
	for(int i=1; i<MAXN; i++)
		sum[i] = (ll)i * (i+1) / 2;

	twopow[0] = 1;
	for(int i=1; i<MAXN; i++)
		twopow[i] = (twopow[i-1] * 2) % MOD;

	int curl = 0;
	for(int i=1; i<MAXN; i++)
	{
		while(2 * sum[curl+1] < sum[i]) curl++;
		les[i] = curl;
	}
}

ll calc()
{
	for(int i=0; i<=N; i++)
		dp[i] = dpsum[i] = 0;

	dp[K] = twopow[les[K]];
	dpsum[K] = dp[K];

	for(int i=K+1; i<=N; i++)
	{
		int s = les[i];
		if(s < i-1)
		{
			dp[i] = (dpsum[i-1] - dpsum[s]) % MOD;
			if(dp[i] < 0) dp[i] += MOD;
		}
		dpsum[i] = (dpsum[i-1] + dp[i]) % MOD;
	}

	ll ans = (dp[N] * 2) % MOD;

	return ans;
}

int main() {
	IOS;

	pre();

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>K;
		ll ans = calc();
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

