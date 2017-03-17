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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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

const int MAXN = 10101;

int N, W, H, M;
ll h[MAXN], k[MAXN];
set<ll> layer[MAXN];
ll w[MAXN], wx[MAXN], wy[MAXN], lb[MAXN], rb[MAXN];

bool check_collapse()
{
	ll cw = 0, cwx = 0, cwy = 0;
	for(int i=H; i>=1; i--)
	{
		//cout<<"L "<<i<<" CW "<<cw<<" CWX "<<cwx<<" CWY "<<cwy<<" ["<<lb[i]<<","<<rb[i]<<"]"<<endl;
		if(cw > 0)
		{
			if(i%2==1)
			{
				if(cwx <= cw * lb[i] or cwx >= cw * rb[i]) return true;
			}
			else
			{
				if(cwy <= cw * lb[i] or cwy >= cw * rb[i]) return true;
			}
		}

		cw += w[i];
		cwx += wx[i];
		cwy += wy[i];
	}

	return false;
}

int calc()
{
	for(int i=1; i<=H; i++)
	{
		layer[i].clear();
		w[i] = N;
		wx[i] = wy[i] = N * (N+1LL);
		lb[i] = 1;
		rb[i] = 2*N+1;

		layer[i].insert(1);
		layer[i].insert(N);
	}

	for(int i=0; i<M; i++)
	{
		int l = h[i], kk = k[i];
		layer[l].insert(kk);
		if(kk > 1) layer[l].insert(kk-1);
		if(kk < N) layer[l].insert(kk+1);
	}


	for(int i=0; i<M; i++)
	{
		int l = h[i], kk = k[i];;
		layer[l].erase(kk);
		if(l%2 == 1)
		{
			wx[l] -= 2*kk;
			wy[l] -= N+1;
		}
		else
		{
			wx[l] -= N+1;
			wy[l] -= 2*kk;
		}
		w[l]--;

		if(layer[l].empty()) return i+1;
		lb[l] = 2 * (*layer[l].begin()) - 1;
		rb[l] = 2 * (*layer[l].rbegin()) + 1;

		//cout<<"Layer "<<l<<" : "<<lb[l]<<"~"<<rb[l]<<endl;

		if(check_collapse()) return i+1;
	}

	return -1;
}

int main() {
	FILEIO("jenga");
	IOS;

	while(cin>>N>>W>>H>>M)
	{
		for(int i=0; i<M; i++)
			cin>>h[i]>>k[i];

		int ans = calc();
		if(ans == -1)
			cout<<"no"<<endl;
		else
			cout<<"yes"<<endl<<ans<<endl;
	}

	return 0;
}

