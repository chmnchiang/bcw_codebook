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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

int N, M;

void output(int x, int n) {
	vector<int> vec;
	for (int j=0; j<n; j++) {
		vec.PB(x%2);
		x /= 2;
	}
	for (int j=n-1; j>=0; j--) {
		cout << vec[j];
	}
	cout << "\n";

}
int main() {
	IOS;
	FILEIO("binary");
	cin >> M;
	for (int i=0; (1<<i) < M; i++) {
		N = i;
	}
	N++;
	int two = (1<<N) - M;
	int p = 0;
	for (int i=0; i<two; i++, p++) {
		output(p, N-1);
	}
	p = p * 2;
	for (int i=two; i<M; i++, p++) {
		output(p, N);
	}

	return 0;
}
