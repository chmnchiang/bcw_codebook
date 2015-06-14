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

/* hack some non-reasonble solution */

int main(){
	puts("100000");
  int N = 100000;
  vector<int> vec;
  vec.PB((N-3)/3);
  vec.PB((N-3)/3);
  vec.PB((N-3) - (N-3)/3*2);
  puts("1 2");
  puts("2 3");
  int p = 4;
  for (int i=0; i<3; i++){
    for (int j=0; j<vec[i]; j++)
      printf("%d %d\n", i+1, p++);
  }
  return 0;
}

