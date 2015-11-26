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

const int MAXN = 514;
const int MAXR = 30;
const ll MOD = 1000000007;

int N;
ll f[MAXR][MAXR];
ll part[MAXR];
ll partconv[MAXR];
ll tmp[MAXR];

void pre()
{
	for(int i=0; i<MAXR; i++)
		f[0][i] = 1;
	for(int i=1; i<MAXR; i++)
	{
		f[i][0] = 0;
		for(int j=1; j<MAXR; j++)
		{
			f[i][j] = f[i][j-1];
			if(i-j >= 0) f[i][j] = (f[i][j] + f[i-j][j]) % MOD;
		}
	}
	for(int i=0; i<MAXR; i++)
		part[i] = f[i][i];
	
	partconv[0] = 1;

	for(int i=0; i<4; i++)
	{
		FZ(tmp);
		for(int j=0; j<MAXR; j++)
		{
			for(int k=0; k<=j; k++)
				tmp[j] = (tmp[j] + part[k] * partconv[j-k]) % MOD;
		}
		for(int j=0; j<MAXR; j++)
			partconv[j] = tmp[j];
	}
}

int main() {
    FILEIO("expedition");
	pre();
	IOS;
	cin>>N;

	ll ans = 0;
	ll best = 1<<20;

	for(int i=1; i<=N; i++)
	{
		int j = (N+i-1)/i;
		int rem = i*j-N;
		int len = 2*(i+j);
		ll num = partconv[rem];

		if(len < best)
		{
			best = len;
			ans = 0;
		}
		if(len == best)
		{
			ans = (ans + num) % MOD;
		}
	}

	cout<<ans<<endl;

    return 0;
}

