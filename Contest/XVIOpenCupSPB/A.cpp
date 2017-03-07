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

typedef pair<int, int> pii;

const int MAXN = 1010;

int N;
pii pt[MAXN];
int dis[MAXN];

pii reg(int a, int b)
{
	if(b < 0)
	{
		a = -a;
		b = -b;
	}
	int g = __gcd(abs(a), b);
	a /= g;
	b /= g;
	return {a, b};
}

int calc()
{
	for(int i=0; i<N; i++)
		dis[i] = pt[i].F * pt[i].F + pt[i].S * pt[i].S;

	vector<pii> vec;
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			int da = pt[i].F - pt[j].F;
			int db = dis[i] - dis[j];
			if(da != 0)
			{
				vec.PB(reg(db, da));
			}
			else if(db == 0)
			{
				return 0;
			}
		}
	}
	sort(ALL(vec));
	int L = unique(ALL(vec)) - vec.begin();
	return L + 1;
}

int main() {
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		int ans = calc();
		cout<<ans<<endl;
	}

	return 0;
}

