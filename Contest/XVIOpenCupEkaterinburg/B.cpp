#pragma GCC optimize ("O2")
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

const int MAXN = 1010;

int N;
int arr[MAXN];

int main() {
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<N; i++)
			cin>>arr[i];
		sort(arr, arr+N);
		N = unique(arr, arr+N) - arr;

		for(int i=1; ; i++)
		{
			bool ok = true;
			for(int j=0; j<N; j++)
			{
				if(arr[j] % i == 0)
				{
					ok = false;
					break;
				}
			}

			if(ok)
			{
				cout<<i<<endl;
				break;
			}
		}
	}

	return 0;
}

