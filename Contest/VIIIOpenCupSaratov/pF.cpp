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
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;

const int MAXN = 101010;
const int LG = 18;
const ll INF = 1LL<<60;

int N, M;
vector<pil> edge[MAXN];
ll s[MAXN], d[MAXN], t[MAXN];
int A, B;
ll V, tl, tr;
int par[LG][MAXN];
int dep[MAXN];
ll len[MAXN];

void dfs(int v, int p, ll dd, ll l)
{
	par[0][v] = p;
	dep[v] = dd;
	len[v] = l;
	for(auto e: edge[v])
	{
		if(e.F == p) continue;
		dfs(e.F, v, dd+1, l+e.S);
	}
}

int lca(int a, int b)
{
	if(dep[a] > dep[b])
		swap(a, b);
	int dif = dep[b] - dep[a];
	for(int i=0; i<LG; i++)
		if(dif&(1<<i))
			b = par[i][b];
	if(a == b) return a;
	for(int i=LG-1; i>=0; i--)
	{
		int pa = par[i][a], pb = par[i][b];
		if(pa != pb)
		{
			a = pa;
			b = pb;
		}
	}
	return par[0][a];
}

ll calc()
{
	dfs(A, A, 0, 0);

	for(int i=1; i<LG; i++)
		for(int j=1; j<=N; j++)
			par[i][j] = par[i-1][par[i-1][j]];

	map<ll, pll> mp;
	mp[tl] = {0, 0};
	mp[tr] = {0, 0};

	for(int i=0; i<M; i++)
	{
		int p1 = lca(B, s[i]);
		int p2 = lca(B, d[i]);
		if(dep[p1] >= dep[p2]) continue;

		ll alpha = t[i] + len[s[i]] - len[p1];
		ll beta = alpha + len[p2] - len[p1];
		ll x = len[p1];
		ll y = len[p2];
		ll lb = alpha - (x / V);
		ll rb = beta - (y / V);

		mp[lb] = {mp[lb].F + V, mp[lb].S + x - V * alpha}; 
		mp[rb] = {mp[rb].F - V, mp[rb].S - x + V * alpha}; 
	}

	ll best = INF;
	ll btime = -1;
	ll slope = 0, offset = 0;
	for(auto p: mp)
	{
		int v = p.F;
		slope += p.S.F;
		offset += p.S.S;
		ll val = slope * v + offset;
		if(tl <= v && v <= tr && val < best)
		{
			best = val;
			btime = v;
		}
	}

	return btime;
}

int main() {
	IOS;
	FILEIO("sapsan");

	cin>>N;
	for(int i=0; i<N-1; i++)
	{
		int x, y;
		ll l;
		cin>>x>>y>>l;
		edge[x].PB({y, l});
		edge[y].PB({x, l});
	}
	
	cin>>M;
	for(int i=0; i<M; i++)
		cin>>s[i]>>d[i]>>t[i];

	cin>>A>>B>>V>>tl>>tr;

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

