#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef pair<int, int> pii;

const int MAXN = 101;
const int MOD = 997;

int N, M, K, S;
int comb[MOD][MOD];
pii pt[MAXN];
int death[MAXN];

void make_comb()
{
	comb[0][0] = 1;
	for(int i=1; i<MOD; i++)
	{
		comb[i][0] = 1;
		for(int j=1; j<=i; j++)
			comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
	}
}

int cob(int a, int b)
{
	int res = 1;
	int c = a+b;
	while(c | b)
	{
		res *= comb[c%MOD][b%MOD];
		res %= MOD;
		c /= MOD;
		b /= MOD;
	}
	return res;
}

int main() {
	make_comb();
	IOS;
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M>>K;
		S = 0;
		for(int i=0; i<K; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			for(int x=a-1; x<=a+1; x++)
				for(int y=b-1; y<=b+1; y++)
					pt[S++] = {x, y};
		}
		sort(pt, pt+S);

		for(int i=0; i<S; i++)
		{
			int x = pt[i].F, y = pt[i].S;
			int cb = cob(x, y);
			for(int j=0; j<i; j++)
			{
				int xx = pt[j].F, yy = pt[j].S;
				if(xx <= x && yy <= y)
				{
					cb -= death[j] * cob(x-xx, y-yy);
				}
			}
			cb %= MOD;
			if(cb < 0) cb += MOD;
			death[i] = cb;
		}

		int ans = cob(N-1, M-1);
		for(int i=0; i<S; i++)
			ans -= death[i] * cob(N-1-pt[i].F, M-1-pt[i].S);
		ans %= MOD;
		if(ans < 0) ans += MOD;

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

    return 0;
}

