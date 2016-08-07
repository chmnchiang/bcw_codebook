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


int N,X,rev[55];
int a[55];
double b[55];
double dp[51][505050];
bool prv[51][505050];

int main() {
	FILEIO("discount");
	cin >> N >> X;
	REP(i,N) {
		cin >> a[i] >> b[i];
		b[i] = (100 - b[i]) * 0.01;
	}

	for(int i=0; i<51; i++)
		for(int j=0; j<505050; j++)
			dp[i][j] = 1E100;
	dp[0][0] = 1;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<505050; j++)
		{
			dp[i+1][j] = dp[i][j] * b[i];
			prv[i+1][j] = 1;
		}
		for(int j=0; j+a[i]<505050; j++)
		{
			double newv = dp[i][j];
			if(dp[i+1][j+a[i]] > newv)
			{
				dp[i+1][j+a[i]] = newv;
				prv[i+1][j+a[i]] = 0;
			}
		}
	}

	int bst = -1;
	double bval = 1E100;

	for(int i=0; i<505050; i++)
	{
		double val = X * dp[N][i] - i;
 		if(val < bval)
		{
			bval = val;
			bst = i;
		}
	}

	for(int i=N; i>0; i--)
	{
		rev[i-1] = prv[i][bst];
		if(!rev[i-1]) bst -= a[i-1];
	}

	for(int i=0; i<N; i++)
		if(rev[i]) cout<<i+1<<" reverse"<<endl;
	for(int i=0; i<N; i++)
		if(!rev[i]) cout<<i+1<<" front"<<endl;

    return 0;
}

