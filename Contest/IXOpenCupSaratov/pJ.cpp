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
    freopen(name".in", "r", stdin);
//    freopen(name".out", "w", stdout);
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

typedef pair<int, string> psi;
typedef pair<int, int> pii;

const int MAXN = 2020;
const int INF = 1029384756;

int N, M;
psi boy[MAXN], girl[MAXN];
int dp[MAXN][MAXN];
pii prv[MAXN][MAXN];

void calc()
{
	sort(boy, boy+N);
	sort(girl, girl+M);

	for(int i=0; i<=N; i++)
		for(int j=0; j<=M; j++)
			dp[i][j] = INF;

	dp[0][0] = 0;
	for(int i=0; i<=N; i++)
	{
		for(int j=0; j<=M; j++)
		{
			for(int x=1; x<=4; x++)
			{
				if(i+x>N) break;
				for(int y=0; y<=4; y++)
				{
					if(j+y>M) break;
					if(x+y>4) break;

					int ncost = boy[i+x-1].F;
					if(y>0) ncost = max(ncost, girl[j+y-1].F);
					int zcost = ncost + dp[i][j];
					int ni = i + x, nj = j + y;
					if(zcost < dp[ni][nj])
					{
//						cout<<i<<","<<j<<" => "<<ni<<","<<nj<<" COST "<<ncost<<" + "<<dp[i][j]<<" = "<<zcost<<endl;
						dp[ni][nj] = zcost;
						prv[ni][nj] = {i, j};
					}
				}
			}
		}
	}

	int ans = dp[N][M];

	vector<vector<string>> vvs;

	int cx = N, cy = M;
	while(cx > 0 || cy > 0)
	{
		vector<string> vs;
		int nx = prv[cx][cy].F, ny = prv[cx][cy].S;
		for(int i=nx; i<cx; i++)
			vs.PB(boy[i].S);
		for(int i=ny; i<cy; i++)
			vs.PB(girl[i].S);
		vvs.PB(vs);
		cx = nx;
		cy = ny;
	}

	cout<<ans<<endl;
	int V = vvs.size();
	cout<<V<<endl;
	for(int i=0; i<V; i++)
	{
		int Z = vvs[i].size();
		cout<<"Taxi "<<i+1<<": ";
		for(int j=0; j<Z; j++)
		{
			cout<<vvs[i][j];
			if(j == Z-1)
				cout<<"."<<endl;
			else if(j == Z-2)
				cout<<" and ";
			else
				cout<<", ";
		}
	}
}

int main() {
	IOS;
	FILEIO("taxi");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>boy[i].S>>boy[i].F;
	cin>>M;
	for(int i=0; i<M; i++)
		cin>>girl[i].S>>girl[i].F;

	calc();


	return 0;
}

