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

int N;
int main(){
	IOS;
	FILEIO("jubilee");
  while(cin >> N and N) {

    if(N == 3) {
      cout << 1 << endl;
      cout << "1 1 1\n1 1 1" << endl;
    } else if (N == 4) {
      cout << 2 << endl;
      cout << "1 1 1 2" << endl;
      cout << "1 2 1 1" << endl;
    } else if (N == 5) {
      cout << 2 << endl;
      cout << "1 1 1 2 2" << endl;
      cout << "1 2 1 1 1" << endl;
    } else if (N == 6) {
      cout << 2 << endl;
      cout << "1 1 1 2 2 2" << endl;
      cout << "1 2 1 1 2 1" << endl;
    } else {
      cout << 3 << endl;
      for(int i=0; i<N; i++) {
        cout << (i&1?1:2) << (i==N-1?"\n":" ");
      }
      for(int i=0; i<N; i++) cout << 3 << (i==N-1?"\n":" ");
    }
  }

	return 0;
}

