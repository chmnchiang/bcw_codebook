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

typedef pair<int, double> pid;
typedef pair<double, int> pdi;

const int MAXN = 404;
const double INF = 1e20;

int N, M;
int px[MAXN], py[MAXN], pz[MAXN], k[MAXN];
int edge[MAXN][MAXN];
double dis[MAXN][MAXN];
bool canuse[MAXN];

int root[MAXN];
double cost[MAXN];
vector<int> vch[MAXN];

double sdis[MAXN*2];
vector<pid> sedge[MAXN*2]; 

double gdis(int a, int b)
{
	double dx = px[a] - px[b];
	double dy = py[a] - py[b];
	double dz = pz[a] - pz[b];
	return sqrt(dx*dx+dy*dy+dz*dz);
}

void djInit()
{
	for(int i=0; i<N; i++)
	{
		root[i] = i;
		cost[i] = k[i] * 0.5;
	}
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
	cost[pv] += cost[pu];
	return true;
}

double calc2(int thres)
{
	if(pz[N-1] > thres || pz[0] > thres) return INF;

	for(int i=0; i<N; i++)
		canuse[i] = (pz[i] <= thres);

	djInit();

	for(int i=0; i<N; i++)
	{
		if(!canuse[i]) continue;
		for(int j=0; j<N; j++)
		{
			if(!canuse[j]) continue;
			if(edge[i][j])
				djUnion(i, j);
		}
	}

	for(int i=0; i<N; i++)
		vch[i].clear();
	for(int i=0; i<N; i++)
		if(canuse[i])
			vch[djFind(i)].PB(i);

	for(int i=0; i<2*N; i++)
	{
		sdis[i] = INF;
		sedge[i].clear();
	}

	for(int i=0; i<N; i++)
	{
		if(!canuse[i]) continue;
		if(root[i] != i) continue;
		for(auto v: vch[i])
		{
			if(k[v] == 0) continue;
			for(auto u: vch[i])
			{
				if(u != v || k[v] >= 2)
					sedge[v].PB({N+u, 0});
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		if(!canuse[i] || root[i] != i) continue;
		for(int j=0; j<N; j++)
		{
			if(!canuse[j] || root[j] != j) continue;
			if(i == j) continue;
			for(auto v: vch[i])
			{
				for(auto u: vch[j])
				{
					if(k[v] > 0 && k[u] > 0)
					{
						sedge[N+v].PB({u, dis[v][u] + cost[j]});
					}
				}
			}
		}
	}

	priority_queue<pdi, vector<pdi>, greater<pdi> > pq;

	int SS = djFind(0), TT = djFind(N-1);
	double cc = cost[SS];
	for(auto v: vch[SS])
	{
		sdis[v] = cc;
		sdis[N+v] = cc;
		pq.push({cc, v});
		pq.push({cc, N+v});
	}

	while(!pq.empty())
	{
		pdi p = pq.top();
		pq.pop();
		double c = p.F;
		int v = p.S;
		if(c != sdis[v]) continue;

		for(auto e: sedge[v])
		{
			double nc = c + e.S;
			if(sdis[e.F] > nc)
			{
				sdis[e.F] = nc;
				pq.push({nc, e.F});
			}
		}
	}

	double ans = INF;
	
	for(auto v: vch[TT])
	{
		ans = min(ans, sdis[v]);
	}

	return ans;
}

double calc()
{
	double ans = INF;
	for(int i=0; i<N; i++)
		ans = min(ans, calc2(pz[i]));
	return ans;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N>>M)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>px[i]>>py[i]>>pz[i]>>k[i];
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				edge[i][j] = 0;
				dis[i][j] = gdis(i, j) - 1;
			}
		}
		for(int i=0; i<M; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			edge[a][b] = edge[b][a] = 1;
		}

		double ans = calc();
		cout<<"Case "<<t<<": ";
		if(ans == INF) cout<<"impossible"<<endl;
		else cout<<fixed<<setprecision(4)<<ans<<endl;
	}


	return 0;
}

