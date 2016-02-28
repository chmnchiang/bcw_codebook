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

//const int MX = 101234567;
const int MX = 1e17;
//int mem[MX];
//bool us[MX];
int f(int a) {
	assert(a < MX);
	if (a == 1) return 0;
	//if (us[a]) return mem[a];

	//us[a] = true;
	int ans = 0;
	if (a%2) {
		int t = (a+1)/2;
		int z = f(t*3-1);
		ans = z + t*2;
	} else {
		ans = a + f(a/2);
	}
	return ans;
	//return mem[a] = ans;
}

int32_t main() {
	IOS;

	/*
	for (int i=1; i<=1000000; i++) {
		//cout << i << endl;
		f(i);
	}*/
	
	int N; cin >> N;
	cout << f(N) << endl;
	return 0;
}

