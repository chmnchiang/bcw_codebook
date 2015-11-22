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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

const int MAXN = 42;

int N;
int arr[MAXN], brr[MAXN];

int guess()
{
	for(int i=0; i<N; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
	int res;
	cin>>res;
	if(res == N)
		exit(0);
	return res;
}

void backup()
{
	for(int i=0; i<N; i++)
		brr[i] = arr[i];
}

void move(int a, int b)
{
	while(b > a)
	{
		swap(arr[b], arr[b-1]);
		b--;
	}
}

void restore()
{
	for(int i=0; i<N; i++)
		arr[i] = brr[i];
}

int main() {
	srand(time(0));
	cin>>N;

	for(int i=0; i<N; i++)
		arr[i] = i+1;
	random_shuffle(arr, arr+N);

	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			backup();
			swap(arr[j], arr[N-1]);
			int base = guess();
			move(i, N-1);
			int nw = guess();
			if(nw > base)
			{
				j=i+1;
				random_shuffle(arr+j+1, arr+N);
			}
			else restore();
		}
	}
	guess();
	assert(false);

    return 0;
}
