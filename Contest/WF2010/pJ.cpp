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

const int MAXN = 102;
const int MAXS = 1<<15;

int N, X, Y;
int arr[MAXN];
vector<int> dp[MAXN][MAXN];

bool calc()
{
	for(int i=1; i<=X; i++)
		for(int j=1; j<=Y; j++)
			dp[i][j].clear();

	for(int i=0; i<N; i++)
		for(int j=1; j<=X; j++)
			for(int k=1; k<=Y; k++)
				if(j * k == arr[i])
					dp[j][k].PB(1<<i);

	for(int i=1; i<=X; i++)
	{
		for(int j=1; j<=Y; j++)
		{
			for(int k=1; k<=i-1; k++)
			{
				for(auto a: dp[k][j])
					for(auto b: dp[i-k][j])
						if((a&b) == 0)
							dp[i][j].PB(a|b);
			}
			for(int k=1; k<=j-1; k++)
			{
				for(auto a: dp[i][k])
					for(auto b: dp[i][j-k])
						if((a&b) == 0)
							dp[i][j].PB(a|b);
			}
			sort(ALL(dp[i][j]));
			dp[i][j].resize(unique(ALL(dp[i][j])) - dp[i][j].begin());
		}
	}

	for(auto v: dp[X][Y])
		if(v == (1<<N)-1)
			return true;
	return false;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N>>X>>Y && N)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>arr[i];

		bool res = calc();
		cout<<"Case "<<t<<": "<<(res ? "Yes" : "No")<<endl;
	}

	return 0;
}

