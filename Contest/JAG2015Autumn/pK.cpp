#include<bits/stdc++.h>
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

const int MXN = 1005;
const int MXK = 54;
const int INF = 1029384756;

int N, K, ip[MXN];
int dp[MXK][MXN][MXN];
int bk[MXK][MXN][MXN];


int go(int l, int r, int k) {
	if (l == r) return 0;
	if (r-l+1 > (1LL << k)) return INF;
	if (r-l == 1) {
		return ip[r] - ip[l];
	}
	int &ret = dp[k][l][r];
	if (ret != -1) return ret;
	ret = INF;
	go(l, r-1, k);
	go(l+1, r, k);
	int ll = bk[k][l][r-1];
	int rr = bk[k][l+1][r];
	if (ll == -1) ll = l;
	if (rr == -1) rr = r-1;
	/*
	if (r - l <= k) {
		ll = l;
		rr = r-1;
	}
	*/
	for (int m = ll; m<=rr; m++) {
		int c = go(l, m, k-1) + go(m+1,r, k-1) + ip[r] - ip[m];
		if (ret > c) {
			ret = c;
			bk[k][l][r] = m;
		}
	}
	return ret;
}


int main() {
    IOS;
	while (cin >> N >> K) {
		for (int i=0; i<N; i++)
			cin >> ip[i];
		sort(ip, ip+N);
		FMO(dp);
		FMO(bk);

		cout << go(0, N-1, K) << endl;
	}

	return 0;
}

