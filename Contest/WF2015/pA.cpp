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


typedef long double ld;

int P,A,B,C,D,N;
ld ip[1000005];

inline ld f(int k) {
	return P * (sinl(A*k+B) + cosl(C*k+D) + 2);
}

int main() {
	IOS;
	cin >> P >> A >> B >> C >> D >> N;
	REP1(i,1,N) ip[i] = f(i);
	ld ans = 0;
	ld mn = ip[N];
	for (int i=N; i>=1; i--) {
		mn = min(mn, ip[i]);
		ans = max(ans, ip[i]-mn);
	}

	cout << fixed << setprecision(10) << ans << endl;

	return 0;
}

