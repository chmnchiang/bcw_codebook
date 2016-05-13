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


const int MX = 10000005;

int isp[MX];

int main() {
	IOS;
	fill(isp,isp+MX,1);
	isp[0] = isp[1] = 0;
	for (int i=2; i<MX; i++) {
		if (isp[i]) {
			for (long long j = 1LL*i*i; j<MX; j+=i) {
				isp[j] = 0;
			}
		}
	}

	int K;
	cin >> K;
	int cnt = 0;
	REP(i,MX) {
		if (isp[i]) {
			string s = to_string(i);
			reverse(ALL(s));
			int x = stoi(s);
			if (x == i or x > MX or !isp[x]) continue;
			cnt++;
			if (cnt == K) {
				cout << i << endl;
				return 0;
			}
			
		}
	}
	cout << -1 << endl;
	

	return 0;
}

