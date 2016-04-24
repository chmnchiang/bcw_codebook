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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

typedef pair<int, int> pii;

const int MAXN = 303;
const int MXN = MAXN;
const double INF = 1E20;
const double HHHHH = 10000;
const double EPS = 1E-8;

double getdis(pii a, pii b)
{
	int dx = a.F - b.F, dy = a.S - b.S;
	return sqrt(dx*dx + dy*dy);
}

int N;
pii ps[MAXN], pt[MAXN];

struct KM{
// Maximum Bipartite Weighted Matching (Perfect Match)
	int n,match[MXN],vx[MXN],vy[MXN];
	double edge[MXN][MXN],lx[MXN],ly[MXN],slack[MXN];
	// ^^^^ long long
	void init(int _n){
		n = _n;
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				edge[i][j] = 0;
	}
	void add_edge(int x, int y, double w){ // long long
		edge[x][y] = w;
	}
	bool DFS(int x){
		vx[x] = 1;
		for (int y=0; y<n; y++){
			if (vy[y]) continue;
			if (lx[x]+ly[y] > edge[x][y] + EPS){
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
	double solve(){
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
				double d = INF; // long long
				for (int j=0; j<n; j++)
					if (!vy[j]) d = min(d, slack[j]);
				for (int j=0; j<n; j++){
					if (vx[j]) lx[j] -= d;
					if (vy[j]) ly[j] += d;
					else slack[j] -= d;
				}
			}
		}
		double res=0;
		for (int i=0; i<n; i++)
			res += edge[match[i]][i];
		return res;
	}
}graph;

double calc()
{
	double ans = 0;

	for(int i=0; i<N; i++)
		ans += getdis(ps[i], pt[i]);

	graph.init(N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			graph.add_edge(i, j, -getdis(ps[i], pt[j]) + HHHHH);

	double res = graph.solve() - HHHHH * N;
	ans -= res;

	return ans;
}

int main() {
	IOS;

	cin>>N;
	pii trash;
	cin>>trash.F>>trash.S;
	for(int i=0; i<N; i++)
		cin>>ps[i].F>>ps[i].S>>pt[i].F>>pt[i].S;

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}

