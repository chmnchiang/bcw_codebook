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

const int MXN = 100005;
const int MXK = 105;
const int LOG = 18;

int N,K,ip[MXN];
int ns,seq[MXN];
int dp[MXK][MXN];
int dp2[MXK][MXN], choose[MXK][MXN];
int cnt[MXN];
int good[LOG][MXN];
vector<int> position[MXN];

int max_node(int k, int a, int b){
	if (a > b) swap(a,b);
	if (b > N) return a;
	return dp[k][a] >= dp[k][b] ? a : b;
}
void init(int k){
	for (int j=1; j<=N; j++)
		good[0][j] = j;
	for (int i=1; i<LOG; i++){
		for (int j=1; j+(1<<i)-1 <= N; j++)
			good[i][j] = max_node(k, good[i-1][j], good[i-1][j+(1<<(i-1))]);
	}
}
int query(int k, int l, int r){
	if (r < l) return 0;
	int len = r-l+1;
	int b = 0;
	for (int i=0; i<N; i++){
		if ((1 << i) > len) break;
		b = i;
	}
	return max_node(k, good[b][l], good[b][r-(1<<b)+1]);
}
int main(){
	FILEIO("funny");
	while (cin >> N >> K && N){
		ns = 0;
		for (int i=1; i<=N; i++){
			scanf("%d", &ip[i]);
			position[ns].clear();
			cnt[ns] = 0;
			seq[ns++] = ip[i];
		}
		sort(seq, seq+ns);
		ns = unique(seq, seq+ns) - seq;
		for (int i=1; i<=N; i++){
			ip[i] = lower_bound(seq, seq+ns, ip[i]) - seq;
			position[ip[i]].PB(i);
		}
		for (int i=1, ans=1; i<=N; i++){
			cnt[ip[i]]++;
			ans = max(ans,cnt[ip[i]]);
			dp[1][i] = ans;
		}
		
		for (int i=0; i<ns; i++){
			int j = 0;
			for (auto it : position[i])
				cnt[it] = j++;
		}
		for (int k=2; k<=K; k++){
			init(k-1);
			for (int i=1; i<=N; i++){
				if (cnt[i] == 0){
					choose[k-1][i] = query(k-1,1,i-1);
	//				for (int j=1; j<=i-1; j++)
		//				choose[k-1][i] = max_node(k-1, choose[k-1][i], j);
					dp2[k-1][i] = dp[k-1][choose[k-1][i]];
				} else {
					int x = ip[i];
					int pre = position[x][cnt[i]-1];
					choose[k-1][i] = query(k-1,pre,i-1);
			//		for (int j=1; j<=i-1; j++)
				//		choose[k-1][i] = max_node(k-1, choose[k-1][i], j);
					dp2[k-1][i] = dp[k-1][choose[k-1][i]] - (cnt[pre]+1);
					if (dp2[k-1][i] < dp2[k-1][pre]){
						dp2[k-1][i] = dp2[k-1][pre];
						choose[k-1][i] = choose[k-1][pre];
					}
				}
			}
			for (int i=k; i<=N; i++){
				dp[k][i] = cnt[i] + 1 + dp2[k-1][i];
			}
		}
		int best = K;
		for (int i=K; i<=N; i++)
			if (dp[K][i] > dp[K][best])
				best = i;
		printf("%d\n", dp[K][best]);
		vector<int> vec;
		for (int k=K, n=best; k>1; k--){
			n = choose[k-1][n];
			vec.PB(n);
		}
		sort(vec.begin(), vec.end());
		for (int i=0; i<K-1; i++)
			printf("%d%c", vec[i], i==K-2 ? '\n' : ' ');
	}
	return 0;
}

