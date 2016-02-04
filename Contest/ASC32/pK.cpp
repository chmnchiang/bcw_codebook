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
// Let's Fight!


typedef long long ll;

const int MAXN = 52;
const int BIT = 64;

bool canuse[MAXN][BIT], use[MAXN][BIT];

int N, B;
ll arr[MAXN], brr[MAXN];
int num[MAXN];
ll dp[MAXN][BIT], prv[MAXN][BIT];

bool calc()
{
	for(int i=0; i<N; i++)
		num[i] = __builtin_popcountll(arr[i]);

	B = 0;
	for(int i=0; i<N; i++)
	{
		int l = 0;
		ll x = arr[i];
		while(x)
		{
			l++;
			x >>= 1;
		}
		B = max(B, l);
	}

	for(int i=0; i<=N; i++)
		for(int j=0; j<=B; j++)
			dp[i][j] = -1;
	dp[0][0] = 0;

	for(int i=0; i<N; i++)
	{
		int n = num[i];
		for(int j=0; j<=B; j++)
		{
			if(dp[i][j] == -1) continue;

			vector<int> vo, vz;
			for(int k=0; k<B; k++)
			{
				if(dp[i][j] & (1LL<<k)) vo.PB(k);
				else vz.PB(k);
			}
			for(int k=0; k<=n; k++)
			{
				if(k > j || n-k > B-j) continue;
				ll res = 0;
				for(int l=0; l<k; l++)
					res |= (1LL << vo[l]);
				for(int l=0; l<n-k; l++)
					res |= (1LL << vz[l]);
				ll nxt = dp[i][j] ^ res;
				int np = __builtin_popcountll(nxt);
				dp[i+1][np] = nxt;
				prv[i+1][np] = res;
			}
		}
	}

	if(dp[N][0] == -1) return false;

	int curj = 0;
	ll curx = 0;
	for(int i=N; i>=1; i--)
	{
		brr[i-1] = prv[i][curj];
		curx ^= brr[i-1];
		curj = __builtin_popcountll(curx);
	}

	return true;
}

int main() {
	IOS;
	FILEIO("xor");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	bool res = calc();
	if(!res)
	{
		cout<<"impossible"<<endl;
	}
	else
	{
		for(int i=0; i<N; i++)
			cout<<brr[i]<<(i==N-1 ? "\n" : " ");
	}

    return 0;
}

