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

const int MAXN = 1010;

int N, K;
int arr[MAXN];
bool on[MAXN];
int ans;

void init()
{
	ans = 0;
}

int main() {
	IOS;
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>K;
		init();
		for(int i=0; i<K; i++)
			cin>>arr[i];
		sort(arr, arr+K);
		int SZ = 0;
		while(SZ < K && arr[SZ] <= 29) SZ++;
		for(int i=0; i<(1<<SZ); i++)
		{
			for(int j=1; j<=N; j++)
				on[j] = false;
			for(int j=0; j<SZ; j++)
			{
				if(i&(1<<j))
				{
					int x = arr[j];
					for(int k=x; k<=N; k+=x)
						on[k] = !on[k];
				}
			}
			int curans = 0;
			for(int j=1; j<=N; j++)
				if(on[j])
					curans++;
			for(int j=SZ; j<K; j++)
			{
				int gc = 0, bc = 0;
				int x = arr[j];
				for(int k=x; k<=N; k+=x)
				{
					if(on[k]) bc++;
					else gc++;
				}
				if(gc > bc)
					curans += gc - bc;
			}
			ans = max(ans, curans);
		}

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

    return 0;
}


