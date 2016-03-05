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

#define y0 asdfasdf

const double PI = acos(-1);

double W, H, xc, yc, x0, y0, alpha, s, ll, tt;

void calc()
{
	W *= s;
	H *= s;
	xc *= s;
	yc *= s;
	xc -= W/2;
	yc -= H/2;
	double a = alpha * PI / 180;

	double xx = cos(a) * xc - sin(a) * yc;
	double yy = sin(a) * xc + cos(a) * yc;
	ll = x0 - xx - W/2;
	tt = y0 - yy - H/2;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>W>>H>>xc>>yc>>x0>>y0>>alpha>>s;
		calc();
		cout<<fixed<<setprecision(1);
		cout<<".item"<<t<<" { width: "<<W<<"px; height: "<<H<<"px; left: "<<ll<<"px; top: "<<tt<<"px; transform: rotate("<<alpha<<"deg); }"<<endl;
	}


	return 0;
}
