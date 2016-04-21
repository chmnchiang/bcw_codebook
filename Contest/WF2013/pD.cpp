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
typedef __int128_t lll;

const int MAXN = 10101;
const lll LIM = 1ULL<<63;

bool isp[MAXN];
vector<int> primes;
vector<int> stk;
map<ll, ll> mp;

ll get_num()
{
	int tot = 0;
	for(auto v: stk)
		tot += v;

	vector<ll> up, down;
	for(int i=1; i<=tot; i++)
		up.PB(i);
	for(auto v: stk)
		for(int i=1; i<=v; i++)
			down.PB(i);

	for(auto d: down)
	{
		for(auto &u: up)
		{
			if(u == 1) continue;
			if(d == 1) break;
			ll g = __gcd(u, d);
			u /= g;
			d /= g;
		}
	}

	lll res = 1;
	for(auto u: up)
	{
		res *= u;
		if(res >= LIM)
			return -1;
	}
	return res;
}

void dfs(int lv, lll val)
{
	ll res = get_num();
//	cout<<stk<<" = "<<(ll)val<<" / "<<res<<endl;

	if(res != -1 && val > 1)
	{
		if(!mp.count(res))
			mp[res] = LIM-1;
		mp[res] = min(mp[res], (ll)val);
	}

	ll p = primes[lv];
	int lm = 10000;
	if(!stk.empty())
		lm = stk.back();
	for(int i=1; i<=lm; i++)
	{
		val *= p;
		if(val >= LIM) break;
		stk.PB(i);
		dfs(lv+1, val);
		stk.pop_back();
	}
}

void pre()
{
	for(int i=2; i<MAXN; i++)
		isp[i] = true;
	for(int i=2; i<MAXN; i++)
	{
		if(!isp[i]) continue;
		primes.PB(i);
		for(int j=2*i; j<MAXN; j+=i)
			isp[j] = false;
	}

	dfs(0, 1);
}

ll calc(ll N)
{
	return mp[N];
}

int main() {
	IOS;
	pre();

	ll N;
	while(cin>>N)
	{
		ll ans = calc(N);
		cout<<N<<" "<<ans<<"\n";
	}

	return 0;
}

