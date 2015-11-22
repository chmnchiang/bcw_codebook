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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

//#define double long double
int main() {
	int N; cin >> N;

	double best = 0.0;
	int ans = 0;

	for (int i=1; i<N; i++) {
		double t = 0.0;
		int a1 = i, a2 = N-i;
		for (int j=1; j<=N-i; j++) {
			double q = 1.0;
			for (int k=0; k<j; k++) {
				q *= (a2 - k);
				q /= (N - k);
				//cout << (a2-k) << ' ' << N-k << ' ' << k+1 << endl;
			}
			q /= j;
			q *= a1;
			q /= (N-j);
			//cout << (a1) << ' ' << N-j <<  endl;
			t += q;
			//cout << q << endl;
		}
		if (t > best) {
			best = t;
			ans = i;
		}
		//cout << "Tkj " << t << endl;
	}
	cout << ans << endl;
	return 0;
}

