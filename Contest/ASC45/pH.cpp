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

typedef long long LL;
typedef pair<int,int> pii;
const int MX = 514;

int N;
pii pt[MX];
vector<pii> seg[MX];
vector<int> ans;
int dp[MX][MX];
int choose[MX][MX];

int go(int l, int r){
	if (l == r) return 1;
	if (dp[l][r] != -1) return dp[l][r];
	int ret1 = go(l+1,r);
	int ret2 = 1;
	for (auto it : seg[l]){
		if (it.F > r) break;
		ret2 += go(it.F, min(it.S,r));
	}
	if (ret1 > ret2){
		choose[l][r] = 0;
	} else {
		choose[l][r] = 1;
	}
	return dp[l][r] = max(ret1, ret2);
}
void get_answer(int l, int r){
	if (l == r){
		ans.PB(l);
		return ;
	}
	if (!choose[l][r]){
		get_answer(l+1,r);
	} else {
		ans.PB(l);
		for (auto it : seg[l]){
			if (it.F > r) break;
			get_answer(it.F, min(it.S,r));
		}
	}
}
int main(){
	FILEIO("hide");
	while (~scanf("%d", &N) && N){
		for (int i=0; i<N; i++){
			scanf("%d%d", &pt[i].F, &pt[i].S);
			seg[i].clear();
		}
		pt[N] = pt[0];
		for (int i=1; i<N; i++){
			vector<int> canSee;
			canSee.PB(i+1);
			for (int j=i+2; j<=N; j++){
				pii v = pt[canSee.back()];
				if ((LL)(v.F-pt[i].F)*(pt[j].S-pt[i].S) >= (LL)(pt[j].F-pt[i].F)*(v.S-pt[i].S))
					canSee.PB(j);
			}
			for (int j=1; j<(int)canSee.size(); j++){
				if (canSee[j] != canSee[j-1]+1)
					seg[i].PB(MP(canSee[j-1]+1,canSee[j]-1));
			}
		}
		FMO(dp);
		go(1,N-1);
		ans.clear();
		get_answer(1,N-1);
		sort(ans.begin(),ans.end());
		printf("%d\n", (int)ans.size());
		for (int i=0; i<(int)ans.size(); i++)
			printf("%d%c", ans[i]+1, i==(int)ans.size()-1 ? '\n' : ' ');
	}
	return 0;
}

