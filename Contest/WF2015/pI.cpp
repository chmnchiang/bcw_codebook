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


const int MX = 102300;
int N;
double W, Vth, Vme, T1, T2;;
using pdd=pair<double, double>;
vector<pdd> ship[MX];
using pdi = pair<double, int>;
vector<pdi> uni;

int main() {
	IOS;
	cin>>N>>W>>Vth>>Vme>>T1>>T2;
	for (int i=0; i<N; i++) {
		string s; int t;
		cin >> s >> t;
	
		for (int j=0; j<t; j++) {
			double l, x; cin >> l >> x;
			if (s == "E") x = -x;
			ship[i].PB({x, x+l});
		}
		sort(ALL(ship[i]));
	}
	const double INF = 1e9;
	const double EPS = 1e-9;

	for (int i=0; i<N; i++) {
		double ts = W / Vme * i;
		double dt = W / Vme;

		double ls = -INF;

		for (auto p: ship[i]) {
			double t1 = max(p.F / Vth - ts, 0.0);
			double t2 = p.S / Vth - ts;

			double a = max(ls, T1), b = min(t1-dt, T2);
			if (b > a+EPS) {
				uni.PB({a, 1});
				uni.PB({b, -1});
			}
			
			ls = t2;
		}

		if (T2 > ls+EPS) {
			uni.PB({ls, 1});
			uni.PB({T2, -1});
		}
	}
	sort(ALL(uni));

//	cout << uni << endl;
	
	int s = 0;
	double lst = 0.0;
	double ans = 0.0;
	for (auto p: uni) {
		double nt = p.F;
		if (p.S == 1) {
			s += p.S;
			if (s == N) {
				lst = nt;
			}
		} else if (p.S == -1) {
			if (s == N) {
				ans = max(ans, nt - lst);
			}
			s += p.S;
		}
	}

	cout << fixed << setprecision(10) << ans << endl;


	return 0;
}

