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

const int MX = 100005;
typedef pair<int,int> pii;

int N,M,is[MX],ans[MX];
pii eg[MX],cost[MX];

int main(){
	FILEIO("flights");
	while (~scanf("%d%d", &N, &M) && N && M){
		for (int i=1; i<=N; i++){
			cost[i].S = i;
			cost[i].F = 0;
		}
		int c = 1;
		for (int i=1; i<=M; i++){
			scanf("%d%d", &eg[i].F, &eg[i].S);
			if (eg[i].F > eg[i].S) swap(eg[i].F, eg[i].S);
			if (eg[i].F == 1) is[eg[i].S] = i;
			else {
				ans[i] = c;
				cost[eg[i].F].F += c;
				cost[eg[i].S].F += c;
				c++;
			}
		}
		sort(cost+2,cost+1+N);
		for (int i=2; i<=N; i++){
			ans[is[cost[i].S]] = c++;
		}
		if (N == 2){
			puts("No");
		} else {
			puts("Yes");
			for (int i=1; i<=M; i++)
				printf("%d%c", ans[i], i==M ? '\n' : ' ');
		}
	}

	return 0;
}

