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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MXN = 100005;
const int LOG = 17;

int N,W,ip[MXN];
int rmq[LOG][MXN];

inline int query(int l, int r) {
	int len = (r - l) + 1;
	int i=31-__builtin_clz(len);
	int res = max(rmq[i][l], rmq[i][r-(1<<i)+1]);
	return res;
}
bool check(int len) {
	long long sum = 0;
	for (int i=0; i<N; i+=len) {
		sum += query(i, min(i+len-1,N-1)) + 1;
	}
	sum--;
	return sum <= W;
}
int main() {
	IOS;
	cin >> N >> W;
	REP(i,N) {
		cin >> ip[i];
		rmq[0][i] = ip[i];
	}
	REP1(i,1,LOG-1) {
		REP(j,N) {
			if (j + (1<<i) - 1 >= N) break;
			rmq[i][j] = max(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
		}
	}
	int ans = 0;
	REP1(i,1,N) {
		if (check(i)) {
			ans = i;
			break;
		}
	}
	cout << ans << endl;
	
	
	return 0;
}

