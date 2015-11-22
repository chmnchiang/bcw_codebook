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

const int MX = 200;

int N, cnt[MX], sum[MX];

int go(int x) {
	return abs(4 * x - N);
}
int calc(int a, int b, int c) {
	int ret = go(sum[a]);
	ret += go(sum[b] - sum[a]);
	ret += go(sum[c] - sum[b]);
	ret += go(sum[160] - sum[c]);
	return ret;
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		cin >> N;
		FZ(cnt);
		for (int i=0, v; i<N; i++) {
			cin >> v;
			cnt[v]++;
		}
		sum[0] = cnt[0];
		for (int i=1; i<MX; i++)
			sum[i] = sum[i-1] + cnt[i];
		int A, B, C, cost;
		A = B = C = -1;
		cost = 1029384756;
		for (int i=0; i<160; i++) {
			for (int j=i+1; j<160; j++) {
				for (int k=j+1; k<160; k++) {
					int tmp = calc(i, j, k);
					if (tmp < cost) {
						cost = tmp;
						A = i;
						B = j;
						C = k;
					}
				}
			}
		}
		cout << "Case " << t << ": " << A << " " << B << " " << C << endl;
	}

    return 0;
}

