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
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

const int MAXN = 2120;
const int INF = 1029384756;

struct Edge
{
	int u, v, c, id;
};

int NT, NI, N;

int tprice[MAXN];
int tlen[MAXN], ilen;
vector<int> tpath[MAXN], ipath;
vector<int> vans;
int dp[MAXN];
int prv[MAXN], pno[MAXN];
vector<Edge> edge;
vector<int> disc;

int calc()
{
	vans.clear();
	edge.clear();
	int V = N * ilen;

	for(int i=0; i<V; i++)
	{
		dp[i] = INF;
		prv[i] = -1;
		pno[i] = -1;
	}

	for(int i=0; i<ilen; i++)
	{
		for(int k=0; k<NT; k++)
		{
			int s = tpath[k][0];
			int curpos = i; 
			int p = tprice[k];
			for(int l=1; l<tlen[k]; l++)
			{
				int v = tpath[k][l];
				if(curpos<ilen-1 && ipath[curpos+1] == v)
					curpos++;
				edge.PB({i*N+s, curpos*N+v, p, k+1});
			}
		}
	}
	
	int start = ipath[0], ends = ipath.back();
	dp[start] = 0;

	for(int i=0; i<=V; i++)
	{
		for(auto e: edge)
		{
			int nc = dp[e.u] + e.c;
			if(nc < dp[e.v])
			{
				dp[e.v] = nc;
				prv[e.v] = e.u;
				pno[e.v] = e.id;
			}
		}
	}

	int ans = dp[(ilen-1)*N+ends];
	if(ans == INF) while(1);

	int cur = (ilen-1)*N+ends;
	while(cur != start)
	{
		vans.PB(pno[cur]);
		cur = prv[cur];
	}

	reverse(ALL(vans));

	return ans;
}

int main() {
	IOS;
	increase_stack_size();

	for(int t=1;; t++)
	{
		cin>>NT;
		if(NT == 0) break;
		for(int i=0; i<NT; i++)
		{
			cin>>tprice[i];
			cin>>tlen[i];
			tpath[i].clear();
			for(int j=0; j<tlen[i]; j++)
			{
				int x;
				cin>>x;
				tpath[i].PB(x);
			}
		}

		disc.clear();
		for(int i=0; i<NT; i++)
			for(int j=0; j<tlen[i]; j++)
				disc.PB(tpath[i][j]);
		sort(ALL(disc));
		N = unique(ALL(disc)) - disc.begin();
		disc.resize(N);
		if(N >= MAXN) while(1);

		for(int i=0; i<NT; i++)
			for(int j=0; j<tlen[i]; j++)
				tpath[i][j] = lower_bound(ALL(disc), tpath[i][j]) - disc.begin();

		cin>>NI;
		for(int i=0; i<NI; i++)
		{
			cin>>ilen;
			ipath.clear();
			for(int j=0; j<ilen; j++)
			{
				int x;
				cin>>x;
				x = lower_bound(ALL(disc), x) - disc.begin();
				ipath.PB(x);
			}

			int ans = calc();
			cout<<"Case "<<t<<", Trip "<<i+1<<": Cost = "<<ans<<endl;
			cout<<"  Tickets used:";
			for(auto v: vans)
				cout<<" "<<v;
			cout<<endl;
		}
	}

    return 0;
}

