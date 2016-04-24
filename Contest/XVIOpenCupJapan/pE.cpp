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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 201010;

pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}
ll operator % (const pii &a, const pii &b) { return (ll)a.F*b.S - (ll)a.S*b.F; }
double ang(pii a){return atan2(a.S, a.F);}

struct Lisan {
	vector<int> seq;
	void add(int x) { seq.PB(x); }
	void make() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq); }
}lx;
struct Segment {
  pii p,q;
  int v;
  Segment () {}
  Segment (pii _p, pii _q, int _v) :
    p(_p), q(_q), v(_v) {}
  double at(double x) {
	  pii d = q - p;
	  double dx = x - p.F;
	  return p.S + dx * d.S / d.F;
  }
};
bool operator < (const Segment &a, const Segment &b) {
  if (a.p == b.q) return false;
  if (a.q == b.p) return true;
  if (a.p == b.p) return (a.q-a.p) % (b.q-a.p) > 0;
  if (a.q == b.q) return (a.p-a.q) % (b.p-a.q) < 0;
  if (a.p.F == b.p.F) return a.p.S < b.p.S;
  if (a.q.F == b.q.F) return a.q.S < b.q.S;
  if (a.p.F < b.p.F) return (a.q-a.p) % (b.p-a.p) > 0;
  else return (b.q-b.p) % (a.p-b.p) < 0;
}

const int MEM = 350004;
struct Treap {
  static Treap nil, mem[MEM], *pmem;
  Treap *l, *r;
  int sum,size,pri;
  Segment seg;
  Treap () : l(&nil), r(&nil), sum(0), size(0), pri(0), seg() {}
  Treap (Segment _val) : 
    l(&nil), r(&nil), sum(_val.v), size(1), seg(_val) {
		pri = rand();
	}
} Treap::nil, Treap::mem[MEM], *Treap::pmem = Treap::mem;

int size(const Treap *t) { return t->size; }
void pull(Treap *t) {
  if (!size(t)) return;
  t->size = size(t->l) + size(t->r) + 1;
  t->sum = t->l->sum + t->seg.v + t->r->sum;
}
Treap* merge(Treap *a, Treap *b) {
  if (!size(a)) return b;
  if (!size(b)) return a;
  Treap *t;
  if (a->pri > b->pri) {
    t = a;
    t->r = merge(a->r, b);
  } else {
    t = b;
    t->l = merge(a, b->l);
  }
  pull(t);
  return t;
}
void split(Treap *t, int k, Treap *&a, Treap *&b) {
  if (!size(t)) a = b = &Treap::nil;
  else if (size(t->l) + 1 <= k) {
    a = t;
    split(t->r, k - size(t->l) - 1, a->r, b);
    pull(a);
  } else {
    b = t;
    split(t->l, k, a, b->l);
    pull(b);
  }
}
int get_rank(Treap *t, Segment x) {
  if (!size(t)) return 0;
  if (x < t->seg) return get_rank(t->l, x);
  return get_rank(t->r,x) + size(t->l) + 1;
}
int get_pt_rank(Treap *t, pii x) {
	if (!size(t)) return 0;
	if (t->seg.at(x.F) > x.S) return get_pt_rank(t->l, x);
	return t->seg.v + t->l->sum + get_pt_rank(t->r, x);
}
Treap* find_leftist(Treap *t) {
  while (size(t->l)) t = t->l;
  return t;
}
Treap* find_rightist(Treap *t) {
  while (size(t->r)) t = t->r;
  return t;
}

int N, M, Q;
pii pt[MAXN];
int deg[MAXN];
set<int> sedge[MAXN];
pii edge[MAXN];
pii qt[MAXN];
bool vcanuse[MAXN];
vector<int> vedge[MAXN];
map<int, int> vmedge[MAXN];
int ord[MAXN], qord[MAXN];
bool vused[MAXN];
int curv;
vector<pii> evec;
vector<Segment> vseg;
bool qans[MAXN];
vector<Segment> addseg[MAXN],subseg[MAXN];
vector<int> qlx[MAXN];
double tmp[MAXN];

bool cmp(int a, int b)
{
	return pt[a] < pt[b];
}

bool cmp2(int e1, int e2)
{
	return tmp[e1] < tmp[e2];
}

void tag(int v)
{
	if(vused[v]) return;
	vused[v] = true;
	for(auto e: vedge[v])
	{
		int u = (edge[e].F == v ? edge[e].S : edge[e].F);
		tag(u);
	}
}

void solve()
{
	for(int i=0; i<N; i++)
		vcanuse[i] = true;
	for(int i=0; i<M; i++)
	{
		int u = edge[i].F, v = edge[i].S;
		if(!vcanuse[v] || !vcanuse[u]) continue;
		vedge[u].PB(i);
		vedge[v].PB(i);
	}

	for(int i=0; i<N; i++)
	{
		if(!vcanuse[i]) continue;
		curv = i;
		for(int j=0; j<SZ(vedge[i]); j++)
		{
			int e = vedge[i][j];
			int u = (edge[e].F == i ? edge[e].S : edge[e].F);
			tmp[j] = ang(pt[u] - pt[i]);
		}
		vector<int> uord;
		for(int j=0; j<SZ(vedge[i]); j++)
			uord.PB(j);
		sort(ALL(uord), cmp2);
		vector<int> ve = vedge[i];
		for(int j=0; j<SZ(uord); j++)
			vedge[i][j] = ve[uord[j]];

		for(int j=0; j<SZ(vedge[i]); j++)
			vmedge[i][vedge[i][j]] = j;
	}

	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(ord, ord+N, cmp);

	for(int ii=0; ii<N; ii++)
	{
		int i = ord[ii];
		if(!vcanuse[i]) continue;
		if(vused[i]) continue;
		if(vedge[i].empty()) continue;

		int v = i;
		int e = vedge[v][0];
		int startv = v, starte = e;
		while(true)
		{
			int nv = (edge[e].F == v ? edge[e].S : edge[e].F);
			int s = vedge[nv].size();
			int id = vmedge[nv][e];
			e = vedge[nv][(id+1)%s];
			evec.PB({v, nv});
			v = nv;
			if(v == startv && e == starte) break;
		}

		tag(i);
	}

//	cout<<evec<<endl;
	for(auto e: evec)
	{
		pii pu = pt[e.F], pv = pt[e.S];
		int val = 1;
		if(pu.F == pv.F) continue;
		if(pu.F > pv.F)
		{
			swap(pu, pv);
			val = -1;
		}
		vseg.PB({pu, pv, val});
	}
//	for(auto v: vseg) cout<<v.p<<" "<<v.q<<" "<<v.v<<endl;

	for (int i=0; i<N; i++) {
		lx.add(pt[i].F);
	}
	for (int i=0; i<Q; i++) {
		lx.add(qt[i].F);
	}
	lx.make();
	for (auto it:vseg) {
		int x1 = lx.qry(it.p.F);
		int x2 = lx.qry(it.q.F);
		addseg[x1].PB(it);
		subseg[x2].PB(it);
	}
	for (int i=0; i<Q; i++) {
		qlx[lx.qry(qt[i].F)].PB(i);
	}

	Treap *rt = &Treap::nil;
	for (int i=0; i<SZ(lx.seq); i++) {
		for (auto it:subseg[i]) {
			Treap *tl,*tm,*tr;
			int k = get_rank(rt,it);
			split(rt,k-1,tl,tm);
			split(tm,1,tm,tr);
			rt = merge(tl,tr);
		}

		for (auto it:addseg[i]) {
			int k = get_rank(rt,it);
			Treap *tl,*tm,*tr;
			split(rt,k,tl,tr);
			tm = new (Treap::pmem++) Treap(it);
			rt = merge(merge(tl,tm),tr);
		}

		for (auto qid:qlx[i]) {
			int sum = get_pt_rank(rt, qt[qid]);
			qans[qid] = (sum > 0);
		}

	}
/*
	for(int i=0; i<Q; i++)
	{
		pii q = qt[i];
		int v = 0;
		for(auto s: vseg)
		{
			if(s.p.F <= q.F && s.q.F > q.F && s.at(q.F) < q.S)
				v += s.v;
		}
		qans[i] = (v > 0);
	}
	*/
}

int main() {
	IOS;

	cin>>N>>M>>Q;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;
	for(int i=0; i<M; i++)
	{
		cin>>edge[i].F>>edge[i].S;
		edge[i].F--;
		edge[i].S--;
	}
	for(int i=0; i<Q; i++)
		cin>>qt[i].F>>qt[i].S;

	solve();

	for(int i=0; i<Q; i++)
		cout<<(qans[i] ? "Yes" : "No")<<"\n";

//	cout<<"  ==== XDD ====  "<<endl;

	return 0;
}

