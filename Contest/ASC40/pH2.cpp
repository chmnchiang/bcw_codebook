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

string ans[] = {"1", "2", "5", "14", "42", "165", "714", "3094", "14858", "79534", "447051", "2714690", "17395070", "114371070", "783152070", "5708587335", "43848093003", "342444658094", "2803119896185", "23619540863730", "201813981102615", "1793779293633437", "16342050964565645", "154170926013430326", "1518409177581024365", "15259825120722837478", "154870329715038713659", "1601991088154989174258", "16725278985898957454695", "177792163538134124432895"};
int main(){
  FILEIO("handsome");
  int N, T = 0;
  while (cin >> N && N){
    T++;
    cout << "Case #" << T << ": " << ans[N-1] << endl;
  }
	return 0;
}

