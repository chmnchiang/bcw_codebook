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

typedef long double ld;

const ld PI = acosl(-1);

int A, B, C, L;

ld calc(vector<ld> vec, ld lb, ld rb)
{
	ld ret = 0;
	for(int i=0; i<200; i++)
	{
		ret = 0;
		ld mb = (lb + rb) / 2;

		ld l = 0;
		for(auto a: vec)
		{
			ld th = 2 * asinl(a / (2*mb));
			ret += th - sinl(th);
			l += mb * th;
		}

		ret *= mb * mb / 2;

		if(l > L)
			lb = mb;
		else
			rb = mb;
	}

	return ret;
}

int main() {
    FILEIO("border");

	while(cin>>A>>B>>C>>L)
	{
		if(A<B) swap(A, B);
		if(B<C) swap(B, C);
		if(A<B) swap(A, B);

		ld ans = 0;

		ld s = (A+B+C)/2.;
		ld area = sqrtl(s*(s-A)*(s-B)*(s-C));
		ld R = (A*B*C) / (4*area);

		if(A*A<=B*B+C*C)
		{
			if(A+B+C == L)
			{
				ans = area;
			}
			else if(L < 2 * PI * R)
			{
				vector<ld> vec;
				vec.PB(A);
				vec.PB(B);
				vec.PB(C);
				
				ans = area + calc(vec, R, 1E20);
			}
			else
			{
				ans = L*L/(4*PI);
			}
		}
		else
		{
			ld rp = 4 * R * asinl(A/(2*R));
			if(A+B+C == L)
			{
				ans = area;
			}
			else if(L < rp)
			{
				vector<ld> vec;
				vec.PB(A);
				vec.PB(B);
				vec.PB(C);
				
				ans = area + calc(vec, R, 1E20);
			}
			else if(L < PI * A)
			{
				vector<ld> vec;
				vec.PB(A);
				vec.PB(A);
				
				ans = calc(vec, A/2., R);
			}
			else
			{
				ans = L*L/(4*PI);
			}
		}

		cout<<fixed<<setprecision(15)<<ans<<endl;
	}

    return 0;
}

