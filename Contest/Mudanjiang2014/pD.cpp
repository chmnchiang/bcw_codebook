#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

typedef long double ld;

const int MAXN = 52;
const int MAXK = MAXN * MAXN;

int N, M;
ld d[MAXK][MAXK];
ld comb[MAXN][MAXN];

void init()
{
	comb[0][0] = 1;
	for(int i=1; i<MAXN; i++)
	{
		comb[i][0] = 1;
		for(int j=1; j<=i; j++)
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
	}
}

void pre()
{
	for(int i=0; i<N*M; i++)
	{
		d[i][0] = 1;
		for(int k=1; k<=i; k++)
		{
			d[i][k] = d[i][k-1] * (i+1-k) / (M*N+1-k);
		}
		//for(int k=0; k<=i; k++)
		//	cout<<i<<","<<k<<" : "<<d[i][k]<<endl;
	}
}

ld calc(int n, int m)
{
	ld ret = 0;
	for(int k=max(n, m); k<=n*m; k++)
	{
		ld cur = 0;
		for(int i=0; i<=n; i++)
		{
			for(int j=0; j<=m; j++)
			{
				int q = (n-i) * (m-j);
				if(q < k) continue;
				ld dif = comb[n][i] * comb[m][j] * d[q][k];
				if((i+j)%2)
					dif = -dif;
				cur += dif;
				//cur += comb[n][i] * comb[m][j] * comb[q][k] / comb[M*N][k] * ((i+j)%2 ? -1 : 1);
			}
		}
		cur /= (N*M-k);
		cur *= k+1;
		//if(k<50)cout<<k<<" :: "<<cur<<endl;
		ret += cur;
	}
	//cout<<"Calc "<<n<<","<<m<<" = "<<ret<<endl;
	return ret;
}

int main() {
	init();
    IOS;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>M;
		pre();

		ld ans = calc(N-1, M-1) + calc(N-1, M) + calc(N, M-1);
		ans *= N*M;
		cout<<fixed<<setprecision(12)<<ans<<endl;		
	}

    return 0;
}
