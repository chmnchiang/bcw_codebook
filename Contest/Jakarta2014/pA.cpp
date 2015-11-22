#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MX = 123;
int N, K;
int djs[MX];

int ffa(int a) {
	return (djs[a] == a ? a : (djs[a] = ffa(djs[a])));
}

int main() {

	int T; cin >> T;
	for (int cas=1; cas<=T; cas++) {
		cin >> N >> K;
		for (int i=0; i<=N; i++) {
			djs[i] = i;
		}
		vector<int> ip;
		for (int i=0; i<N; i++) {
			int a; cin >> a;
			ip.PB(a);
		}

		int ans = N;
		for (int i=0; i<N; i++) {
			for (int j=0; j<i; j++) {
				int d = abs(ip[j] - ip[i]);
				if (d <= K) {
					int f1 = ffa(i), f2 = ffa(j);
					if (f1 != f2) {
						djs[f1] = f2;
						ans --;
					}
				}
			}
		}
		cout << "Case #" << cas << ": " << ans << endl;
	}

    return 0;
}


