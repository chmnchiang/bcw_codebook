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

const int MAXN = 52;
const int MAXS = 5000;
const ll MOD = 1000000007;

int M, N, R;
int S;
vector<int> vstate[MAXS];
map<vector<int>, int> vmp;
int trans[MAXS][MAXN];
ll dp[MAXN][MAXS];

void normal(vector<int> &vec) {
	map<int,int> mp;
	int id = 0;
	for (auto it:vec) if (not mp.count(it)) mp[it] = id++;
	for (auto &it:vec) it = mp[it];
}

bool check(vector<int> &vec) {
	for(int i=0; i<M; i++)
		for(int j=i+1; j<M; j++)
			for(int k=j+1; k<M; k++)
				for(int l=k+1; l<M; l++)
					if(vec[i] == vec[k] && vec[j] == vec[l] && vec[i] != vec[j])
						return true;
	return false;
}

void dfs(int lv, vector<int> &vec)
{
	if(lv == M)
	{
		vector<int> v2 = vec;
		normal(v2);
		if(check(v2) && !vmp.count(v2))
		{
//			cout<<v2<<endl;
			vmp[v2] = S;
			vstate[S] = v2;
			S++;
		}
		return;
	}
	for(int i=0; i<=lv && i < R; i++)
	{
		vec.PB(i);
		dfs(lv+1, vec);
		vec.pop_back();
	}
}

void make_state()
{
	vector<int> vec;
	dfs(0, vec);
}

void make_trans()
{
	for(int i=0; i<S; i++)
	{
		vector<int> v = vstate[i];
		v.erase(v.begin());
		for(int j=0; j<MAXN; j++)
		{
			vector<int> v2 = v;
			v2.PB(j);
			normal(v2);
//			cout<<v2<<endl;
			trans[i][j] = -1;
			if(vmp.count(v2))
				trans[i][j] = vmp[v2];
		}
	}
}

ll calc()
{
	make_state();
	make_trans();

	for(int i=0; i<S; i++)
	{
		int mn = 0;
		for(int j=0; j<M; j++)
			mn = max(mn, vstate[i][j]);
		mn += 1;
		dp[M][i] = 1;
		for(int j=0; j<mn; j++)
			dp[M][i] = (dp[M][i] * (R-j)) % MOD;
	}

//	cout<<dp[M][0]<<endl;
//	for(int i=0; i<MAXN; i++) cout<<i<<" "<<trans[0][i]<<endl;

	for(int i=M+1; i<=N; i++)
	{
		for(int j=0; j<S; j++)
		{
			for(int k=0; k<R; k++)
			{
				int t = trans[j][k];
				if(t == -1) continue;
				dp[i][t] = (dp[i][t] + dp[i-1][j]) % MOD;
			}
		}
	}

	ll ans = 0;
	for(int i=0; i<S; i++)
		ans += dp[N][i];
	ans %= MOD;

	return ans;
}

int main() {
	IOS;
	FILEIO("linked");

	cin>>M>>N>>R;

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

