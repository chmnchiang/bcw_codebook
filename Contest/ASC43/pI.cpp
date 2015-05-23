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

const int MX = 10005;

int N;
int nxt[MX];
LL cost[MX];
pair<LL,LL> ip[MX];

int main(){
	FILEIO("iq");
	IOS;
	while (cin >> N && N){
		for (int i=0; i<N; i++){
			cin >> ip[i].F;
			ip[i].S = i + 1;
		}
		sort(ip,ip+N);
		cost[N] = 0;
		for (int i=N-1; i>=0; i--){
			cost[i] = 1ll << 62;
			for (int j=i; j<N; j++){
				LL v = cost[j+1] + (LL)(N-i) * ip[j].F;
				if (v < cost[i]){
					cost[i] = v;
					nxt[i] = j+1;
				}
			}
		}
		vector< vector<int> > ans;
		cout << cost[0] << "\n";
		int pos = 0;
		while (pos < N){
			vector<int> vec;
			int nx = nxt[pos];
			for (int i=pos; i<nx; i++){
				vec.PB(ip[i].S);
			}
			ans.PB(vec);
			pos = nx;
		}
		cout << ans.size() << endl;
		for (auto it : ans){
			cout << it.size();
			sort(it.begin(), it.end());
			for (auto it2 : it)
				cout << " " << it2;
			cout << "\n";
		}
	}
	return 0;
}

