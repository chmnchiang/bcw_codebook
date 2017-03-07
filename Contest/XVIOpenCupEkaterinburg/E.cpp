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

typedef long long ll;
const int MAXN = 10010;

int N;
ll px[MAXN], py[MAXN], pr[MAXN]; 
ll pz[MAXN][4];
bool used[4];
int arr[4];

void dfs(int lv, ll cur, ll &ans)
{
	if(lv == 4)
	{
		//cout<<"C = "<<cur<<endl;
		ans += cur;
		return;
	}

	for(int i=0; i<4; i++)
	{
		if(used[i]) continue;
		used[i] = true;
		int sgn = 1;
		for(int j=i+1; j<4; j++)
			if(used[j])
				sgn = -sgn;

		//cout<<"PZ "<<pz[arr[i]][lv]<<endl;
		dfs(lv+1, cur * sgn * pz[arr[i]][lv], ans);
		used[i] = false;
	}
}

ll det(int a, int b, int c, int d)
{
	ll ans = 
		+ pz[a][0] * pz[b][1] * pz[c][2] * pz[d][3]
		- pz[a][0] * pz[b][1] * pz[c][3] * pz[d][2]
		- pz[a][0] * pz[b][2] * pz[c][1] * pz[d][3]
		+ pz[a][0] * pz[b][2] * pz[c][3] * pz[d][1]
		+ pz[a][0] * pz[b][3] * pz[c][1] * pz[d][2]
		- pz[a][0] * pz[b][3] * pz[c][2] * pz[d][1]

		- pz[a][1] * pz[b][0] * pz[c][2] * pz[d][3]
		+ pz[a][1] * pz[b][0] * pz[c][3] * pz[d][2]
		+ pz[a][1] * pz[b][2] * pz[c][0] * pz[d][3]
		- pz[a][1] * pz[b][2] * pz[c][3] * pz[d][0]
		- pz[a][1] * pz[b][3] * pz[c][0] * pz[d][2]
		+ pz[a][1] * pz[b][3] * pz[c][2] * pz[d][0]

		+ pz[a][2] * pz[b][0] * pz[c][1] * pz[d][3]
		- pz[a][2] * pz[b][0] * pz[c][3] * pz[d][1]
		- pz[a][2] * pz[b][1] * pz[c][0] * pz[d][3]
		+ pz[a][2] * pz[b][1] * pz[c][3] * pz[d][0]
		+ pz[a][2] * pz[b][3] * pz[c][0] * pz[d][1]
		- pz[a][2] * pz[b][3] * pz[c][1] * pz[d][0]

		- pz[a][3] * pz[b][0] * pz[c][1] * pz[d][2]
		+ pz[a][3] * pz[b][0] * pz[c][2] * pz[d][1]
		+ pz[a][3] * pz[b][1] * pz[c][0] * pz[d][2]
		- pz[a][3] * pz[b][1] * pz[c][2] * pz[d][0]
		- pz[a][3] * pz[b][2] * pz[c][0] * pz[d][1]
		+ pz[a][3] * pz[b][2] * pz[c][1] * pz[d][0];


	return ans;
	/*
	arr[0] = a;
	arr[1] = b;
	arr[2] = c;
	arr[3] = d;
	ll ans = 0;
	dfs(0, 1, ans);
	return ans;*/
}

bool calc()
{
	for(int i=0; i<N; i++)
	{
		ll x1 = px[3*i+1] - px[3*i], y1 = py[3*i+1] - py[3*i];
		ll x2 = px[3*i+2] - px[3*i], y2 = py[3*i+2] - py[3*i];
		if(x1 * y2 - x2 * y1 < 0)
		{
			swap(px[3*i+1], px[3*i+2]);
			swap(py[3*i+1], py[3*i+2]);
			swap(pr[3*i+1], pr[3*i+2]);
		}
	}
	for(int i=0; i<3*N; i++)
	{
		pz[i][0] = pr[i];
		pz[i][1] = px[i];
		pz[i][2] = py[i];
		pz[i][3] = 1;
	}

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<3*N; j++)
		{
			ll d = det(j, 3*i, 3*i+1, 3*i+2);
			if(d < 0) return false;
		}
	}
	return true;
}

int main() {
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<3*N; i++)
		{
			cin>>px[i]>>py[i];
			pr[i] = px[i] * px[i] + py[i] * py[i];
		}

		bool ans = calc();
		cout<<(ans ? "YES" : "NO")<<endl;
	}

	return 0;
}

