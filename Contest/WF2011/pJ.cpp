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

const int MAXN = 1000005;
const int MAXC = 321;
const int INF = 102;

int V;
vector<int> nvec;
map<int, string> nmp;
char dp[MAXC][MAXN];
char prv[MAXC][MAXN];

string gen_str(int i, char c)
{
	stringstream ss;
	string s;
	ss << i << c;
	ss >> s;
	return s;
}

void pre()
{
	for(int i=2; ; i++)
	{
		int z = 0;
		for(int j=1; j<=i; j++)
			z += j * j;
		if(z >= MAXN) break;
		nvec.PB(z);
		assert(!nmp.count(z));
		nmp[z] = gen_str(i, 'H');
	}
	for(int i=3; ; i++)
	{
		int z = 0;
		for(int j=i; j>=1; j-=2)
			z += j * j;
		if(z >= MAXN) break;
		nvec.PB(z);
		assert(!nmp.count(z));
		nmp[z] = gen_str(i, 'L');
	}

	V = nvec.size();
	sort(ALL(nvec));

	for(int i=0; i<MAXC; i++)
		for(int j=0; j<MAXN; j++)
			dp[i][j] = INF;
	dp[0][0] = 0;

	for(int j=0; j<V; j++)
	{
		int v = nvec[j];
		for(int i=0; i<MAXN; i++)
		{
			if(dp[j][i] == INF) continue;
			if(dp[j][i] < dp[j+1][i])
			{
				dp[j+1][i] = dp[j][i];
				prv[j+1][i] = 0;
			}
			if(i+v < MAXN && dp[j][i] + 1 <= dp[j+1][i+v])
			{
				dp[j+1][i+v] = dp[j][i] + 1;
				prv[j+1][i+v] = 1;
			}
		}
	}
}

string calc(int x)
{
	string ret = "";
	int cur = V;
	if(dp[cur][x] == INF) return "impossible";
	while(cur > 0)
	{
		if(prv[cur][x])
		{
			int v = nvec[cur-1];
			ret += nmp[v] + " ";
			x -= v;
		}
		cur--;
	}
	ret.pop_back();
	return ret;
}

int main() {
	IOS;
	pre();

	int N;
	int t = 0;
	while(cin>>N && N)
	{
		t++;
		string ans = calc(N);
		cout<<"Case "<<t<<": "<<ans<<endl;
	}

	return 0;
}

