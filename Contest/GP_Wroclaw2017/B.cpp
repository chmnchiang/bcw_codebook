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

const int MAXN = 333;

struct Isap{
  static const int MXN = 10000;
  static const int INF = 2147483647;
  struct Edge{ int v,f,re; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,SZ(E[v])});
    E[v].PB({u,f,SZ(E[u])-1});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (nf){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  int flow(int res=0){
    for (int i=0; i<n; i++) h[i] = gap[i] = 0;
    gap[0] = n;
    while (h[s] < n) res += DFS(s,INF);
    return res;
  }
}flow;

int N, M;
pii ed[MAXN*MAXN];
int ec[MAXN*MAXN];
int S1, T1, S2, T2;

int calc(int s1, int s2, int t1, int t2)
{
	int V = N+2;
	int S = 0, T = N+1;

	flow.init(V, S, T);
	flow.add_edge(S, s1, 5E8);
	flow.add_edge(S, s2, 5E8);
	flow.add_edge(T, t1, 5E8);
	flow.add_edge(T, t2, 5E8);
	
	for(int i=0; i<M; i++)
		flow.add_edge(ed[i].F, ed[i].S, ec[i]);

	int f = flow.flow();
//	cout<<"F = "<<f<<endl;
	return f;
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>M;
		for(int i=0; i<M; i++)
			cin>>ed[i].F>>ed[i].S>>ec[i];
		cin>>S1>>T1>>S2>>T2;

		int ans = min(calc(S1, S2, T1, T2), calc(S1, T2, T1, S2));
		cout<<ans<<endl;
	}

	return 0;
}

