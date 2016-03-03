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

const int MAXN = 1010;

pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}

int N;
ll M;
pll pt[MAXN];

ll calc()
{
	ll ans = 0;
	ll area = 0;
	vector<pll> vec;
	for(int i=0; i<N; i++)
	{
		int j = (i+1)%N, k = (i+N-1)%N;
		ll c = cross(pt[i]-pt[j], pt[i]-pt[k]);
		if(c)
			vec.PB(pt[i]);
	}

	int V = vec.size();
	ll g = 0;
	ll out = 0;
	for(int i=0; i<V; i++)
	{
		int j = (i+1) % V;
		area += cross(vec[i], vec[j]);
		pll dif = vec[i] - vec[j];
		ll tg = __gcd(abs(dif.F), abs(dif.S));
		g = __gcd(g, tg);
		out += tg;
	}
	area = abs(area);
	area /= g * g;
	out /= g;

	for(int i=1; i<=M; i++)
	{
		ans += (area * i * i - out * i) / 2 + 1;
	}

	return ans;
}

int main() {
    IOS;

	int t = 0;
	while(cin>>N>>M && N && M)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;
		ll ans = calc();
		cout<<"Case "<<t<<": "<<ans<<endl;
	}

    return 0;
}

