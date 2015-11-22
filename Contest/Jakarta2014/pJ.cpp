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

typedef long long i64;
typedef pair<i64, i64> pii;
const int MX = 1020102;
int N, M;
string ip;
i64 he[MX], hs[MX], cs[MX], up[MX];
deque<pii> dq;

int main() {
	IOS;
	int T; cin >> T;

	for (int cas=1; cas<=T; cas++) {
		cin >> N >> M;
		cin >> ip;
		
		for (int i=0; i<N; i++) {
			he[i+1] = (ip[i] == '/' ? 1 :
					   ip[i] == '\\' ? -1 : 0);
			cs[i+1] = ((ip[i] == '/' or ip[i] == '\\') ?
					   1 : 0);
			up[i+1] = ((ip[i] == '/') ?
					   1 : 0);
		}

		for (int i=1; i<=N; i++) {
			he[i] += he[i-1];
			hs[i] = hs[i-1] + he[i];
			cs[i] += cs[i-1];
			up[i] += up[i-1];
		}

		dq.clear();
		dq.PB({0, 0});

		i64 ans = 5e18;
		for (int i=1; i<=N; i++) {
			while (not dq.empty()) {
				auto x = dq.front();
				if (x.F < i - M) dq.pop_front();
				else break;
			}
			while (not dq.empty()) {
				auto x = dq.back();
				if (x.S >= he[i]) dq.pop_back();
				else break;
			}
			dq.PB({i, he[i]});
			if (i < M) continue;

			i64 mn = dq.front().S;
			i64 cost = cs[i] - cs[i-M] + 2LL * (hs[i] - hs[i-M] - up[i] + up[i-M]) -
				2 * mn * M;
			//cout << i << ' ' << cost << endl;

			//cout << hs[i]-hs[i-M] << ' ' << mn*M << endl;
			//cout << cs[i] - cs[i-M] << endl;
			ans = min(ans, cost);
		}
		cout << "Case #" << cas << ": " << (ans/2) << "." << (ans%2==0 ? 0 : 5) << endl;
	}

    return 0;
}

