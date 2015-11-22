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

long long a, b;

int main() {
	cin >> a >> b;
	if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
		cout << a - b << endl;
	} else {
		cout << a + b << endl;
	}
	return 0;
}

