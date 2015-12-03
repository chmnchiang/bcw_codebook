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

typedef long long ll;

const int MAXN = 101010;
const int MAXM = 514;
const ll INF = 1LL<<50;

int N;
int arr[MAXN];
ll dp[MAXN][MAXM];

int toint(char c)
{
	if(c >= '0' && c <= '9') return c-'0';
	return c-'A'+10;
}

int main() {
	IOS;
	cin>>N;
	for(int i=0; i<N; i++)
	{
		string s;
		cin>>s;
		arr[i] = toint(s[0]) * 16 + toint(s[1]);
	}

	for(int i=0; i<=N; i++)
		for(int j=0; j<MAXM; j++)
			dp[i][j] = -INF;
	dp[0][0] = 0;

	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<MAXM; j++)
		{
			if(j>0) dp[i][j] = dp[i-1][j-1];
			if(i-1-j>=0) dp[i][j] = max(dp[i][j], dp[i-1][j] + ((i-1-j)^arr[i-1]));
		}
	}

	ll ans = 0;
	for(int i=0; i<MAXM; i++)
		ans = max(ans, dp[N][i]);

	cout<<ans<<endl;

    return 0;
}

