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

const int MAXN = 20;

int N, M;
set<int> arr[MAXN], brr[MAXN];
multiset<int> good[MAXN];

int dfs(int lv)
{
	if(lv >= M)
	{
		int ans = 0;
		for(int i=0; i<N; i++)
		{
			bool ok = true;
			for(auto x: arr[i])
				if(!good[i].count(x))
					ok = false;

			if(ok) ans++;
		}

		return ans;
	}

	int ans = 0;
	ans = max(ans, dfs(lv+1));
	for(auto x: brr[lv])
	{
		for(int i=0; i<N; i++)
		{
			if(arr[i].count(x))
			{
				for(auto y: brr[lv])
				{
					good[i].insert(y);
				}
				int res = dfs(lv+1);
				ans = max(ans, res);
				for(auto y: brr[lv])
				{
					good[i].erase(good[i].find(y));
				}
			}
		}
	}

	return ans;
}

int calc()
{
	int ans = dfs(0);
	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M;
		for(int i=0; i<N; i++)
		{
			arr[i].clear();
			good[i].clear();
			int c;
			cin>>c;
			for(int j=0; j<c; j++)
			{
				int x;
				cin>>x;
				arr[i].insert(x);
			}
		}
		for(int i=0; i<M; i++)
		{
			brr[i].clear();
			int d;
			cin>>d;
			for(int j=0; j<d; j++)
			{
				int x;
				cin>>x;
				brr[i].insert(x);
			}
		}

		int ans = calc();

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

