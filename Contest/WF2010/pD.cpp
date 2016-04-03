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

#define loop(i, a, b) for (auto (i)=(a); (i)!=(b); (i) += ((b) < (a) ? -1 : 1))

template<typename T>
using Vec = vector<T>;
using pii = pair<int,int>;
int N;
const int MX = 1111;
int vx[MX], vy[MX];
Vec<int> el[MX];
bool vt[MX];
const int INF = 1029384756;

pii dfs(int u, int fa=-1) {
	Vec<pii> vec;
	for (auto v: el[u]) {
		if (v == fa) continue;
		vec.PB(dfs(v, u));
	}
	sort(ALL(vec), [](pii p1, pii p2) { return p1.F-p1.S > p2.F-p2.S; });
	int ret = vx[u], ys=vy[u];
	for (auto p:vec) {
		ret=max(ret, ys+p.F);
		ys += p.S;
	}
	ret = max(ret, ys);
	return {ret, ys};
}

void deinit() {
	loop (i, 0, N+5) el[i].clear();
}

int calc() {
	int ans=INF;
	loop(i, 1, N+1) {
		fill(vt, vt+N+5, 0);
		ans = min(ans, dfs(i).F);
	}
	return ans;
}

int main() {
	IOS;

	int cas=0;
	while (true) {
		cin >> N;
		if(!N) break;

		loop(i, 1, N+1) {
			int a, b, c;cin>>a>>b>>c;
			vx[i] = a;
			vy[i] = b+c;
		}
		loop(i, 0, N-1) {
			int u, v;cin >> u >> v;
			el[u].PB(v); el[v].PB(u);
		}
		cas++;
		cout <<"Case " << cas << ": " << calc() << endl;
		deinit();
	}


	return 0;
}

