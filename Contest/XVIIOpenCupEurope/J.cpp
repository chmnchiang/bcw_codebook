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


#define int long long

typedef pair<int, int> pii;
typedef long long ll;

const ll INF = 1LL<<50;

int N,D,M;
vector<int> ip;

map<pii, int> mo, mr;
map<pii, vector<bool> > ma;

int32_t main() {
	IOS;
	cin>>N>>D;
	ip.resize(D);
	REP(i,D)
	{
		cin>>ip[i];
		ip[i]--;
	}


	cin>>M;
	REP(i,M) {
		int s,d,p;
		char t;
		cin>>s>>d>>t>>p;
		s--;
		d--;
		
		pii r = {s, d};
		if(!mo.count(r))
			mo[r] = p;
		mo[r] = min(mo[r], p);

		if(t == 'R')
		{
			if(!mr.count(r))
				mr[r] = p;
			mr[r] = min(mr[r], p);
		}
	}

	for(int i=0; i<D-1; i++)
	{
		int x = ip[i], y = ip[i+1];
		if(x < y)
			ma[{x, y}].PB(0);
		else
			ma[{y, x}].PB(1);
	}

	ll ans = 0;

	for(auto &p: ma)
	{
		int x, y;
		tie(x, y) = p.F;
		//cout<<x<<" "<<y<<endl;
		auto vec = p.S;

		//cout<<vec<<endl;

		int ocnt = 0, icnt = 0;
		for(auto z: vec)
		{
			if(z) icnt++;
			else ocnt++;
		}

		if(!mo.count({x, y})) mo[{x, y}] = INF;
		if(!mo.count({y, x})) mo[{y, x}] = INF;
		if(!mr.count({x, y})) mr[{x, y}] = INF;
		if(!mr.count({y, x})) mr[{y, x}] = INF;

		ll o = mo[{x, y}];
		ll i = mo[{y, x}];
		ll oi = mr[{x, y}];
		ll io = mr[{y, x}];

		oi = min(oi, o+i);
		io = min(io, o+i);

		//cout<<o<<" "<<i<<" "<<oi<<" "<<io<<endl;

		ll g01 = o + i - oi;
		ll g10 = o + i - io;

		if(g01 < g10)
		{
			swap(o, i);
			swap(oi, io);
			swap(g01, g10);
			swap(icnt, ocnt);
			for(int j=0; j<SZ(vec); j++)
				vec[j] = !vec[j];
		}

		int cur = 0;
		int bin = 0;
		for(auto z: vec)
		{
			if(!z) cur++;
			else if(cur > 0)
			{
				cur--;
				bin++;
			}
		}

		int m = min(ocnt, icnt);
		ll val = i * icnt + o * ocnt - bin * g01 - (m-bin) * g10;

		//cout<<vec<<" M "<<m<<" BIN "<<bin<<endl;

		ans += val;
	}

	cout<<ans<<endl;

	return 0;
}

