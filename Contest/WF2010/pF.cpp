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
typedef long double ld;

const int MAXN = 105;

ll S, P, H;
ll D;
ll arr[MAXN][MAXN];
ld ans;

ll ceil(ll a, ll b)
{
	return (a+b-1) / b;
}

ld calc_triangle(ll a, ll b, ll c)
{
	if(a>b) swap(a, b);
	if(b>c) swap(b, c);
	if(a>b) swap(a, b);

//	cout<<a<<" "<<b<<" "<<c<<" : ";

	if(a == c)
	{
//		cout<<" x"<<endl;
		return 0;
	}

	ld res = 0;

	ld dif = 1./2. - (ld)(c-b) / (c-a);
	ld L = D * sqrtl(3./4. + dif * dif);

	ll lb = ceil(a+1, H), rb = ceil(b, H) - 1;
	if(lb <= rb)
		res += L / (b-a) * (rb-lb+1) * (H * (rb+lb) / 2. - a);
//	cout<<" -- "<<lb<<" "<<rb;

	lb = ceil(b+1, H), rb = ceil(c, H) - 1;
	if(lb <= rb)
		res += L / (c-b) * (rb-lb+1) * (c - H * (rb+lb) / 2.);

	if(a<b && b<c && b%H==0)
		res += L;

//	cout<<" -- "<<lb<<" "<<rb<<" "<<res<<endl;

	return res;
}

ld calc_edgeB(ll a, ll b, ll c)
{
//	cout<<a<<","<<b<<","<<c<<endl;
	if(a != b) return 0;
	if(a%H) return 0;
	return D;
}

ld calc_edgeNB(ll a, ll b, ll c, ll d)
{
//	cout<<a<<","<<b<<","<<c<<","<<d<<endl;
	if(a != b) return 0;
	if(a%H) return 0;
	if(a == c && a == d) return 0;
	return D;
}

ll calc()
{
	ans = 0;

	for(int i=0; i<S-1; i++)
	{
		if(i%2==0)
		{
			for(int j=0; j<P-1; j++)
			{
				ans += calc_triangle(arr[i][j], arr[i+1][j], arr[i+1][j+1]);
				ans += calc_triangle(arr[i][j], arr[i][j+1], arr[i+1][j+1]);
				ans += calc_edgeNB(arr[i][j], arr[i+1][j+1], arr[i][j+1], arr[i+1][j]);
				ans += calc_edgeNB(arr[i][j+1], arr[i+1][j+1], arr[i][j], arr[i+1][j+2]);
			}
			ans += calc_triangle(arr[i][P-1], arr[i+1][P-1], arr[i+1][P]);
			ans += calc_edgeB(arr[i][0], arr[i+1][0], arr[i+1][1]);
			ans += calc_edgeB(arr[i][P-1], arr[i+1][P], arr[i+1][P-1]);
		}
		else
		{
			for(int j=0; j<P-1; j++)
			{
				ans += calc_triangle(arr[i+1][j], arr[i][j], arr[i][j+1]);
				ans += calc_triangle(arr[i+1][j], arr[i+1][j+1], arr[i][j+1]);
				ans += calc_edgeNB(arr[i+1][j], arr[i][j+1], arr[i+1][j+1], arr[i][j]);
				ans += calc_edgeNB(arr[i+1][j+1], arr[i][j+1], arr[i+1][j], arr[i][j+2]);
			}
			ans += calc_triangle(arr[i+1][P-1], arr[i][P-1], arr[i][P]);
			ans += calc_edgeB(arr[i+1][0], arr[i][0], arr[i][1]);
			ans += calc_edgeB(arr[i+1][P-1], arr[i][P], arr[i][P-1]);
		}
	}

	for(int i=0; i<S; i++)
	{
		int l = P + i%2;
		for(int j=0; j<l-1; j++)
		{
			int b1 = -1, b2 = -1;
			if(i%2 == 0)
			{
				if(i > 0) b1 = arr[i-1][j+1];
				if(i < S-1) b2 = arr[i+1][j+1];
			}
			else
			{
				if(i > 0) b1 = arr[i-1][j];
				if(i < S-1) b2 = arr[i+1][j];
			}

			if(b1 == -1 || b2 == -1)
				ans += calc_edgeB(arr[i][j], arr[i][j+1], max(b1, b2));
			else
				ans += calc_edgeNB(arr[i][j], arr[i][j+1], b1, b2);
		}
	}

//	cout<<ans<<endl;

	return ans + 0.5 + 1E-10;
}

int main() {
	IOS;

	int t=0;
	while(cin>>S && S)
	{
		t++;
		cin>>P>>D>>H;
		for(int i=0; i<S; i++)
		{
			int l = P + i%2;
			for(int j=0; j<l; j++)
				cin>>arr[i][j];
		}

		ll as = calc();
		cout<<"Case "<<t<<": "<<as<<endl;
	}

	return 0;
}

