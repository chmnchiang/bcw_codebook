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
const int MX = 500005;

const int MEM = 500005;
struct Splay {
	static Splay nil, mem[MEM], *pmem;
	Splay *ch[2], *f;
	int val, sum, rev, size;
	Splay () : val(0), sum(0), rev(0), size(0) {
		f = ch[0] = ch[1] = &nil;
	}
	Splay (int _val) : val(_val), sum(_val), rev(0), size(1) {
		f = ch[0] = ch[1] = &nil;
	}
	bool isr() {
		return f->ch[0] != this && f->ch[1] != this;
	}
	int dir() {
		return f->ch[0] == this ? 0 : 1;
	}
	void setCh(Splay *c, int d) {
		ch[d] = c;
		if (c != &nil) c->f = this;
		pull();
	}
	void push() {
		if (rev) {
			swap(ch[0], ch[1]);
			if (ch[0] != &nil) ch[0]->rev ^= 1;
			if (ch[1] != &nil) ch[1]->rev ^= 1;
			rev=0;
		}
	}
	void pull() {
		size = ch[0]->size + ch[1]->size + 1;
		sum = ch[0]->sum + ch[1]->sum + this->val;
		if (ch[0] != &nil) ch[0]->f = this;
		if (ch[1] != &nil) ch[1]->f = this;
	}
} Splay::nil, Splay::mem[MEM], *Splay::pmem = Splay::mem;
Splay *nil = &Splay::nil;
void rotate(Splay *x) {
	Splay *p = x->f;
	int d = x->dir();
	if (!p->isr()) p->f->setCh(x, p->dir());
	else x->f = p->f;
	p->setCh(x->ch[!d], d);
	x->setCh(p, !d);
	p->pull(); x->pull();
}
vector<Splay*> splayVec;
void splay(Splay *x) {
	splayVec.clear();
	for (Splay *q=x;; q=q->f) {
		splayVec.push_back(q);
		if (q->isr()) break;
	}
	reverse(begin(splayVec), end(splayVec));
	for (auto it : splayVec) it->push();
	while (!x->isr()) {
		if (x->f->isr()) rotate(x);
		else if (x->dir()==x->f->dir()) rotate(x->f),rotate(x);
		else rotate(x),rotate(x);
	}
}
Splay* access(Splay *x) {
	Splay *q = nil;
	for (;x!=nil;x=x->f) {
		splay(x);
		x->setCh(q, 1);
		q = x;
	}
	return q;
}
void evert(Splay *x) {
	access(x);
	splay(x);
	x->rev ^= 1;
	x->push(); x->pull();
}
void link(Splay *x, Splay *y) {
	evert(x);
	access(x);
	splay(x);
	evert(y);
	x->setCh(y, 1);
}
void cut(Splay *x, Splay *y) {
	evert(x);
	access(y);
	splay(y);
	y->push();
	y->ch[0] = y->ch[0]->f = nil;
}

int N,Q,val[MX],dep[MX],fa[MX];
vector<pii> E[MX];
Splay *vt[MX];

void DFS(int u, int f, int d) {
	dep[u] = d;
	fa[u] = f;
	for (auto it:E[u]) {
		int v = it.F;
		int w = it.S;
		if (v == f) continue;
		val[v] = w;
		DFS(v,u,d+1);
	}
}
int main() {
	IOS;
	cin >> N >> Q;
	REP(i,N-1) {
		int u,v,c;
		cin >> u >> v >> c;
		E[u].PB({v,c});
		E[v].PB({u,c});
	}
	DFS(1,1,1);

	REP1(i,1,N) {
		vt[i] = new (Splay::pmem++) Splay(val[i]);
	}
	REP1(i,2,N) {
		link(vt[fa[i]],vt[i]);
	}
	int u,v,w;
	string cmd;
	REP(_,Q) {
		cin >> cmd;
		if (cmd == "S") {
			cin >> u >> v >> w;
			if (dep[u] > dep[v]) swap(u,v);
			assert(fa[v] == u);

			evert(vt[v]);
			vt[v]->val = w;
			vt[v]->push();
			vt[v]->pull();

			val[v] = w;

		} else {
			cin >> v;
			evert(vt[1]);
			auto t = access(vt[v]);
			cout << t->sum << "\n";
		}
	}


	return 0;
}

