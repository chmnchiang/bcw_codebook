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
const int MXN = 10005;

struct Lisan {
	vector<int> seq;
	void init() {
		seq.clear();
	}
	void add(int x){ seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq)) - begin(seq));
	}
	int query(int x) {
		return lower_bound(ALL(seq), x) - begin(seq);
	}
}lisanX, lisanY;

struct Node {
	int best;
	pii cnt;
}tree[MXN*4];

struct Point {
	int x, y, c;
};

bool operator == (const Point &a, const Point &b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

int N;
Point pt[MXN];

void predo() {
	lisanX.init();
	lisanY.init();
	for (int i=0; i<N; i++) {
		lisanX.add(pt[i].x);
		lisanY.add(pt[i].y);
	}
	lisanX.build();
	lisanY.build();
	for (int i=0; i<N; i++) {
		pt[i].x = lisanX.query(pt[i].x);
		pt[i].y = lisanY.query(pt[i].y);
	}
}

void init(int l, int r, int id) {
	tree[id].cnt = {0, 0};
	tree[id].best = 0;
	if (l == r) return ;
	int mid = (l+r)/2, lc = id*2+1, rc = id*2+2;
	init(l, mid, lc);
	init(mid+1, r, rc);
}
void pull(int id, int lc, int rc) {
	tree[id].cnt.F = tree[lc].cnt.F + tree[rc].cnt.F;
	tree[id].cnt.S = tree[lc].cnt.S + tree[rc].cnt.S;
	tree[id].best = max(tree[lc].best + tree[rc].cnt.S, tree[rc].best + tree[lc].cnt.F);
	tree[id].best = max(tree[id].best, tree[lc].cnt.F + tree[rc].cnt.S);
}
void add(int l, int r, int fn, int c, int id) {
	if (l == r) {
		if (c == 0) tree[id].cnt.F++;
		else tree[id].cnt.S++;
		tree[id].best = max(tree[id].cnt.F, tree[id].cnt.S);
		return ;
	}
	int mid = (l+r)/2, lc = id*2+1, rc = id*2+2;
	if (fn <= mid) add(l, mid, fn, c, lc);
	else add(mid+1, r, fn, c, rc);
	pull(id, lc, rc);
	//cout << "best[" << id << "]: " << tree[id].best << endl;
}

int suf[MXN], pre[MXN], mx[MXN], preA[MXN];

bool comp(Point a, Point b) {
	return a.x < b.x;
}
int solve(int a, int b, int c) {
	init(0, N, 0);
	suf[N] = 0;
	for (int i=N-1; i>=0; i--) {
		suf[i] = suf[i+1];
		if (pt[i].c == c) suf[i]++;
	}
	pre[0] = pt[0].c == b ? 1 : 0;
	preA[0] = pt[0].c == a ? 1 : 0;
	for (int i=1; i<N; i++) {
		pre[i] = pre[i-1];
		if (pt[i].c == b) pre[i]++;
		preA[i] = preA[i-1];
		if (pt[i].c == a) preA[i]++;
	}
	mx[N] = pre[N-1];
	for (int i=N-1; i>=0; i--) {
		mx[i] = suf[i+1] + pre[i];
		mx[i] = max(mx[i], mx[i+1]);
	}
	/*
	for (int i=0; i<N; i++) {
		cout << pt[i].x << " " << pt[i].y << " , color " << pt[i].c << endl;
	}
	*/
	int ret = 0;
	for (int i=N-1, prvX=-1; i>=0; prvX=pt[i].x) {
		while (i >= 0 && prvX == pt[i].x) {
			if (pt[i].c == b) {
				add(0, N, pt[i].y, 0, 0);
				//cout << "ADD 0 " << pt[i].y << endl;
			} else if (pt[i].c == c) {
				//cout << "ADD 1 " << pt[i].y << endl;
				add(0, N, pt[i].y, 1, 0);
			}
			i--;
		}
		if (i < 0) break;
		int r1 = preA[i] + mx[i+1] - pre[i];
		int r2 = tree[0].best + preA[i];
		//cout << "I = " << i << " : " << r1 << " , " << r2 << endl;
		//cout << preA[i] << " " << tree[0].best << endl;
		ret = max(ret, r1);
		ret = max(ret, r2);
	}
	ret = max(ret, tree[0].best);
	//cout << a << " " << b << " " << c << " : " << ret << endl;
	return ret;
}

int main() {
	IOS;
	int nT, A, B, C;
	cin >> nT;
	while (nT--) {
		N = 0;
		cin >> A >> B >> C;
		for (int i=0; i<A; i++) {
			cin >> pt[N].x >> pt[N].y;
			pt[N++].c = 0;
		}
		for (int i=0; i<B; i++) {
			cin >> pt[N].x >> pt[N].y;
			pt[N++].c = 1;
		}
		for (int i=0; i<C; i++) {
			cin >> pt[N].x >> pt[N].y;
			pt[N++].c = 2;
		}
		int per[3];

		predo();
		sort(pt, pt+N, comp);
		per[0] = 0; per[1] = 1; per[2] = 2;
		int ans = 0;
		do {
			ans = max(ans, solve(per[0], per[1], per[2]));
		} while (next_permutation(per, per+3));

		reverse(pt, pt+N);
		per[0] = 0; per[1] = 1; per[2] = 2;
		do {
			ans = max(ans, solve(per[0], per[1], per[2]));
		} while (next_permutation(per, per+3));

		//////// ROTATE /////////

		for (int i=0; i<N; i++) {
			swap(pt[i].x, pt[i].y);
		}
		sort(pt, pt+N, comp);
		per[0] = 0; per[1] = 1; per[2] = 2;
		do {
			ans = max(ans, solve(per[0], per[1], per[2]));
		} while (next_permutation(per, per+3));

		reverse(pt, pt+N);
		per[0] = 0; per[1] = 1; per[2] = 2;
		do {
			ans = max(ans, solve(per[0], per[1], per[2]));
		} while (next_permutation(per, per+3));

		cout << ans << endl;
	}

	return 0;
}

