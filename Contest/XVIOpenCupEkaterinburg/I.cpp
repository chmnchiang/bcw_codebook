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

const int MAXN = 105;
const ll INF = 1LL<<40;

int N, K, C, M, Q;
ll arr[MAXN][MAXN];
int suse[MAXN][MAXN];
int thisuse[MAXN];
ll dp[MAXN];

struct KM{
    // Maximum Bipartite Weighted Matching (Perfect Match)
	static const int MXN = 650;
	static const ll INF = 1LL<<60; // long long
	int n,match[MXN],vx[MXN],vy[MXN];
	ll edge[MXN][MXN],lx[MXN],ly[MXN],slack[MXN];
	// ^^^^ long long
	void init(int _n){
		n = _n;
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				edge[i][j] = 0;
	}
	void add_edge(int x, int y, ll w){ // long long
		edge[x][y] = w;
	}
	bool DFS(int x){
		vx[x] = 1;
		for (int y=0; y<n; y++){
			if (vy[y]) continue;
			if (lx[x]+ly[y] > edge[x][y]){
				slack[y] = min(slack[y], lx[x]+ly[y]-edge[x][y]);
			} else {
				vy[y] = 1;
				if (match[y] == -1 || DFS(match[y])){
					match[y] = x;
					return true;
				}
			}
		}
		return false;
	}
	ll solve(){
		fill(match,match+n,-1);
		fill(lx,lx+n,-INF);
		fill(ly,ly+n,0);
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				lx[i] = max(lx[i], edge[i][j]);
		for (int i=0; i<n; i++){
			fill(slack,slack+n,INF);
			while (true){
				fill(vx,vx+n,0);
				fill(vy,vy+n,0);
				if ( DFS(i) ) break;
				ll d = INF; // long long
				for (int j=0; j<n; j++)
					if (!vy[j]) d = min(d, slack[j]);
				for (int j=0; j<n; j++){
					if (vx[j]) lx[j] -= d;
					if (vy[j]) ly[j] += d;
					else slack[j] -= d;
				}
			}
		}
		ll res=0;
		for (int i=0; i<n; i++)
			res += edge[match[i]][i];
		return res;
	}
} graph;

ll solve_use()
{
	graph.init(N);
	int match_cnt = 0;
	for(int j=0; j<K; j++)
	{
		if(!thisuse[j]) continue;
		match_cnt++;
		for(int i=0; i<N; i++)
			graph.add_edge(i, j, INF-arr[i][j]*thisuse[j]);
	}

	ll res = graph.solve();
	ll cst = INF * match_cnt - res;
//	cout<<"MATCH "<<cst<<endl;
	return cst;
}

ll calc()
{
	dp[0] = 0;
	for(int i=1; i<=Q; i++)
	{
		dp[i] = INF;
		for(int j=0; j<i; j++)
		{
			for(int k=0; k<K; k++)
				thisuse[k] = suse[i][k] - suse[j][k];
//			cout<<i<<" ~ "<<j<<" :"; for(int k=0; k<K; k++) cout<<" "<<thisuse[k]; cout<<endl;
			ll cst = solve_use() + C;
			dp[i] = min(dp[i], dp[j] + cst);
		}
	}
	return dp[Q];
}

int main() {
	IOS;

	cin>>N>>K>>C;
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			arr[i][j] = INF;
	cin>>M;
	for(int i=0; i<M; i++)
	{
		int s, t;
		ll w;
		cin>>s>>t>>w;
		s--;
		t--;
		arr[s][t] = w;
	}

	cin>>Q;
	for(int i=0; i<K; i++)
		suse[0][i] = 0;
	for(int i=0; i<Q; i++)
	{
		for(int j=0; j<K; j++)
		{
			cin>>suse[i+1][j];
			suse[i+1][j] += suse[i][j];
		}
	}

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

