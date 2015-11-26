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

int N;
typedef vector<int> vint;
vint ip;
const int MX = 123;

vint& operator << (vint &v, int a) {
	v.PB(a);
	return v;
}

bool us[2][MX];
int mem[2][MX];
int dp(int p, int n) {
	if (n == N) return 0;
	if (us[p][n]) return mem[p][n];
	us[p][n] = 1;

	int ans = ip[n]-dp(1-p, n+1);
	
	if (ip[n] >= 4) {
		ans = max(ans, ip[n] - 8 + dp(p, n+1));
	}
	return mem[p][n] = ans;
}

int32_t main() {
    FILEIO("diamonds");

	cin >> N;
	int sm = 0;
	for (int i=0; i<N; i++) {
		int a; cin >> a;
		ip << a;
		sm += a;
	}

	sort(ALL(ip));

	int df = dp(1, 0);
	int a1 = (sm-df) / 2, a2 = (sm+df)/2;
	cout << a1 << ' ' << a2 << endl;

    return 0;
}

