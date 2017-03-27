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
typedef pair<int, int> pii;
typedef pair<ll, pii> Edge;
const int MAXN = 1010101;

int root[MAXN];

void djInit(int n)
{
	for(int i=1; i<=n; i++)
		root[i] = i;
}

int djFind(int v)
{
	if(root[v] == v) return v;
	return root[v] = djFind(root[v]);
}

bool djUnion(int u, int v)
{
	int pu = djFind(u), pv = djFind(v);
	if(pu == pv) return false;
	root[pu] = pv;
	return true;
}

ll mst(int n, int s)
{
	vector<Edge> edge;

	int x = s;
	for(int i=2; i<=n; i++)
	{
		x = x * 907 % 2333333;
		int T = x;
		for(int j=max(1, i-5); j<=i-1; j++)
		{
			x = x * 907 % 2333333;
			int w = T ^ x;
			edge.PB({w, {i, j}});
		}
	}

	sort(ALL(edge));

	ll ans = 0;

	djInit(n);
	for(auto e: edge)
	{
		ll w = e.F;
		int u = e.S.F, v = e.S.S;
		if(djUnion(u, v))
			ans += w;
	}

	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		int N, S;
		cin>>N>>S;

		ll ans = 0;
		if(N < 108)
		{
			ans = mst(N, S);
		}
		else
		{
			int n = (N % 54) + 54;
			ll base = mst(n, S);
			ll dif = mst(n+54, S) - base;
			ans = base + dif * ((N - n) / 54);
		}
		
		cout<<ans<<endl;
	}

	return 0;
}

