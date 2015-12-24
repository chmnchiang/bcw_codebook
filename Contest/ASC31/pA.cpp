/* bcw0x1bd2 */
#include <bits/stdc++.h>
//
using namespace std;
//
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)-1);(i)>=0;(i)--)
#define CDFOR(s,e,i) for(int i=((e)-1);(i)>=(s);(i)--)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),-1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP make_pair
#define _PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
// Let's Fight!

const int MAXN = 64;

int N, M, S;
double p[MAXN];
int w[MAXN];

double dp[MAXN];

inline double getdp(int x)
{
	if(x>N)return 1;
	return dp[x];
}

int main(int argc, char** argv)
{
	freopen("casino.in", "r", stdin);
	freopen("casino.out", "w", stdout);

	cin>>N>>M>>S;
	for(int i=0; i<M; i++)
	{
		cin>>p[i]>>w[i];
		p[i] /= S;
	}

	for(int i=0; i<2000; i++)
	{
		//for(int j=0; j<=N+1; j++)cout<<getdp(j)<<" ";cout<<endl;
		for(int j=1; j<=N; j++)
		{
			for(int k=0; k<M; k++)
			{
				double res = p[k] * getdp(j+w[k]) + (1-p[k]) * dp[j-1];
				dp[j] = max(dp[j], res);
			}
		}
	}

	printf("%.15f\n", dp[N]);



	return 0;
}
