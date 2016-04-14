#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
    return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
    s<<"[ ";
    for (auto it : c) s << it << " ";
    s<<"]";
    return s;
}
// Let's Fight!

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); ((i) += ((a) < (b) ? 1 : -1)))

struct Li {
	vector<int> vl;
	void insert(int a) {
		vl.PB(a);
	}
	int make() {
		sort(ALL(vl));
		vl.resize(unique(ALL(vl)) - vl.begin());
		return SZ(vl);
	}
	int qry(int a) {
		return lower_bound(ALL(vl), a) - vl.begin();
	}
}li;

using vi=vector<int>;
int N, M;
vector<vi> ip;
const int MX = 66;

const int INF = 1029384756;
vector<vi> op;
void deinit() {
	ip.clear();
	op.clear();
	li = Li();
}
int calc() {
	//cout << M << endl;
	op.resize(M);
	for (int i=0; i<N; i++) {
		for (auto x: ip[i]) {
			op[x].PB(i);
		}
	}
	loop (i, 0, M) {
		sort(ALL(op[i]));
		op[i].resize(unique(ALL(op[i])) - op[i].begin());
	}

	int dis[2][MX] = {};
	fill(dis[0], dis[0]+N+1, INF);
	dis[0][N] = 0;
	for (int i=0; i<M; i++) {
		int my = (i+1)%2, he = i%2;
		fill(dis[my], dis[my]+N+1, INF);
		//cout << "SZ = " << SZ(op[i]) << endl;

		if (SZ(op[i]) == 1) {
			int x = op[i][0];
			for (int j=0; j<=N; j++) {
				dis[my][x] = min(dis[my][x], dis[he][j] + (x != j));
			}
		} else {
		
			for (int j=0; j<=N; j++) {
				for (auto x: op[i]) {
					int cs = (x == j ? SZ(op[i]) - 1 : SZ(op[i]));
					for (auto y: op[i]) {
						if (x == y) continue;
						dis[my][y] = min(dis[my][y], dis[he][j]+cs);
					}
				}
			}

		}

		if (i == M-1) {
			int ans = INF;
			for (int j=0; j<=N; j++) {
				ans = min(ans, dis[my][j]);
			}
			return ans-N+ans-1;
		}
	}
}

int main() {
	IOS;
	int cas=0;
	while (cin>>N) {
		ip.resize(N);
		for (int i=0; i<N; i++) {
			int c; cin >> c;
			loop(j, 0, c) {
				int t; cin >> t;
				li.insert(t);
				ip[i].PB(t);
			}
		}
		M = li.make();
		loop (i, 0, N) {
			for (auto &x: ip[i]) {
				x = li.qry(x);
			}
		}
		cas++;
		cout << "Case " << cas << ": " << calc() << endl;
		deinit();
	}


	return 0;
}

