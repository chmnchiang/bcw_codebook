#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MAXN = 111;

int N, M;
bool edge[MAXN][MAXN];
bool vis[MAXN];
vector<int> vec;
int deg[MAXN];

void dfs(int v)
{
	if(vis[v]) return;
	vis[v] = true;
	vec.PB(v);

	for(int i=0; i<N; i++)
		if(edge[v][i])
			dfs(i);
}

bool check()
{
	int sz = vec.size();
	if(sz%2) return false;

	sort(vec.begin(), vec.end(), [](int a, int b){return deg[a] > deg[b];});
	int p = vec[0], q = vec[1];
	if(!edge[p][q]) return false;
	vector<int> v1, v2;
	v1.PB(p);
	v2.PB(q);
	for(int i=0; i<N; i++)
	{
		if(edge[p][i] && i != q) v1.PB(i);
		if(edge[q][i] && i != p) v2.PB(i);
	}

	if((int)v1.size() != sz/2) return false;
	if((int)v2.size() != sz/2) return false;
	
	for(auto v: v1)
		for(auto u: v1)
			if(v != u && !edge[v][u])
				return false;
	for(auto v: v2)
		for(auto u: v2)
			if(v != u && !edge[v][u])
				return false;
	for(auto v: v1)
		for(auto u: v2)
			if(v == u || (!(v == p && u == q) && edge[v][u]))
				return false;

	return true;
}

int main() {
	IOS;
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M;
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				edge[i][j] = false;
		for(int i=0; i<N; i++)
		{
			vis[i] = false;
			deg[i] = 0;
		}

		for(int i=0; i<M; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			edge[a][b] = edge[b][a] = true;
			deg[a]++;
			deg[b]++;
		}

		int ans = 0;
		for(int i=0; i<N; i++)
		{
			if(vis[i]) continue;
			vec.clear();
			dfs(i);
			if(check())
				ans++;
		}

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

    return 0;
}


