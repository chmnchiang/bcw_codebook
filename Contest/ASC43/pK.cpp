//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Eat! }}}

typedef long long ll;
typedef pair<ll, ll> pll;

pll operator+ (pll a, pll b) { return MP(a.F+b.F, a.S+b.S); }
pll operator- (pll a, pll b) { return MP(a.F-b.F, a.S-b.S); }
pll operator* (pll a, ll b) { return MP(a.F*b, a.S*b); }
ll dot(pll a, pll b) { return a.F*b.F+a.S*b.S; }
ll cross(pll a, pll b) { return a.F*b.S-a.S*b.F; }
int sign(ll x) { return x>0 ? 1 : (x<0 ? -1 : 0); }

const int MAXN = 101010;

int N;
pll pt[MAXN];
pll Q1, Q2, D;

int main(){
	IOS;
	FILEIO("kingdom");

	while(cin>>N && N)
	{
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;
		cin>>Q1.F>>Q1.S;
		cin>>Q2.F>>Q2.S;
		D = Q2 - Q1;

		vector<pll> v1, v2;
		int idx = 0;
		for(int i=0; i<N; i++)
		{
			int j = (i+1) % N;
			int s1 = sign(cross(D, pt[i]-Q1));
			int s2 = sign(cross(D, pt[j]-Q1));
			if(s1 != s2)
				idx = j;
		}

		for(int i=idx; i<N+idx; i++)
		{
			int ii = i % N;
			int s = sign(cross(D, pt[ii]-Q1));
			if(s > 0)
				v1.PB(pt[ii]);
			else if(s < 0)
				v2.PB(pt[ii]);
		}

		//for(auto i: v1) cout<<i.F<<","<<i.S<<" "; cout<<endl;
		//for(auto i: v2) cout<<i.F<<","<<i.S<<" "; cout<<endl;

		ll ans = 0;
		int lb = 0, rb = 0;

		int L2 = v2.size();
		for(auto p1: v1)
		{
			while(lb < L2 && cross(v2[lb]-p1, Q1-p1) >= 0)lb++;
			while(rb < L2 && cross(v2[rb]-p1, Q2-p1) > 0)rb++;
			ans += rb - lb;
			//cout<<lb<<"~"<<rb<<endl;
		}

		cout << ans << endl;
	}

	return 0;
}

