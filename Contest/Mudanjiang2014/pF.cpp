#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

const int MAXN = 52;
const int MAXL = 50505;
const ll MOD = 1000000007;

int N;
int L[MAXN], R[MAXN];
ll f[MAXN][MAXL];
ll g[MAXN][MAXL];
ll h[MAXN][MAXL];
ll tmp[MAXL];
vector<int> edge[MAXN];
int par[MAXN];
vector<int> ch[MAXN];
bool vis[MAXN];
ll ans[MAXN];
bool isp[MAXL];
vector<int> pfactor[MAXL];
ll sum[MAXL];

void pre()
{
	for(int i=2; i<MAXL; i++)
		isp[i] = true;
	for(int i=2; i<MAXL; i++)
	{
		if(!isp[i]) continue;
		for(int j=i; j<MAXL; j+=i)
		{
			pfactor[j].PB(i);
			isp[j] = false;
		}
		isp[i] = true;
	}
}

void init()
{
	for(int i=0; i<MAXN; i++)
	{
		edge[i].clear();
		ch[i].clear();
		par[i] = -1;
		vis[i] = false;
	}
}

void coprime_sum(ll arr[MAXL], ll brr[MAXL])
{
	for(int i=0; i<MAXL; i++)
		brr[i] = sum[i] = 0;
	for(int i=1; i<MAXL; i++)
	{
		for(int j=i; j<MAXL; j+=i)
			sum[i] = (sum[i] + arr[j]) % MOD;
	}

	for(int i=1; i<MAXL; i++)
	{
		int Z = pfactor[i].size();
		ll an = 0;
		for(int j=0; j<(1<<Z); j++)
		{
			int cur = 1;
			for(int k=0; k<Z; k++)
				if(j&(1<<k))
					cur *= pfactor[i][k];
			int bp = (__builtin_popcount(j)%2 ? -1 : 1);
			an += bp * sum[cur];
		}
		an %= MOD;
		if(an < 0) an += MOD;
		brr[i] = an;
	}

	//for(int i=1; i<=10; i++) cout<<arr[i]<<" ";cout<<endl;
	//for(int i=1; i<=10; i++) cout<<brr[i]<<" ";cout<<endl;
}


void dfs(int v, int p)
{
	if(vis[v]) return;
	vis[v] = true;
	par[v] = p;
	if(p != -1)
		ch[p].PB(v);
	for(auto c: edge[v])
		dfs(c, v);
}

void calc(int v)
{
	for(int i=0; i<MAXL; i++)
		f[v][i] = 0;
	for(int i=L[v]; i<=R[v]; i++)
		f[v][i] = 1;

	for(auto u: ch[v])
	{
		calc(u);
		coprime_sum(f[u], h[u]);
		for(int i=0; i<MAXL; i++)
			f[v][i] = (f[v][i] * h[u][i]) % MOD;
	}

	//cout<<"F "<<v<<" : "; for(int i=1; i<=10; i++) cout<<f[v][i]<<" ";cout<<endl;
}

void calc2(int v)
{
	if(v == 0)
	{
		for(int i=0; i<MAXL; i++)
			g[v][i] = 0;
		for(int i=L[v]; i<=R[v]; i++)
			g[v][i] = 1;
		for(auto c: ch[v])
			calc2(c);
		return;
	}

	int p = par[v];
	for(int i=0; i<MAXL; i++)
		tmp[i] = g[p][i];
	for(auto u: ch[p])
	{
		if(u == v) continue;
		for(int i=0; i<MAXL; i++)
			tmp[i] = (tmp[i] * h[u][i]) % MOD;
	}
	
	coprime_sum(tmp, g[v]);
	for(int i=0; i<MAXL; i++)
		if(!(L[v] <= i && i <= R[v]))
			g[v][i] = 0;
	//cout<<"G "<<v<<" : "; for(int i=1; i<=10; i++) cout<<g[v][i]<<" ";cout<<endl;
	for(auto c: ch[v])
		calc2(c);
}

void calc_ans()
{
	for(int i=0; i<N; i++)
	{
		ans[i] = 0;
		for(int j=L[i]; j<=R[i]; j++)
		{
			ans[i] += (f[i][j] * g[i][j] % MOD) * j % MOD;
		}
		ans[i] %= MOD;
	}
}

int main() {
	pre();
    IOS;
	int T;
	cin>>T;
	while(T--)
	{
		init();
		cin>>N;
		for(int i=0; i<N; i++)
			cin>>L[i];
		for(int i=0; i<N; i++)
			cin>>R[i];
		for(int i=0; i<N-1; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			edge[a].PB(b);
			edge[b].PB(a);
		}
		dfs(0, -1);

		calc(0);
		calc2(0);
		calc_ans();

		for(int i=0; i<N; i++)
			cout<<ans[i]<<(i==N-1 ? "\n" : " ");
	}

    return 0;
}
