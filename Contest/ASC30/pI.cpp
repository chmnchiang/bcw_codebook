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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

typedef pair<int, int> pii;

const int MAXN = 104;
const int INF = 1029384756;

int N;
string s1, s2;
int arr[MAXN];
map<char, int> mp;
int dp[MAXN][MAXN*2][MAXN];
pii prv[MAXN][MAXN*2][MAXN];

void update(int i, int j, int k, int c, pii p)
{
	if(dp[i][j][k] > c)
	{
		dp[i][j][k] = c;
		prv[i][j][k] = p;
	}
}

void solve()
{
	mp['A'] = 0;
	mp['C'] = 1;
	mp['G'] = 2;
	mp['T'] = 3;

	for(int i=0; i<N; i++)
		arr[i] = (mp[s2[i]] - mp[s1[i]] + 4) % 4;

	for(int i=0; i<=N; i++)
		for(int j=MAXN-N; j<=MAXN+N; j++)
			for(int k=0; k<=N; k++)
				dp[i][j][k] = INF;

	dp[0][MAXN][0] = 0;

	for(int i=0; i<N; i++)
	{
		for(int j=MAXN-N; j<=MAXN+N; j++)
			for(int k=0; k<=N; k++)
				dp[i+1][j][k] = dp[i][j][k], prv[i+1][j][k] = {j, k};

		for(int j=MAXN-N; j<=MAXN+N; j++)
			for(int k=0; k<N; k++)
				update(i+1, j, k+1, dp[i+1][j][k]+1, prv[i+1][j][k]);
		for(int j=MAXN-N; j<=MAXN+N; j++)
			for(int k=N; k>0; k--)
				update(i+1, j, k-1, dp[i+1][j][k], prv[i+1][j][k]);

		for(int k=0; k<=N; k++)
			for(int j=MAXN-N; j<MAXN+N; j++)
				update(i+1, j+1, k, dp[i+1][j][k] + (j>=MAXN), prv[i+1][j][k]);
		for(int k=0; k<=N; k++)
			for(int j=MAXN+N; j>MAXN-N; j--)
				update(i+1, j-1, k, dp[i+1][j][k] + (j<=MAXN), prv[i+1][j][k]);

		for(int j=-N; j<=N; j++)
		{
			for(int k=0; k<=N; k++)
			{
				int rem = ((j+2*k)%4 + 4) % 4;
				if(rem != arr[i])
					dp[i+1][MAXN+j][k] = INF;
			}
		}
	}

	int ans = INF, n1 = -1, n2 = -1;
	for(int i=MAXN-N; i<=MAXN+N; i++)
		for(int j=0; j<=N; j++)
			if(dp[N][i][j] < ans)
				ans = dp[N][i][j], n1 = i, n2 = j;

	vector<pii> ans1, ans2, ans3;
	vector<int> stk1, stk2, stk3;

	int c1 = MAXN, c2 = 0;
	for(int i=N; i>=0; i--)
	{
//		cout<<c1-MAXN<<" "<<c2<<" => "<<n1-MAXN<<" "<<n2<<endl;
		while(c2 < n2)
		{
			stk2.PB(i);
			c2++;
		}
		while(c2 > n2)
		{
			ans2.PB({i, stk2.back()});
			stk2.pop_back();
			c2--;
		}
		while(c1 < n1)
		{
			if(c1 >= MAXN)
				stk1.PB(i);
			else
			{
				ans3.PB({i, stk3.back()});
				stk3.pop_back();
			}
			c1++;
		}
		while(c1 > n1)
		{
			if(c1 <= MAXN)
				stk3.PB(i);
			else
			{
				ans1.PB({i, stk1.back()});
				stk1.pop_back();
			}
			c1--;
		}

		pii p = prv[i][n1][n2];
		n1 = p.F;
		n2 = p.S;
	}

//	for(int i=0; i<N; i++) cout<<arr[i];cout<<endl;

	cout<<ans<<endl;
	for(auto v: ans1) cout<<v.F+1<<" "<<v.S<<" 1"<<endl;
	for(auto v: ans2) cout<<v.F+1<<" "<<v.S<<" 2"<<endl;
	for(auto v: ans3) cout<<v.F+1<<" "<<v.S<<" 3"<<endl;
}

int main() {
	IOS;
	FILEIO("transform");

	cin>>s1>>s2;
	N = s1.size();

	solve();

    return 0;
}
