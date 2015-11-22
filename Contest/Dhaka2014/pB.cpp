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

int main() {
	IOS;
	int T; cin >> T;
	for (int cas=1; cas<=T; cas++) {
		i64 A, B; cin >> A >> B;
		i64 a1 = A, a2 = A;
		for (int i=0; i<63; i++) {
			i64 f = (1LL<<i);
			i64 g = f - 1;
			if (f & A) {
				a1 |= f;
				i64 ap = A ^ f;
				ap &= ~g;
				ap += (f << 1);
				if (ap <= B) a2 ^= f;
			} else {
				i64 ap = A^f;
				ap &= ~g;
				if (ap <= B) a1 ^= f;
			}
		}
		cout << "Case " << cas << ": " << a1 << ' ' << a2 << '\n';
	}


    return 0;
}

