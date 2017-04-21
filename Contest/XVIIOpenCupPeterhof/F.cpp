#pragma GCC optimize ("O2")
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
typedef pair<ll, ll> pll;

pll gcd(ll a, ll b){
	if(b == 0) return make_pair(1, 0);
	else{
		ll p = a / b;
		pll q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}

ll P, Q;

ll calc()
{
	if(P > Q) swap(P, Q);
	if(P == 0) return Q == 1 ? 1 : -1;
	if(__gcd(P, Q) != 1) return -1;
	if((P+Q) % 2 == 0) return -1;

	ll x, y;
	tie(x, y) = gcd(P, Q);

	ll ans = 1LL<<60;
	for(int k=0; k<=1; k++)
	{
		for(int l=-5; l<=5; l++)
		{
			ll a = x + k*P + l*Q, b = x - k*P + l*Q, c = y + k*Q - l*P, d = y - k*Q - l*P;
			if(a%2!=0 or b%2!=0 or c%2!=0 or c%2!=0) continue;
			ll val = abs(a) + abs(b) + abs(c) + abs(d);
			val /= 2;
			ans = min(ans, val);
		}
	}

	return ans;
}

int main() {
	IOS;

	while(cin>>P>>Q)
	{
		ll ans = calc();
		cout<<ans<<endl;
	}

	return 0;
}

