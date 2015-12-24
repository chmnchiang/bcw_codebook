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

const int MX = 32;
const int MOD = 239;

ll N;
int K;

struct Mat
{
	int v[MX][MX];
	Mat operator*(Mat m)
	{
		Mat ret;
		for(int i=0; i<=K; i++)
		{
			for(int j=0; j<=K; j++)
			{
				ret.v[i][j] = 0;
				for(int k=0; k<=K; k++)
					ret.v[i][j] += v[i][k] * m.v[k][j];
				ret.v[i][j] %= MOD;
			}
		}
		return ret;
	}

	void print()
	{
		for(int i=0; i<=K; i++)
		{
			for(int j=0; j<=K; j++)
				cout<<v[i][j]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
};

Mat A[MOD], As, I;

void make_mat()
{
	for(int i=0; i<=K; i++)
		for(int j=0; j<=K; j++)
			I.v[i][j] = (i == j);

	for(int n=0; n<MOD; n++)
	{
		for(int i=0; i<=K; i++)
			for(int j=0; j<=K; j++)
				A[n].v[i][j] = 0;
		for(int i=1; i<=K; i++)
		{
			A[n].v[i][i] = (2 * i) % MOD;
			A[n].v[i][i-1] = (n+3 - 2 * i + MOD) % MOD;
		}
	}

	As = I;
	for(int i=0; i<MOD; i++)
		As = A[i] * As;
}

Mat pow(Mat a, ll p)
{
	Mat ret = I, cur = a;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur;
		cur = cur * cur;
		p >>= 1;
	}
	return ret;
}

int calc()
{
	make_mat();

	Mat cur = pow(As, N / MOD);
	int res = N % MOD;
	for(int i=0; i<res; i++)
		cur = A[i] * cur;

	int ans = cur.v[K][0] % MOD;
	return ans;
}

int main() {
	IOS;
	FILEIO("peaks");

	cin>>N>>K;
	int ans = calc();
	cout<<ans<<endl;

    return 0;
}
