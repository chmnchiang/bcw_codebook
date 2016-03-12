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
    freopen(name".in", "r", stdin);
//    freopen(name".out", "w", stdout);
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
typedef pair<ld, ld> pdd;
typedef pair<ld, int> pdi;

const int MAXN = 1010;
const ld PI = acosl(-1);
const ld EPS = 1E-8;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
ld theta(pdd a){return atan2l(a.S, a.F);}
ld abs(pdd a){return sqrtl(a.F*a.F+a.S*a.S);}
ld reg(ld x)
{
	while(x < -PI) x += 2 * PI;
	while(x >= PI) x -= 2 * PI;
	return x;
}

int N;
ld D;
pdd pt[MAXN];

int calc()
{
	int ans = 0;

	for(int i=0; i<N; i++)
	{
		int cur = 0;
		vector<pdi> event;
		for(int j=0; j<N; j++)
		{
			if(j == i) continue;
			pdd dp = pt[j] - pt[i];
			ld th = theta(dp);
			ld lb = reg(th - PI/2 - EPS), rb = reg(th + PI/2 + EPS);
			if(lb > rb)
				cur++;
			event.PB({lb, 1});
			event.PB({rb, -1});

			ld r = abs(dp);
			if(r > 2*D + EPS)
			{
				ld phi = acosl(2*D / r);
				lb = reg(th - phi + EPS), rb = reg(th + phi - EPS);
				if(lb > rb)
					cur--;
				event.PB({lb, -1});
				event.PB({rb, 1});
			}
		}
		sort(ALL(event));

//		cout<<cur<<endl;
//		cout<<event<<endl;

		ans = max(ans, cur);
		for(auto p: event)
		{
			cur += p.S;
			ans = max(ans, cur);
		}
	}

	return ans+1;
}

int main() {
	IOS;
	FILEIO("statistics");

	cin>>N>>D;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	int ans = calc();
	cout<<ans<<endl;

	return 0;
}

