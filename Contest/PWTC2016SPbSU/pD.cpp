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

typedef pair<int,int> pii;
const int MX = 100005;
const int INF = 1029384756;

struct Item {
	int v1,v2,id;
}item[MX];
struct Node {
	int v,tag;
}tree[MX*5];

int N,A[MX],B[MX],at[MX];
pii arr[MX];

void init_tree(int l, int r, int id) {
	tree[id] = {0,0};
	if (l == r) {
		tree[id].v = l/2;
		return;
	}
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	init_tree(l,m,lc);
	init_tree(m+1,r,rc);
	tree[id].v = min(tree[lc].v,tree[rc].v);
}
void push(int id, int lc, int rc) {
	int &v= tree[id].tag;
	tree[lc].tag += v;
	tree[lc].v += v;
	tree[rc].tag += v;
	tree[rc].v += v;
	v = 0;
}
void update(int l, int r, int fl, int fr, int id) {
	if (l == fl and r == fr) {
		tree[id].v--;
		tree[id].tag--;
		return;
	}
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	push(id,lc,rc);
	if (fr <= m) update(l,m,fl,fr,lc);
	else if (m < fl) update(m+1,r,fl,fr,rc);
	else {
		update(l,m,fl,m,lc);
		update(m+1,r,m+1,fr,rc);
	}
	tree[id].v = min(tree[lc].v,tree[rc].v);
}
int query(int l, int r, int fl, int fr, int id) {
	if (r < fl) return INF;
	if (fr < l) return INF;
	if (fl <= l and r <= fr) return tree[id].v;
	int m=(l+r)/2, lc=id*2, rc=id*2+1;
	push(id,lc,rc);
	return min(query(l,m,fl,fr,lc),query(m+1,r,fl,fr,rc));
}

int main() {
	IOS;
	cin >> N;
	REP1(i,1,N) cin >> A[i];
	REP1(i,1,N) cin >> B[i];
	REP1(i,1,N) {
		item[i] = {A[i],B[i],i};
		arr[i] = pii(B[i],i);
	}
	sort(item+1,item+N+1,[](Item a, Item b) { return make_pair(-a.v1,-a.v2) < make_pair(-b.v1,-b.v2);} );
	REP1(i,1,N) at[item[i].id] = i;

	init_tree(1,N,1);
	sort(arr+1,arr+N+1);
	reverse(arr+1,arr+N+1);
	long long ans = 0;
	REP1(ii,1,N) {
		int w = arr[ii].F;
		int id = arr[ii].S;
		int pos = at[id];

		if (query(1,N,pos,N,1) <= 0) continue;

		ans = ans + w;
		update(1,N,pos,N,1);

	}
	cout << ans << endl;

	return 0;
}
