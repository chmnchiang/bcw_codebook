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
// Let's Fight!

const int MXN = 200005;

struct Node {
	int v, lc, rc;
}tree[MXN*32];

int N, nMem, d;

int getNode() {
	tree[nMem] = {0, 0, 0};
	return nMem++;
}

void update(int l, int r, int fl, int fr, int id) {
	if (l == fl && r == fr) {
		tree[id].v++;
		return;
	}
	int mid=(l+r)/2;
	int &lc=tree[id].lc;
	int &rc=tree[id].rc;
	if (fr <= mid) {
		if (!lc) lc = getNode();
		update(l, mid, fl, fr, lc);
	} else if (mid < fl) {
		if (!rc) rc = getNode();
		update(mid+1, r, fl, fr, rc);
	} else {
		if (!lc) lc = getNode();
		if (!rc) rc = getNode();
		update(l, mid, fl, mid, lc);
		update(mid+1, r, mid+1, fr, rc);
	}
}

int query(int l, int r, int fn, int id) {
	if (id == 0) return 0;
	int mid=(l+r)/2;
	if (fn <= mid) return query(l,mid,fn,tree[id].lc) + tree[id].v;
	else return query(mid+1,r,fn,tree[id].rc) + tree[id].v;
}

int main() {
	FILEIO("environment");
	IOS;
	nMem = 1;
	int rt = getNode();
	cin >> N;
	d = 0;
	while (N--) {
		int cmd, l, r, x;
		cin >> cmd;
		if (cmd == 1) {
			cin >> l >> r;
			l += d;
			r += d;
			update(0, 1000000000, l, r, rt);
		} else {
			cin >> x;
			d = query(0, 1000000000, x, rt);
			cout << d << "\n";
		}
	}

    return 0;
}
