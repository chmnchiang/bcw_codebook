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

typedef unsigned long long ll;

const int MAXN = 101010;

int N;
ll K;
int arr[MAXN];

int main(){
	IOS;
	FILEIO("bubble");

	while(cin>>N>>K && N && K)
	{
		K--;
		for(int i=0; i<N; i++)
			arr[i] = i+1;
		vector<int> vec;
		for(int i=0; i<N-1; i++)
		{
			int j = N-i-2;
			if(j >= 64) continue;
			if(K & (1LL<<j))
			{
				vec.PB(i);
				K ^= (1LL<<j);
			}
		}
		reverse(vec.begin(), vec.end());
		for(auto it: vec)
			swap(arr[it], arr[it+1]);
		for(int i=0; i<N; i++)
			cout<<arr[i]<<(i==N-1 ? "\n" : " ");
	}

	return 0;
}

