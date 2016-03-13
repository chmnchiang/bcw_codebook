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

typedef long long ll;

const int B = 100;
const ll MOD = 1000000009;

struct Mat
{
	ll v[B][B];

	Mat()
	{
		FZ(v);
	}
	
	Mat operator*(Mat b)
	{
		Mat res;
		for(int i=0; i<B; i++)
			for(int j=0; j<B; j++)
				for(int k=0; k<B; k++)
					res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j]) % MOD;

		return res;
	}
};

ll N;
int M;
ll c[11];
ll trans[B][B];

Mat A, I;

void make_trans()
{
	for(int i=0; i<=9; i++)
	{
		for(int j=0; j<=9; j++)
		{
			int n = i*10+j;
			n = 99-n;
			if(i==j && i<9)
			{
				int nn = (i+1)*10+(j+1);
				nn = 99-nn;
				trans[nn][n] += c[2];
				trans[nn][n] %= MOD;
			}
			if(i<=j)
			{
				for(int k=1; i+k<=9; k++)
				{
					int nn = (i+k)*10+j;
					nn = 99-nn;
					trans[nn][n] += c[k];
					trans[nn][n] %= MOD;
				}
			}
			else
			{
				for(int k=1; j+k<=9; k++)
				{
					int nn = i*10+(j+k);
					nn = 99-nn;
					trans[nn][n] += c[k];
					trans[nn][n] %= MOD;
				}
			}
		}
	}

//	for(int i=0; i<B; i++) for(int j=0; j<B; j++) if(trans[i][j]) cout<<j<<" => "<<i<<" : "<<trans[i][j]<<endl;
}

void make_mat()
{
	for(int i=0; i<B; i++)
		I.v[i][i] = 1;

	for(int i=9; i>=0; i--)
	{
		for(int j=9; j>=0; j--)
		{
			int n = i*10+j;
			if(i > 0 && j > 0)
			{
				int nn = (i-1)*10+(j-1);
				A.v[n][nn] = 1;
			}
			else
			{
				for(int k=0; k<=9; k++)
				{
					for(int l=0; l<=9; l++)
					{
						int nn = k*10+l;
						ll tr = trans[n][nn];
						if(!tr) continue;
						for(int x=0; x<B; x++)
						{
							A.v[n][x] = (A.v[n][x] + tr * A.v[nn][x]) % MOD;
						}
					}
				}
			}
		}
	}
}

ll calc()
{
	make_trans();
	make_mat();

	Mat res = I, cur = A;
	while(N)
	{
		if(N&1LL)
			res = res * cur;
		cur = cur * cur;
		N >>= 1;
	}

	ll ans = res.v[0][0] % MOD;
	if(ans < -1) ans += MOD;

	return ans;
}

int main() {
	IOS;

	cin>>N>>M;
	for(int i=1; i<=M; i++)
		cin>>c[i];

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

