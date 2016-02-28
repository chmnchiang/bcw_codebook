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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef pair<int, int> pii;
typedef pair<int, double> pid;

const int MAXN = 1010;
const double EPS = 1E-8;
const double INF = 1E20;

int N, X, Y, V;
pii pt[MAXN], qt[MAXN];
vector<double> vx, vy;
int lb[MAXN], rb[MAXN];
vector<pii> vpt;
vector<pid> edge[MAXN];
double dis[MAXN];

void check_edge(int a, int b)
{
	pii pa = vpt[a], pb = vpt[b];
	if(pa.S != pb.S)
	{
		if(pa.S > pb.S) swap(pa, pb);
//		cout<<pa<<" "<<pb<<endl;
		double dx = pb.F - pa.F, dy = pb.S - pa.S;
		double rat = dx / dy;

		for(int i=0; i<Y-1; i++)
		{
			int low = vy[i], hi = vy[i+1];
			if(hi <= pa.S || low >= pb.S) continue;
			double lx = pa.F + rat * (low - pa.S);
			double hx = pa.F + rat * (hi - pa.S);
//			cout<<low<<"~"<<hi<<" LX "<<lx<<" HX "<<hx<<endl;
			if(lx < vx[lb[i]] - EPS || lx > vx[rb[i]] + EPS) return;
			if(hx < vx[lb[i]] - EPS || hx > vx[rb[i]] + EPS) return;
		}
//		cout<<"OK"<<endl;
	}

	double dx = pa.F - pb.F, dy = pa.S - pb.S;
	double di = sqrtl(dx * dx + dy * dy);
	edge[a].PB({b, di});
	edge[b].PB({a, di});

//	cout<<pa<<" "<<pb<<" "<<di<<endl;
}

double calc()
{
	for(int i=0; i<N; i++)
	{
		vx.PB(pt[i].F);
		vy.PB(pt[i].S);
	}
	sort(ALL(vx));
	sort(ALL(vy));
	X = unique(ALL(vx)) - vx.begin();
	Y = unique(ALL(vy)) - vy.begin();
	vx.resize(X);
	vy.resize(Y);

	for(int i=0; i<N; i++)
	{
		qt[i].F = lower_bound(ALL(vx), pt[i].F) - vx.begin();
		qt[i].S = lower_bound(ALL(vy), pt[i].S) - vy.begin();
	}

	for(int i=0; i<N; i++)
	{
		pii p1 = qt[i], p2 = qt[(i+1)%N];
		if(p1.S == p2.S) continue;
		if(p1.S < p2.S)
		{
			for(int j=p1.S; j<p2.S; j++)
				rb[j] = p1.F;
		}
		else
		{
			for(int j=p2.S; j<p1.S; j++)
				lb[j] = p1.F;
		}
	}

	int top = 1;
	while(top < Y-1 && lb[top] <= lb[top-1] && rb[top] >= rb[top-1])
		top++;
	int bot = Y-2;
	while(bot > 0 && lb[bot-1] <= lb[bot] && rb[bot-1] >= rb[bot])
		bot--;

	int tl = lb[0], tr = rb[0], bl = lb[Y-2], br = rb[Y-2];

//	cout<<"TOP "<<top<<" BOT "<<bot<<endl;
//	cout<<tl<<" "<<tr<<" "<<bl<<" "<<br<<endl;

	if(top >= bot)
	{
		if(max(tl, bl) <= min(tr, br))
			return 0;
		double di = min(abs(vx[tl] - vx[br]), abs(vx[tr] - vx[bl]));
		return 2 * di;
	}

	vector<int> vt, vb;
	for(int i=0; i<N; i++)
		vpt.PB(pt[i]);
	for(int i=tl; i<=tr; i++)
	{
		vt.PB(vpt.size());
		vpt.PB({vx[i], vy[top]});
	}
	for(int i=bl; i<=br; i++)
	{
		vb.PB(vpt.size());
		vpt.PB({vx[i], vy[bot]});
	}

	V = vpt.size();

	for(int i=0; i<V; i++)
		for(int j=i+1; j<V; j++)
			check_edge(i, j);

	for(int i=0; i<V; i++)
		dis[i] = INF;

	for(auto v: vt)
		dis[v] = 0;
	
	for(int i=0; i<=V; i++)
	{
		for(int j=0; j<V; j++)
		{
			if(dis[j] == INF) continue;
			for(auto p: edge[j])
			{
				int u = p.F;
				double c = p.S;
				dis[u] = min(dis[u], dis[j] + c);
			}
		}
	}

	double ans = INF;
	for(auto v: vb)
		ans = min(ans, dis[v]);

//	for(auto v: vt) cout<<vpt[v]<<" ";cout<<endl;
//	for(auto v: vb) cout<<vpt[v]<<" ";cout<<endl;

	return 2 * ans;
}

int main() {
	IOS;
	FILEIO("nightwatch");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	double ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}
