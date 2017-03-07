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

typedef pair<int, int> pii;
const int MAXN = 155;

int N, M;
int arr[MAXN][MAXN];
int h[MAXN];
bool vis[MAXN];
vector<pii> edge[MAXN];

bool dfs(int v, int pot)
{
	if(vis[v])
	{
		return h[v] == pot;
	}
	else
	{
		h[v] = pot;
		vis[v] = true;
		for(auto p: edge[v])
			if(!dfs(p.F, pot + p.S))
				return false;
		return true;
	}
}

void calc()
{
	for(int i=0; i<N; i++)
		vis[i] = false;

	bool ok = true;
	for(int i=0; i<N; i++)
		if(!vis[i])
			if(!dfs(i, 0))
				ok = false;

	if(!ok)
	{
		cout<<"Impossible"<<endl;
		return;
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			cout<<(arr[i][j] + h[j] - h[i])<<" \n"[j==N-1];
}

int main() {
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<N; i++)
			edge[i].clear();
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				cin>>arr[i][j];
		cin>>M;
		for(int i=0; i<M; i++)
		{
			int s, t, d;
			cin>>s>>t>>d;
			s--;
			t--;
			edge[s].PB({t, d});
			edge[t].PB({s, -d});
		}

		calc();
	}

	return 0;
}

