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

const int MAXN = 105;
const double INF = 1e20;

int N;
int B1, B2;
pii pt[MAXN];
double dp[MAXN][MAXN];
double dis[MAXN][MAXN];
pii prv[MAXN][MAXN];
vector<int> vans;

double calc()
{
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			dp[i][j] = INF;
	dp[0][0] = 0;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			int dx = pt[i].F - pt[j].F;
			int dy = pt[i].S - pt[j].S;
			dis[i][j] = sqrt(dx * dx + dy * dy);
		}
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
//			cout<<i<<","<<j<<" = "<<dp[i][j]<<endl;
			if(dp[i][j] == INF) continue;
			if(i == N-1 && j == N-1) continue;
			int nxt = max(i, j) + 1;
			if(nxt == N)
				nxt = N-1;
			if(nxt > i && nxt != B2 && dp[nxt][j] > dp[i][j] + dis[i][nxt])
			{
//				cout<<pii(i, j)<<" => "<<pii(nxt, j)<<endl;
				dp[nxt][j] = dp[i][j] + dis[i][nxt];
				prv[nxt][j] = {i, j};
			}
			if(nxt > j && nxt != B1 && dp[i][nxt] > dp[i][j] + dis[j][nxt])
			{
//				cout<<pii(i, j)<<" => "<<pii(i, nxt)<<endl;
				dp[i][nxt] = dp[i][j] + dis[j][nxt];
				prv[i][nxt] = {i, j};
			}
		}
	}

	double ans = dp[N-1][N-1];


	vector<int> v1, v2;
	v1.PB(N-1);
	v2.PB(N-1);
	int x = N-1, y = N-1;
	while(x != 0 || y != 0)
	{
		pii p = prv[x][y];
		tie(x, y) = p;
		if(x != v1.back())
			v1.PB(x);
		if(y != v2.back())
			v2.PB(y);
	}

	reverse(ALL(v1));
	v1.pop_back();

	vans = v1;
	vans.insert(vans.end(), ALL(v2));
	if(vans[1] != 1)
		reverse(ALL(vans));

	return ans;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N>>B1>>B2 && N)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		double ans = calc();
		cout<<"Case "<<t<<": "<<fixed<<setprecision(2)<<ans<<endl;
		for(int i=0; i<=N; i++)
			cout<<vans[i]<<(i==N ? "\n" : " ");
	}

	return 0;
}

