//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}
const int MX = 5432;
int N;
double A[MX], B[MX], C[MX], D[MX];
double dp[MX];

double tmux(double a, double b, double c, double d) {
	if(a+b<=d) return a+b;
	if(c+d<=b) return c+d;
	return (a*c+a*d+c*b) / (a+c);
}

int main(){
	FILEIO("braess")
	cin >> N;
	for(int i=1; i<=N; i++) {
		double a, b, c, d;
		cin >> a >> b >> c >> d;
#define _add(a,i,c) a[i] = a[i-1] + c
		_add(A,i,a);
		_add(B,i,b);
		_add(C,i,c);
		_add(D,i,d);
	}

	double ans = 0;
#define calc(a, b) tmux(A[b] - A[a], B[b] - B[a], C[b] - C[a], D[b] - D[a])
	cout << fixed << setprecision(10) << calc(0, N) << endl;
	for(int i=1; i<=N; i++) {
		ans += calc(i-1, i);
	}
	cout << fixed << setprecision(10) << ans << endl;

	dp[0] = 0;
	for(int i=1; i<=N; i++) {
		double nb = 1e12;
		for(int j=0; j<i; j++) {
			nb = min(nb, calc(j, i) + dp[j]);
		}
		dp[i] = nb;
	}
	cout << fixed << setprecision(10) << dp[N] << endl;

	dp[0] = 0;
	for(int i=1; i<=N; i++) {
		double nb = -1e12;
		for(int j=0; j<i; j++) {
			nb = max(nb, calc(j, i) + dp[j]);
		}
		dp[i] = nb;
	}
	cout << fixed << setprecision(10) << dp[N] << endl;

	
	return 0;
}

