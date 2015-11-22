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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

const int MAXN = 202020;

int N, M, K;

char sex[MAXN];
int fa[MAXN], mo[MAXN];
int dna[MAXN];
bool alive[MAXN];
int par[MAXN];
bool anyalive[MAXN];

int djFind(int v)
{
	if(par[v] == v) return v;
	return par[v] = djFind(par[v]);
}

void djUnion(int u, int v)
{
	int pu = djFind(u), pv = djFind(v);
	if(pu != pv)
		par[pu] = pv;
}

int main() {
	FILEIO("eve");

	IOS;
	cin>>N;
	for(int i=1; i<=N; i++)
	{
		cin>>sex[i];
		alive[i] = true;
		fa[i] = mo[i] = -1;
		dna[i] = -1;
	}
	cin>>M;
	for(int i=0; i<M; i++)
	{
		int x, y;
		char c;
		cin>>x;
		if(x > 0)
		{
			N++;
			cin>>y>>c;
			sex[N] = c;
			fa[N] = x;
			mo[N] = y;
			alive[N] = true;
			dna[N] = -1;
		}
		else
		{
			alive[-x] = false;
		}
	}
	cin>>K;
	for(int i=0; i<K; i++)
	{
		int a, b;
		cin>>a>>b;
		dna[a] = b;
	}

	for(int i=1; i<=N; i++)
		par[i] = i;

	for(int i=1; i<=N; i++)
	{
		if(mo[i] == -1) continue;
		djUnion(i, mo[i]);
	}

	for(int i=1; i<=N; i++)
	{
		if(dna[i] == -1) continue;
		int p = djFind(i);
		dna[p] = dna[i];
	}

	set<int> vec;

	for(int i=1; i<=N; i++)
	{
		if(!alive[i]) continue;
		int p = djFind(i);
		anyalive[p] = true;
	}

	for(int i=1; i<=N; i++)
	{
		if(djFind(i) != i) continue;
		if(!anyalive[i]) continue;
		if(dna[i] == -1) vec.insert(-i);
		else vec.insert(dna[i]);
	}

	if(vec.size() <= 1)
		cout<<"YES"<<endl;
	else
	{
		int plus = 0;
		for(auto v: vec)
			if(v > 0)
				plus++;
		if(plus <= 1)
			cout<<"POSSIBLY"<<endl;
		else
			cout<<"NO"<<endl;
	}



    return 0;
}
