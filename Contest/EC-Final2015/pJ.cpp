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


using pdd=pair<double, double>;
int T;
int N;
vector<pdd> ip;

double sumsq(double x, double y) {
	return x*x+y*y;
}

double getd(pdd p) {
	return min(sumsq(p.F/2, p.S), sumsq(p.F, p.S/2));
}

const double INF = 1e15;
const double EPS = 1e-12;
bool test(double r) {
	double rr = r*r;
	double lm = 0, rm = 0.5;
	for (int i=0; i<N; i++) {
		int n = i/2 + 1;
		double dd = getd(ip[i]);
		if (dd > rr) return false;
		double x = sqrt(rr-dd);
		//cout << x << endl;
		if (i%2 == 0) {
			lm = max(lm, -x + n);
			rm = min(rm, x + n);
		} else {
			lm = max(lm, -x - n);
			rm = min(rm, x - n);
		}
		//cout << lm << ' ' << rm << endl;
	}
	return lm < rm + EPS;
}

double calc() {
	sort(ALL(ip), [](pdd p1, pdd p2) { return getd(p1) > getd(p2); });
	//test(3.0);

	double l = 0, r = 1e8;
	for (int _=0; _<60; _++) {
		double md = (l+r)/2;
		if (test(md)) r = md;
		else l = md;
	}
	return (l+r)/2;
}

int main() {
	IOS;
	cin>>T;
	cout << fixed << setprecision(10);
	for (int cas=1; cas<=T; cas++) {
		cin>>N;
		ip.resize(N);
		for (int i=0; i<N; i++)cin>>ip[i].F>>ip[i].S;

		cout << "Case #" << cas << ": " << calc() << endl;
	}

	return 0;
}

