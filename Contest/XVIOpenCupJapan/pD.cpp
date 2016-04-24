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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

typedef long long ll;
typedef pair<ll, ll> pll;

ll N;

vector<pll> factorize(ll x)
{
	vector<pll> vec;
	for(int i=2; i<=40000; i++)
	{
		int cnt = 0;
		while(x % i == 0)
		{
			x /= i;
			cnt++;
		}
		if(cnt)
			vec.PB({i, cnt});
	}
	if(x > 1)
		vec.PB({x, 1});
	return vec;
}

ll calc_phi(ll x, vector<pll> fact)
{
	for(auto p: fact)
		x = x / p.F * (p.F-1);
	return x;
}

vector<ll> expand(vector<pll> vec)
{
	vector<ll> ret;
	ret.PB(1);
	for(auto p: vec)
	{
		ll v = p.F, c = p.S;
		int S = ret.size();
		for(int i=0; i<c; i++)
		{
			for(int j=0; j<S; j++)
			{
				ret.PB(ret[i*S+j] * v);
			}
		}
	}

	return ret;
}

ll lpow(ll a, ll p, ll m)
{
	ll ret = 1, cur = a % m;
	while(p)
	{
		if(p&1LL)
			ret = (ret * cur) % m;
		cur = (cur * cur) % m;
		p >>= 1;
	}
	return ret;
}

ll calc()
{
	if(N == 2) return 1;
	vector<pll> fac = factorize(N);
	for(auto p: fac)
		if(p.S >= 2)
			return -1;

	vector<ll> fp1;
	for(auto x: fac)
		fp1.PB(x.F-1);
	ll lN = 1;
	for(auto x: fp1)
		lN = lN * x / __gcd(lN, x);
	if(__gcd(N, lN) > 1)
		return -1;
	ll plN = calc_phi(lN, factorize(lN));
	vector<ll> pfac = expand(factorize(plN));
//	cout<<N<<" "<<lN<<" "<<plN<<" "<<pfac<<endl;
	for(auto k: pfac)
		if(lpow(N, k, lN) == 1)
			return k;
	return -1;
}

ll calc2()
{
	ll pN = calc_phi(N, factorize(N));
	for(int k=1; k<=2*N; k++)
	{
		bool ok = true;
		ll nk = lpow(N, k, pN);
		for(int a=1; a<N; a++)
		{
			if(lpow(a, nk, N) != a)
			{
				ok = false;
				break;
			}
		}
		if(!ok) continue;
		return k;
	}
	return -1;
}

int main() {
	IOS;

/*	for(int i=2; i<=10000; i++)
	{
		N = i;
		if(calc() != calc2())
		cout<<i<<" : "<<calc()<<" "<<calc2()<<endl;
	}*/

	cin>>N;
	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

