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
typedef pair<int, int> pii;

const int MAXN = 202020;
const ll XHASH = 137;
const ll YHASH = 371;
const ll MOD = 1000000007;
//aconst ll YMOD = 1010101109;

int L, M, N, C, X;
ll tempval;
string S, arr[MAXN];
pii pt[MAXN];
int spos[MAXN];


ll lpow(ll a, ll p, ll m=MOD)
{
	ll ret = 1, cur = a%m;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % m;
		cur = cur * cur % m;
		p >>= 1;
	}
	return ret;
}

ll linv(ll a, ll m=MOD)
{
	return lpow(a, m-2, m);
}

ll get_hash(int x, int y)
{
	ll ret = 1; 
	if(x >= 0)
		ret = ret * lpow(XHASH, x) % MOD;
	else
		ret = ret * linv(lpow(XHASH, -x)) % MOD;
	if(y >= 0)
		ret = ret * lpow(YHASH, y) % MOD;
	else
		ret = ret * linv(lpow(YHASH, -y)) % MOD;
	return ret;
}

void calc()
{
	C = 1;
	pt[0] = {0, 0};
	spos[0] = 0;

	for(int i=0; i<SZ(S); i++)
	{
		if(S[i] == 'u')
		{
			pt[C] = {pt[C-1].F-1, pt[C-1].S};
			spos[C] = i+1;
			C++;
		}
		else if(S[i] == 'd')
		{
			pt[C] = {pt[C-1].F+1, pt[C-1].S};
			spos[C] = i+1;
			C++;
		}
		else if(S[i] == 'l')
		{
			pt[C] = {pt[C-1].F, pt[C-1].S-1};
			spos[C] = i+1;
			C++;
		}
		else if(S[i] == 'r')
		{
			pt[C] = {pt[C-1].F, pt[C-1].S+1};
			spos[C] = i+1;
			C++;
		}
	}
	
//	for(int i=0; i<C; i++)
//		cout<<spos[i]<<" "<<pt[i]<<endl;

	multiset<int> msx, msy;
	map<pii, int> mcnt;
	int cnt = 1;
	msx.insert(0);
	msy.insert(0);
	mcnt[{0, 0}] = 1;

	ll cur_hash = get_hash(pt[0].F, pt[0].S);
	int rb = 0;
	for(int lb=0; lb<C; lb++)
	{
		while(rb < C-1 and cnt < X)
		{
			rb++;
			pii p = pt[rb];
			if(mcnt[p] == 0)
			{
				cnt++;
				cur_hash += get_hash(p.F, p.S);
				cur_hash %= MOD;
				msx.insert(p.F);
				msy.insert(p.S);
			}
			mcnt[p]++;
		}

		//cout<<lb<<" "<<rb<<" "<<cnt<<endl;

		if(cnt < X) break;

		ll minx = *msx.begin();
		ll miny = *msy.begin();
		ll real_hash = cur_hash * linv(get_hash(minx, miny)) % MOD;

		//cout<<lb<<"~"<<rb<<" CUR "<<cur_hash<<" REAL "<<real_hash<<endl;

		/*for(auto x: mcnt)
		{
			int xx = x.F.F - minx, yyy = x.F.S - miny;
			int zz = x.S;
			cout<<xx<<","<<yyy<<" : "<<zz<<endl;
		}*/

		if(real_hash == tempval)
		{
			cout<<"YES"<<endl;
			cout<<spos[lb]+1<<" "<<spos[rb]<<endl;
			return;
		}

		pii p = pt[lb];
		mcnt[p]--;
		if(mcnt[p] == 0)
		{
			cnt--;
			cur_hash -= get_hash(p.F, p.S);
			cur_hash %= MOD;
			if(cur_hash < 0) cur_hash += MOD;
			auto it = msx.lower_bound(p.F);
			msx.erase(it);
			it = msy.lower_bound(p.S);
			msy.erase(it);
		}
	}

	cout<<"NO"<<endl;
}

int main() {
	IOS;
	FILEIO("easy");

	cin>>L;
	getline(cin, S);
	getline(cin, S);
	cin>>N>>M;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	int minx = MAXN, miny = MAXN;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			if(arr[i][j] == 'X')
			{
				minx = min(minx, i);
				miny = min(miny, j);
			}
		}
	}

	tempval = 0;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			if(arr[i][j] == 'X')
			{
				tempval += get_hash(i-minx, j-miny);
				tempval %= MOD;
				X++;
			}
		}
	}

//	cout<<"TEMPVAL "<<tempval<<endl;
//	cout<<"X = "<<X<<endl;

	calc();

	return 0;
}

