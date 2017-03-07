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

const int MAXN = 101010;

struct Poly
{
	bitset<MAXN> v;
	int d;
};
typedef pair<Poly, Poly> ppp;

Poly A, B;

void shiftadd(Poly &a, Poly &b, int dif)
{
	a.v ^= (b.v << dif);
	a.d = max(a.d, b.d + dif);
	while(a.d > 0 and !a.v[a.d])
		a.d--;
}

Poly getPoly()
{
	Poly p;
	int n;
	cin>>n;
	p.d = n;
	int x;
	for(int i=0; i<=n; i++)
	{
		cin>>x;
		p.v[i] = x;
	}
	return p;
}

ostream& operator <<(ostream &s, const Poly &p)
{
	s<<p.d;
	for(int i=0; i<=p.d; i++)
		s<<" "<<p.v[i];
	return s;
}

ppp extgcd(Poly a, Poly b)
{
	vector<int> op;

	while(!(b.d == 0 and !b.v[0]))
	{
		//cout<<a<<" / "<<b<<endl;
		if(a.d < b.d)
		{
			swap(a, b);
			op.PB(-1);
		}
		else
		{
			int dif = a.d - b.d;
			shiftadd(a, b, dif);
			op.PB(dif);
			swap(a, b);
			op.PB(-1);
		}
	}

	Poly X, Y;
	X.d = 0;
	X.v[0] = 1;
	Y = X;

	for(int i=SZ(op)-1; i>=0; i--)
	{
		int d = op[i];
		if(d == -1)
			swap(X, Y);
		else
			shiftadd(Y, X, d);
	}

	return {X, Y};

	/*
	cout<<"AXD "<<a<<" "<<b<<endl;
	ppp ret;
	if(a.d < b.d)
	{
		ppp res = extgcd(b, a);
		ret = {res.S, res.F};
		cout<<"USE A"<<endl;
	}
	else if(b.d == 0 and !b.v[0])
	{
		Poly p;
		p.d = 0;
		p.v[0] = 1;
		ret =  {p, p};
		cout<<"USE B"<<endl;
	}
	else
	{
		int dif = a.d - b.d;
		Poly c = shiftadd(a, b, dif);
		ppp res = extgcd(b, c);
		ret = {res.S, shiftadd(res.F, res.S, dif)};
		cout<<"DIF "<<dif<<" RES "<<c<<" / "<<res<<endl;
		cout<<"USE C"<<endl;
	}

	cout<<"("<<a<<","<<b<<") X "<<ret.F<<" Y "<<ret.S<<endl;

	return ret;
	*/
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		A = getPoly();
		B = getPoly();

		ppp res = extgcd(A, B);

		cout<<res.F<<endl<<res.S<<endl;

		//cout<<"XD"<<endl;
	}

	return 0;
}

