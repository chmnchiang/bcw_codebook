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


const int MX = 333;
using p3d = array<double, 3>;
vector<p3d> ip;
double A, B;

double tr(double x) {
	double res = 0.0;
	res += x * B;
	for (auto p: ip) {
		double zz = (p[0] - x * p[2]) / p[1];
		if (zz >= 0) {
			res += zz * A;
		}
	}
	return res;
}

int main() {
	FILEIO("academy");

	int N;
	cout << fixed << setprecision(20);
	cin>>N>>A>>B;
	ip.resize(N);
	vector<double> tv;
	for (int i=0; i<N; i++) {
		double p, q, s;
		cin >> p >> q >> s;
		ip[i] = {p, q, s};
		tv.PB(p/s);
	}

	tv.PB(0);

	double ans = 1e10;
	double av = 0;
	for (auto x: tv) {
		auto res = tr(x);
		if (res < ans) {
			ans = res;
			av = x;
		}
	}
	

	cout << tr(av) << endl;
	cout << av << endl;

	for (int i=0; i<N; i++) {
		double z = ip[i][0] - ip[i][2] * av;
		if (z >= 0.0) {
			double zz = z / ip[i][1];
			cout << zz << ' ';
		} else {
			cout << 0.0 << endl;
		}
		
	}



    return 0;
}

