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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!


typedef pair<int,int> pii;
const int MXN = 100005;
const int MEM = MXN * 30;


struct Node {
	int lc,rc;
	pii v;
	Node () {
		lc = rc = 0;
		v = {0,-1};
	}
	Node (pii _v) {
		lc = rc = 0;
		v = _v;
	}
}tree[MEM];

int nMem,rt;
int N,K,ip[MXN],dp[MXN],prv[MXN];

int get_node(pii v) {
	if (nMem >= MEM) while(1);
	tree[nMem] = Node(v);
	return nMem++;
}
int get_node() {
	if (nMem >= MEM) while(1);
	tree[nMem] = Node();
	return nMem++;
}
void update(int l, int r, int fn, pii v, int id) {
//	cout << "UPDATE " << fn << " : " << pii(l, r) << " = " << v << "( " << id << " )" << endl;
	if (l == r) {
		tree[id].v = max(tree[id].v, v);
		return;
	}
	int m = (l + r) / 2;
	int &lc = tree[id].lc;
	int &rc = tree[id].rc;
	if (fn <= m) {
		if (!lc) lc = get_node();
		update(l, m, fn, v, lc);
	} else {
		if (!rc) rc = get_node();
		update(m+1, r, fn, v, rc);
	}
	
	
	tree[id].v = max(tree[lc].v, tree[rc].v);
}
pii query(int l, int r, int fl, int fr, int id) {
//	cout << "QUERY " << pii(fl, fr) << " : " << pii(l, r) <<  "( " << id << " )" << endl;
	if (!id) return {0,-1};
	if (l == fl && r == fr) return tree[id].v;
	int m = (l + r) / 2;
	int lc = tree[id].lc;
	int rc = tree[id].rc;
	if (fr <= m) return query(l, m, fl, fr, lc);
	if (m < fl) return query(m+1, r, fl, fr, rc);
	return max(query(l, m, fl, m, lc), query(m+1, r, m+1, fr, rc));
}

void update(int i, int v) {
	update(0, 1e9, ip[i], pii(v,i), rt);
}
pii query(int l, int r) {
	if (l > r) return {0,-1};
	return query(0, 1e9, l, r, rt);
}

int main() {
	IOS;
	FILEIO("financial");
	cin >> N >> K;
	REP(i,N) cin >> ip[i];
	rt = 1;
	nMem = 2;
	
	int best = 0;
	REP(i,N) {
		pii v = max(query(0,ip[i]-K), query(ip[i]+K,1e9));
		dp[i] = v.F+1;
		prv[i] = v.S;
		if (dp[i] > dp[best]) {
			best = i;
		}
		update(i, dp[i]);
	}
	vector<int> ans;
	while (best >= 0) {
		ans.PB(best);
		best = prv[best];
	}
	reverse(ALL(ans));
	cout << SZ(ans) << endl;
	for (auto it:ans) cout << ip[it] << " ";
	cout << endl;



	return 0;
}
