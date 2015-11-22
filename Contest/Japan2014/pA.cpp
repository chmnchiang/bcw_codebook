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

const int MXN = 16;
const int MX = 1 << 16;

int N, M;
int ip, a, b;
int vst[MXN], dis[MXN];

void prt(int x) {
	for (int i=0; i<N; i++)
		if (x & (1 << i)) putchar('1');
		else putchar('0');

	puts("");
}
int go(int st, int ed) {
	vector<int> v1, v2;
	for (int i=0; i<N; i++) {
		if (st & (1<<i)) v1.PB(i);
		if (ed & (1<<i)) v2.PB(i);
	}
	if (SZ(v1) != SZ(v2)) return 1029384756;
	int ret = 0;
	for (int i=0; i<SZ(v1); i++) {
		ret += abs(v1[i] - v2[i]);
	}
	return ret;

}


int main() {
	IOS;
	cin >> N >> M;
	ip = a = b = 0;
	for (int i=0, v; i<N; i++) {
		cin >> v;
		if (v) {
			ip |= (1 << i);
		}
	}
	for (int i=0, v, c=0; i<M; i++) {
		cin >> v;
		for (int j=0; j<v; j++) {
			if (i & 1) {
				a |= 1 << (c + j);
			} else {
				b |= 1 << (c + j);
			}
		}
		c += v;
	}
	cout << min(go(ip, a), go(ip, b)) << endl;

    return 0;
}

