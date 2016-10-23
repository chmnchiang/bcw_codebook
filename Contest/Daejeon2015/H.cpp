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

const int MAXN = 30;

struct Frac
{
	ll a, b;
};

Frac norm(Frac f)
{
	ll _g = __gcd(abs(f.a), abs(f.b));
	f.a /= _g;
	f.b /= _g;
	if(f.b < 0)
	{
		f.a = -f.a;
		f.b = -f.b;
	}
	return f;
}

Frac operator*(Frac x, Frac y){return norm({x.a*y.a, x.b*y.b});}
Frac operator/(Frac x, Frac y){return norm({x.a*y.b, x.b*y.a});}
Frac operator+(Frac x, Frac y){return norm({x.a*y.b+y.a*x.b, x.b*y.b});}
Frac operator-(Frac x, Frac y){return norm({x.a*y.b-y.a*x.b, x.b*y.b});}
ostream& operator <<(ostream &s, const Frac f) {
    s<<f.a;
	if(f.b != 1) s<<"/"<<f.b;
	return s;
}

int N, T;
int c[MAXN];
Frac coef[MAXN][MAXN];
Frac comb[MAXN][MAXN];
Frac ans[MAXN];

void make()
{
	for(int i=0; i<MAXN; i++)
		for(int j=0; j<MAXN; j++)
			coef[i][j] = comb[i][j] = {0, 1};

	comb[0][0] = {1, 1};
	for(int i=1; i<MAXN-1; i++)
	{
		comb[i][0] = comb[i][i] = {1, 1};
		for(int j=1; j<i; j++)
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
	}

	coef[0][1] = {1, 1};

	for(int i=1; i<MAXN-1; i++)
	{
		Frac f = {1, i+1};
		coef[i][i+1] = {1, 1};
		for(int j=0; j<i; j++)
		{
			for(int k=0; k<MAXN; k++)
				coef[i][k] = coef[i][k] - coef[j][k] * comb[i+1][j];
		}
		for(int k=0; k<MAXN; k++)
			coef[i][k] = coef[i][k] * f;
	}
	
	for(int i=0; i<MAXN-1; i++)
		coef[i][i] = coef[i][i] + Frac({1, 1});

//	for(int i=0; i<=25; i++){cout<<i<<" : ";for(int j=0; j<=i+1; j++) cout<<coef[i][j]<<" ";cout<<endl;}
}

int main() {
	IOS;

	make();

	int _c;
	cin>>_c;
	while(_c--)
	{
		cin>>T;
		for(int i=0; i<=T; i++)
			cin>>c[i];

		for(int i=0; i<MAXN; i++)
			ans[i] = {0, 1};

		for(int i=0; i<=T; i++)
			for(int j=0; j<MAXN; j++)
				ans[j] = ans[j] + Frac({c[i], 1}) * coef[i][j];

		ll out = 0;
		for(int i=0; i<MAXN; i++)
			out += abs(ans[i].a);

		cout<<out<<endl;
	}

    return 0;
}

