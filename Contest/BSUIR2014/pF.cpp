#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAXN = 101010;

int N;
ll arr[MAXN];
multimap<ll, int> ms;

int main() {
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];
	for(int i=0; i<N; i++)
		ms.insert(MP(arr[i], i));

	vector<pll> vans, vbns;
	vector<int> zeros;
	while(!ms.empty())
	{
		auto jt = --ms.end();
		auto p = *jt;
		ms.erase(jt);
		ll val = p.F;
		if(val == 0)
		{
			zeros.PB(p.S);
			continue;
		}
		int llgg = __lg(val);
		ll up = (2LL<<llgg);
		ll rem = up - val;

		auto it = ms.find(rem);
		if(it != ms.end())
		{
			if(val == rem) vbns.PB(MP(p.S, it->S));
			else vans.PB(MP(p.S, it->S));
			ms.erase(it);
		}
		else if(rem == val)
		{
			it = ms.find(0);
			if(it != ms.end())
			{
				vans.PB(MP(p.S, it->S));
				ms.erase(it);
			}
		}
	}

	while((int)zeros.size() >= 2 && !vbns.empty())
	{
		vans.PB(MP(vbns.back().F, zeros.back()));
		zeros.pop_back();
		vans.PB(MP(vbns.back().S, zeros.back()));
		zeros.pop_back();
		vbns.pop_back();
	}
	for(auto p: vbns)
		vans.PB(p);

	cout<<vans.size()<<"\n";
	for(auto p: vans)
		cout<<p.F+1<<" "<<p.S+1<<"\n";

	return 0;
}

