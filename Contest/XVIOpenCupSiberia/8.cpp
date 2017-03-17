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



typedef pair<int, int> pii;

const int MAXN = 1010101;

int N, M;
int pt[MAXN];
pii seg[MAXN];
int dif[2*MAXN];

void calc()
{
	map<int, int> mp;
	for(int i=0; i<M; i++)
	{
		mp[seg[i].F]++;
		mp[seg[i].S+1]--;
	}

	int cur = 0;
	vector<pii> vdif;
	for(auto p: mp)
	{
		int nw = cur + p.S;
		if(!cur and nw)
			vdif.PB({p.F, 1});
		else if(cur and !nw)
			vdif.PB({p.F, -1});
		cur = nw;
	}

	for(int i=0; i<N; i++)
	{
		int x = pt[i];
		for(auto p: vdif)
		{
			dif[p.F - x + MAXN] += p.S;
		}
	}

	int mx = 0, pos = -1;
	cur = 0;
	for(int i=0; i<2*MAXN; i++)
	{
		cur += dif[i];
		int ip = abs(i - MAXN);
		if(cur > mx)
		{
			mx = cur;
			pos = ip;
		}
		else if(cur == mx)
			pos = min(pos, ip);
	}

	cout<<pos<<" "<<mx<<endl;
}

int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;

	cin>>N>>M;
	for(int i=0; i<N; i++)
		cin>>pt[i];
	for(int i=0; i<M; i++)
		cin>>seg[i].F>>seg[i].S;

	calc();

	return 0;
}

