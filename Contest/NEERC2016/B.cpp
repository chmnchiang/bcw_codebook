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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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

#define int long long
typedef long long ll;

const int MAXN = 3030303;
const ll MOD = 100000000000031LL;
const ll HSH = 13131;

struct Scc{
  int n, nScc, vst[MAXN], bln[MAXN];
  vector<int> E[MAXN], rE[MAXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<n; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    for (int i=0; i<n; i++) vst[i] = 0;
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    for (int i=0; i<n; i++) vst[i] = 0;
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
} scc;

int N, M, V;
string s[MAXN];
ll hv[MAXN];
bool hw[MAXN];
map<ll, int> mp;
map<ll, vector<int>> mpv;
vector<int> edge[MAXN];

int get_node(ll h)
{
	if(!mp.count(h))
		mp[h] = M++;
	return mp[h];
}

void calc()
{
	M = 0;
	mp.clear();
	mpv.clear();
	for(int i=0; i<N; i++)
	{
		bool haswen = false;
		for(int j=0; j<2; j++)
		{
			ll hval = 7;
			int lid = 0, id = -1;
			for(auto c: s[i])
			{
				if(c == '?') haswen = true;
				bool z = (c == '1' or (j and c == '?'));
				hval = (hval * HSH + z * 37373) % MOD;
				lid = id;
				id = get_node(hval);
				if(lid != -1)
				{
					edge[2*(N+lid)].PB(2*(N+id));
					edge[2*(N+id)+1].PB(2*(N+lid)+1);
				}
			}
			int x = 2*i+j;
			int x1 = x^1;
			hv[x] = hval;
			edge[x].PB(2*(N+id));
			edge[2*(N+lid)].PB(x1);
			edge[x].PB(2*(N+lid)+1);
			edge[2*(N+id)+1].PB(x1);
			if(!haswen)
			{
				edge[x].PB(x1);
				edge[x1].PB(x);
			}
			mpv[hval].PB(x);
		}
		hw[i] = haswen;
	}

	V = 2*(N+M);
	for(auto h: mpv)
	{
		vector<int> &vec = h.S;
		int k = SZ(vec);
		
		for(int i=0; i<k-2; i++)
		{
			edge[V+2*i].PB(V+2*(i+1));
			edge[V+2*(i+1)+1].PB(V+2*i+1);
		}
		for(int i=0; i<k-1; i++)
		{
			edge[vec[i]].PB(V+2*i);
			edge[V+2*i].PB(vec[i+1]^1);
			edge[vec[i+1]].PB(V+2*i+1);
			edge[V+2*i+1].PB(vec[i]^1);
		}

		V += 2*(k-1);
	}

	assert(V < MAXN);
	scc.init(V);
	for(int i=0; i<V; i++)
		for(auto c: edge[i])
			scc.add_edge(i, c);
	scc.solve();

	for(int i=0; i<N; i++)
	{
		if(hw[i] and scc.bln[2*i] == scc.bln[2*i+1])
		{
			cout<<"NO"<<endl;
			return;
		}
	}

	cout<<"YES"<<endl;
	for(int i=0; i<N; i++)
	{
		int good = (scc.bln[2*i+1] > scc.bln[2*i]);
		for(auto c: s[i])
			cout<<(c == '1' or (good and c == '?'));
		cout<<"\n";
	}
}

int32_t main() {
	FILEIO("binary");
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<MAXN; i++)
			edge[i].clear();
		for(int i=0; i<N; i++)
			cin>>s[i];

		calc();
	}

	return 0;
}

