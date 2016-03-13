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

#define int long long

int L,N,K;

inline int alpha(int i) {
	return 2 * (i / K) - 1 + min(i % K, 2LL);
}

int32_t main() {
	IOS;
	cin >> L >> N >> K;

/*	REP1(i,1,N) {
		cout << alpha(i) << " ";
	}
	cout<<endl;*/

	int ans = N;
	int Z = 100;
	REP(_,L) {
		int a = alpha(ans);
		if (a == 0) ans = 0;
		if (ans <= 0) {
			ans = 0;
			break;
		}
		int nans = ans - a * Z;
		if(nans > a+a+2 && alpha(nans) == a && L-_ > Z+3)
		{
			ans = nans;
			_ += Z-1;
		}
		else
		{
			ans -= a;
		}
	}
	
	cout << ans << endl;

	return 0;
}

