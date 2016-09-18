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

const int MXN = 100005;

int N,K,low,fa[MXN],sz[MXN];
int step,line[MXN*2],st[MXN],ed[MXN];
int eid[MXN];
int inq[MXN];
int vst[MXN];
vector<int> E[MXN];
int tree[MXN*8];

void DFS(int u, int f) {
	st[u] = step;
	line[step++] = u;
	sz[u] = 1;
	for (auto v:E[u]) {
		DFS(v,u);
		sz[u] += sz[v];
	}
	ed[u] = step;
	line[step++] = u;
}
void DFS2(int u) {
	vst[u] = 1;
	for (auto v:E[u]) if (!vst[v]) DFS2(v);
}
void update(int l, int r, int fn, int v, int id) {
	if (l == r) {
		tree[id] += v;
		return;
	}
	int m = (l+r)/2, lc = id*2, rc = id*2+1;
	if (fn <= m) update(l,m,fn,v,lc);
	else update(m+1,r,fn,v,rc);
	tree[id] = tree[lc]+tree[rc];
}
int query(int l, int r, int fl, int fr, int id) {
	if (l == fl and r == fr) return tree[id];
	int m = (l+r)/2, lc = id*2, rc = id*2+1;
	if (fr <= m) return query(l,m,fl,fr,lc);
	if (m < fl) return query(m+1,r,fl,fr,rc);
	return query(l,m,fl,m,lc) + query(m+1,r,m+1,fr,rc);
}
int main() {
	IOS;
	FILEIO("tree");
	cin >> N >> K;
	low = (K+1)/2;
	REP1(i,1,N-1) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
		eid[v] = i;
		fa[v] = u;
	}
	step = 0;
	DFS(1,1);
	queue<int> que;
	REP1(i,1,N) {
		if (sz[i] <= K) {
			que.push(i);
			inq[i] = 1;
		}
	}
//	cout << "LOW = " << low << endl;
	vector<int> ans;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (u == 1) {
			break;
		}
		if (vst[u]) continue;
		int f = fa[u];
		int s = sz[u] - query(0,step,st[u],ed[u],1);
		assert(s <= K);
		if (s >= low) {
			ans.PB(eid[u]);
			update(0,step,st[u],s,1);
			DFS2(u);
		}
		if (!inq[f] and sz[f]-query(0,step,st[f],ed[f],1) <= K) {
			que.push(f);
			inq[f] = 1;
		}
	}
	
	cout << SZ(ans) << endl;
	for (auto it:ans) cout << it << " ";
	cout << endl;
	assert(SZ(ans) <= (2*N+K-1)/K);

	return 0;
}

