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


typedef long long ll;
const int MX = 100000;

ll N;
int isp[MX];
vector<int> p;

int checkp(ll x) {
	if (x < MX) return isp[x];
	for (auto i:p) if (x % i == 0) return 0;
	return 1;
}
int main() {
	IOS;

	fill(isp,isp+MX,1);
	isp[0] = isp[1] = 0;
	for (int i=2; i<MX; i++) {
		if (isp[i]) {
			for (int j=i+i; j<MX; j+=i) {
				isp[j] = 0;
			}
			p.PB(i);
		}
	}

	cin >> N;
	if (N <= 10) {
		ll x = 1;
		REP1(i,1,N) x = x * i;
		if (x % (N * N)) cout << "NO" << endl;
		else cout << "YES" << endl;
	} else {
		int x = checkp(N);
		if (x) cout << "NO" << endl;
		else cout << "YES" << endl;
	}

	return 0;
}
