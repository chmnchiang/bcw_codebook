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

const int MX = 1005;

int isp[MX];
vector<int> p,ans[MX];

int main() {
	IOS;
	REP1(i,2,1000) {
		int is = 1;
		REP1(j,2,i-1) {
			if (i % j == 0) {
				is = 0;
				break;
			}
		}
		if (is) {
			isp[i] = 1;
			p.PB(i);
		}
	}
	int T;
	cin >> T;
	while (T--) {
		int N;
		cin >> N;
		if (ans[N].empty()) {
			for (auto i:p) {
				for (auto j:p) {
					if (i + j > N) break;
					if (isp[N-i-j]) {
						ans[N].PB(i);
						ans[N].PB(j);
						ans[N].PB(N-i-j);
						sort(ALL(ans[N]));
						break;
					}
				}
				if (!ans[N].empty()) break; 
			}
		}
		cout << ans[N][0] << " " << ans[N][1] << " " << ans[N][2] << "\n";
	}


    return 0;
}


