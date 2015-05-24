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
const int INF = 1029384756;

vector<int> pos[28];
int N, ip[MX], done[28];
char str[MX];
map<int,int> mp;

void output(int v){
	for (int i=0; i<26; i++){
		if (v & (1<<i))
			putchar('a' + i);
	}
}
int main(){
	IOS;
	FILEIO("jingles");
	int nT;
	cin >> nT;
	while (nT--){
		for (int i=0; i<27; i++)
			pos[i].clear();
		cin >> str;
		N = strlen(str);
		pos[27].PB(N);
		mp.clear();
		for (int i=0; i<N; i++){
			pos[ip[i]=(int)str[i]-'a'].PB(i);
		}
		for (int i=0; i<N; i++){
			FZ(done);
			done[ip[i]] = 1;
			int cur = 0;
			cur |= 1 << ip[i];
			mp[cur] = max(mp[cur],1);
			int p = i;
			while (p < N){
				int best = -1;
				int cost = INF;
				for (int j=0; j<27; j++){
					if (done[j]) continue;
					int tmp = lower_bound(pos[j].begin(), pos[j].end(), p) - pos[j].begin();
					if (tmp == (int)pos[j].size()) continue;
					if (cost > pos[j][tmp]){
						cost = pos[j][tmp];
						best = j;
					}
				}
				if (best == -1) break;
				done[best] = 1;
				mp[cur] = max(mp[cur], cost-i);
				cur |= 1 << best;
				p = cost;
			}
			mp[cur] = max(mp[cur], N-i);
		}
		int cnt = 0;
		long long ret = 0;
		for (auto it : mp){
			cnt++;
			ret += __builtin_popcount(it.F) * it.S;
		}
		cout << cnt << " " << ret << "\n";
	}

	return 0;
}

