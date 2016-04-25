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

typedef long long ll;
typedef pair<int,int> pii;
const int MXN = 100005;
const int MEM = 7000005;

struct Event {
	int qid,y,a,b;
};
struct Tree {
	int ch[2],f;
	int l,r;
	ll v;
	Tree () : l(0),r(0),v(0) {
		f = ch[0] = ch[1] = 0;
	}
	Tree (int _l, int _r, ll _v) : l(_l), r(_r), v(_v) {
		f = ch[0] = ch[1] = 0;
	}
}tree[MEM];


int nMem;
int N,M,Q;
ll ans[MXN];
vector<Event> eve;
int vt[MXN];

void travel(int rt) {
	if (rt == 0) return;
	if (tree[rt].l == tree[rt].r) {
		cout << tree[rt].v << " ";
		return;
	}
	travel(tree[rt].ch[0]);
	travel(tree[rt].ch[1]);
}
void dump(int rt) {
	travel(rt);
	cout << endl;
}
int get_node(int l, int r, int v) {
	tree[nMem] = Tree(l,r,v);
	return nMem++;
}
void pull(int t) {
	if (tree[t].l == tree[t].r) return;
	int l = tree[t].ch[0];
	int r = tree[t].ch[1];
	tree[t].v = tree[l].v + tree[r].v;
}
void setCh(int t, int ch, int d) {
	tree[t].ch[d] = ch;
	if (ch == 0) return;
	tree[ch].f = t;
}
int init_tree(int l, int r) {
	int t = get_node(l,r,0);
	if (l == r) {
		tree[t].v = l;
		return t;
	}
	int m = (l+r)/2;
	setCh(t,init_tree(l,m),0);
	setCh(t,init_tree(m+1,r),1);
	pull(t);
	return t;
}
int merge(int a, int b) {
	if (!a) return b;
	if (!b) return a;
//	int t = get_node(tree[a].l, tree[a].r, 0);
	int t = a;
	setCh(t,merge(tree[a].ch[0],tree[b].ch[0]),0);
	setCh(t,merge(tree[a].ch[1],tree[b].ch[1]),1);
//	setCh(t,merge(tree[a].ch[0],tree[b].ch[0]),0);
//	setCh(t,merge(tree[a].ch[1],tree[b].ch[1]),1);
	pull(t);
	return t;
}
pii split(int t, int k) {
	int a,b;
	int m = (tree[t].l+tree[t].r)/2;
	if (t == 0) a = b = 0;
	else if (k == 0) {
		tie(a,b) = make_tuple(0,t);
	} else if (tree[t].l == tree[t].r) {
		if (k == tree[t].l) {
			tie(a,b) = make_tuple(t,0);
		} else {
			tie(a,b) = make_tuple(0,t);
		}
	} else if (k <= m) {
		a = get_node(tree[t].l,tree[t].r,tree[t].v);
		b = get_node(tree[t].l,tree[t].r,tree[t].v);
		setCh(a,0,1);
		setCh(b,tree[t].ch[1],1);
		auto tmp = split(tree[t].ch[0],k);
		setCh(a,tmp.F,0);
		setCh(b,tmp.S,0);
	} else {
		a = get_node(tree[t].l,tree[t].r,tree[t].v);
		b = get_node(tree[t].l,tree[t].r,tree[t].v);
		setCh(a,tree[t].ch[0],0);
		setCh(b,0,0);
		auto tmp = split(tree[t].ch[1],k);
		setCh(a,tmp.F,1);
		setCh(b,tmp.S,1);
	}
	pull(a);
	pull(b);
	return pii(a,b);
}
inline int get_root(int t) {
	while (tree[t].f) t = tree[t].f;
	return t;
}
void go(int t) {
	if (t == 0) return;
	cout << t << " [" << tree[t].l << " ~ " << tree[t].r << "]" << " : " << tree[t].v << endl;
	go(tree[t].ch[0]);
	go(tree[t].ch[1]);
}
int main() {
	nMem = 1;
	IOS;
	cin >> N >> M >> Q;
	REP(_,M) {
		int y,a,b;
		string cmd;
		cin >> y >> cmd >> a >> b;
		if (cmd == "U") {
			eve.PB({-1,y,a,b});
		} else if (cmd == "S") {
			eve.PB({-2,y,a,b});
		}
	}
	REP1(i,1,Q) {
		int y,x;
		cin >> y >> x;
		eve.PB({i,y,x,0});
	}

	int rt = init_tree(1,N);
	REP1(i,1,nMem-1) {
		if (tree[i].l == tree[i].r) vt[tree[i].l] = i;
	}
	REP1(i,1,N) {
		assert(vt[i] != 0);
		auto tmp = split(rt,i);
		rt = tmp.S;
	}

	sort(ALL(eve),[](const Event &a, const Event &b) { return a.y < b.y; } );
	for (auto it:eve) {
		if (it.qid == -1) {
			int a = get_root(vt[it.a]);
			int b = get_root(vt[it.b]);
			merge(a,b);
		} else if (it.qid == -2) {
			int a = get_root(vt[it.a]);
			split(a,it.b-1);
		} else {
			int a = get_root(vt[it.a]);
			ans[it.qid] = tree[a].v;
		}
	}
	REP1(i,1,Q) cout << ans[i] << "\n";
	cerr << "N+M+Q = " << N+M+Q << "," << nMem << endl;


	return 0;
}

