//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

const int MX = 101010;
int a[MX], b[MX];
int N;
int main(){
	FILEIO("analogous");
	IOS;
	while (~scanf("%d", &N) && N){
		if((N-1)&N) {
			cout << "No" << endl;
		} else {
			a[0] = 1; a[1] = 4;
			b[0] = 2; b[1] = 3;

			for(int k=2; k<N; k+=k) {
				for(int i=0; i<k; i++) {
					a[k+i] = b[i] + k + k;
					b[k+i] = a[i] + k + k;
				}
			}

			cout << "Yes" << endl;
			for(int i=0; i<N; i++) cout << a[i] << (i==N-1?"\n":" ");
			for(int i=0; i<N; i++) cout << b[i] << (i==N-1?"":" ");
			cout << endl;
		}
	}
	return 0;
}

