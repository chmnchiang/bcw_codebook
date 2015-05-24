//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

const int MAXN = 5050;
const int MOD = 1000000009;

int N, K;

int arr[MAXN][MAXN];

int main(){
	IOS;
	FILEIO("comb");

	while(cin>>K>>N && N)
	{
		for(int i=0; i<=N; i++)
		{
			for(int j=0; j<=N; j++)
			{
				if(i < j || i > j + K - 2)
					continue;
				if(j == 0)
					arr[i][j] = 1;
				else
					arr[i][j] = (arr[i-1][j] + arr[i][j-1]) % MOD;
			}
		}

		for(int i=0; i<N; i++)
			cout<<arr[i][i]<<endl;
		break;
	}

	return 0;
}
