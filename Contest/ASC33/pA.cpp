#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!

const int MAXN = 1010;

int N;
int arr[MAXN][MAXN];
int edge[MAXN][MAXN];

bitset<MAXN> b1[MAXN], b2[MAXN];

int main(){
	FILEIO("avia");
	srand(time(0));

	IOS
	cin>>N;
	for(int i=0; i<N; i++)
	{
		string s;
		cin>>s;
		for(int j=0; j<N; j++)
		{
			arr[i][j] = (s[j] == '+');
		}
	}

	while(1)
	{
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<i; j++)
			{
				if(arr[i][j])
				{
					edge[i][j] = rand()%2 + 1;
					edge[j][i] = edge[i][j];
				}
			}
		}

		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				b1[i][j] = (edge[i][j] == 1);
				b2[i][j] = (edge[i][j] == 2);
			}
		}

		bool ok = true;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<i; j++)
			{
				if(edge[i][j] > 0)continue;
				if(!(b1[i]&b2[j]).any() && !(b1[j]&b2[i]).any())
				{
					ok = false;
					break;
				}
			}
			if(!ok)break;
		}
		if(ok)
		{
			for(int i=0; i<N; i++)
			{
				for(int j=0; j<N; j++)
				{
					printf("%c", edge[i][j] ? ('0'+edge[i][j]) : '-');
				}
				puts("");
			}
			break;
		}
	}

	return 0;
}
