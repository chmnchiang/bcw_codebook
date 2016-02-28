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

#define int long long
int N;

int check(int a) {
	int t = a;
	int s = 1 + a;
	int ans = 0;
	while (s <= N) {
		if (N % s == 0) {
			ans ++;
		}

		t *= a;
		s += t;
	}

	return ans;
}

int32_t main() {
	IOS;
	
	cin >> N;

	int s = 0;
	for (int i=2; i<N; i++) {
		s += check(i);
	}

	for (int i=2; i<=N; i++) {
		if (N % i == 0) {
			s ++;
		}
	}

	cout << s << endl;
	
	return 0;
}

