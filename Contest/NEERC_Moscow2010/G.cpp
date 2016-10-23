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


using ld = long double;

struct pdd : pair<double, double> {
	using pair<double, double>::pair;
	pdd operator + (const pdd &he) const { return {F+he.F, S+he.S}; }
	pdd operator - (const pdd &he) const { return {F-he.F, S-he.S}; }
	double operator * (const pdd &he) const { return F*he.F+S*he.S; }
	pdd operator * (double f) const { return {F*f, S*f}; }
};
pdd operator * (double f, const pdd &p) { return {p.F*f, p.S*f}; }

inline double abs(pdd p) {
	return hypot(p.F, p.S);
}

const double EPS = 1e-12;
vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
	ld d2 = (o1 - o2) * (o1 - o2);
	ld d = sqrtl(d2);
	if (d < abs(r1-r2)) return {}; 
	if (d > r1+r2) return {};
	pdd u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
	double z = (r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d);
	if (z < 0) return {};
	double A = sqrtl((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
	pdd v = A / (2*d2) * pdd(o1.S-o2.S, -o1.F+o2.F);
	return {u+v, u-v};
}

const int MXN = 2005;

int N;
pdd ip[MXN];
vector<pdd> vec[MXN];

int main() {
	IOS;
	cin >> N;

	REP(i,N) {
		cin >> ip[i].F >> ip[i].S;
		ip[i].S = ip[i].S / 12.0 * 7 * 24;
	}
	sort(ip,ip+N, [&](pdd a, pdd b) { return a.F-a.S < b.F-b.S; } );
//	sort(ip,ip+N);
	{
		int i = 0;
		while (true) {
			pdd lst = {ip[i].F-ip[i].S,0};
			while (i < N) {
				int best = -1;
				pdd jiao = {1e9,1e9};
				for (int j=i+1; j<N; j++) {
					vector<pdd> vv = interCircle({ip[i].F,0},ip[i].S,{ip[j].F,0},ip[j].S);
					if (SZ(vv) == 0) continue;
					pdd x = vv[0];
					if (x.S < 0) x = vv[1];
					if (x < jiao) {
						jiao = x;
						best = j;
					}
				}
				if (best == -1) {
					vec[i] = {lst, {ip[i].F+ip[i].S,0}};
					break;
				}
				vec[i] = {lst, jiao};
				lst = jiao;

				i = best;
			}
			ld x = 1e9;
			int best = -1;
			int bye = 1;
			for (int j=i+1; j<N; j++) {
				if (ip[j].F-ip[j].S > ip[i].F+ip[i].S) {
					if (x > ip[j].F-ip[j].S) {
						best = j;
						x = ip[j].F-ip[j].S;
					}
					bye = 0;
					break;
				}
			}
			if (bye) break;
			i = best;
		}
	}
	/*
	REP(i,N) {
		cout << i << " " << vec[i] << endl;
	}
	*/

	const double PI = acos(-1);
	double ans = 0;

	for (int i=0; i<N; i++) {
		int sz = SZ(vec[i]);
		if (!sz) continue;
		assert(sz == 2);
		ld l = vec[i][0].F, r = vec[i][1].F;
		if (r <= 0) continue;
		l = max(l, (ld)0.0);

		ld radi = ip[i].S;
		ld ar = 2 * PI * radi * radi;
		double z = abs(r - l);
		ar *= z / radi;
		ans += ar;
	}
	cout << fixed << setprecision(10) << ans << endl;

	return 0;
}
