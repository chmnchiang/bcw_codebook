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
int N, nxt[MX], vst[MX];

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> N;
		for (int i=1; i<=N; i++) {
			cin >> nxt[i];
			vst[i] = 0;
		}
		int ans = 0;
		for (int i=1; i<=N; i++) {
			if (vst[i]) continue;
			vst[i] = 1;
			for (int j=nxt[i]; !vst[j]; j = nxt[j]) {
				vst[j] = 1;
			}
			ans++;
		}
		cout << ans << "\n";
	}

    return 0;
}

