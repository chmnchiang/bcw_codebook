#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!
//

const int INF = 2147400000;

int N;

int f(int a, int b){

	int alp = (a + 1) / 3;
	if(b >= alp * 3) return 2 * alp;
	else{
		return b / 3 * 2 + 1;
	}
}

int main(){
	FILEIO("knights");

	IOS;

	while (1){
		cin >> N;
		if (!N) return 0;

		int ans = INF;

		for (int i = 0; i < N; i++){
			
			int a, b;
			cin >> a >> b;

			ans = min(f(a, b), ans);
		}

		if(ans & 1) cout << "Andrew";
		else cout << "Peter";

		cout << " wins the game" << endl;
	}

	return 0;
}
