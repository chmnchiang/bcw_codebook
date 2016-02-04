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


typedef long long ll;
typedef pair<int,int> pii;
const int MXN = 100005;

struct KDTree {
  struct Node {
    int x,y,x1,y1,x2,y2;
    int id,f;
    Node *L, *R;
  }tree[MXN];
  int n;
  Node *root;

  long long dis2(int x1, int y1, int x2, int y2) {
    long long dx = x1-x2;
    long long dy = y1-y2;
    return dx*dx+dy*dy;
  }
  static bool cmpx(const Node& a, const Node& b) { return a.x<b.x; }
  static bool cmpy(const Node& a, const Node& b) { return a.y<b.y; }
  void init(vector<pair<int,int>> ip) {
    n = ip.size();
    for (int i=0; i<n; i++) {
      tree[i].id = i;
      tree[i].x = ip[i].first;
      tree[i].y = ip[i].second;
    }
    root = build_tree(0, n-1, 0);
  }
  Node* build_tree(int L, int R, int dep) {
    if (L>R) return nullptr;
    int M = (L+R)/2;
    tree[M].f = dep%2;
    nth_element(tree+L, tree+M, tree+R+1, tree[M].f ? cmpy : cmpx);
    tree[M].x1 = tree[M].x2 = tree[M].x;
    tree[M].y1 = tree[M].y2 = tree[M].y;

    tree[M].L = build_tree(L, M-1, dep+1);
    if (tree[M].L) {
      tree[M].x1 = min(tree[M].x1, tree[M].L->x1);
      tree[M].x2 = max(tree[M].x2, tree[M].L->x2);
      tree[M].y1 = min(tree[M].y1, tree[M].L->y1);
      tree[M].y2 = max(tree[M].y2, tree[M].L->y2);
    }

    tree[M].R = build_tree(M+1, R, dep+1);
    if (tree[M].R) {
      tree[M].x1 = min(tree[M].x1, tree[M].R->x1);
      tree[M].x2 = max(tree[M].x2, tree[M].R->x2);
      tree[M].y1 = min(tree[M].y1, tree[M].R->y1);
      tree[M].y2 = max(tree[M].y2, tree[M].R->y2);
    }

    return tree+M;
  }
  int touch(Node* r, int x, int y, long long d2){
    long long dis = sqrt(d2)+1;
    if (x<r->x1-dis || x>r->x2+dis || y<r->y1-dis || y>r->y2+dis)
      return 0;
    return 1;
  }
  void nearest(Node* r, int x, int y, ll &md2) {
    if (!r || !touch(r, x, y, md2)) return;
    long long d2 = dis2(r->x, r->y, x, y);
    if (d2 < md2) {
      md2 = d2;
    }
    // search order depends on split dim
    if ((r->f == 0 && x < r->x) ||
        (r->f == 1 && y < r->y)) {
      nearest(r->L, x, y, md2);
      nearest(r->R, x, y, md2);
    } else {
      nearest(r->R, x, y, md2);
      nearest(r->L, x, y, md2);
    }
  }
  ll query(int x, int y) {
    ll d2 = 102938475612345678LL;
    nearest(root, x, y, d2);
    return d2;
  }
}tree;

struct Point {
	int x, y, id;
};
int N,bye[MXN];
vector<Point> ip;

bool comp(Point a, Point b) {
	ll da = 1LL * a.x * a.x + 1LL * a.y * a.y;
	ll db = 1LL * b.x * b.x + 1LL * b.y * b.y;
	return da < db;
}
vector<int> dc(vector<int> vec) {
	if (SZ(vec) <= 1) {
		return vec;
	}
	int n = SZ(vec);
	int mid = (n-1)/2;
	vector<int> lc,rc;
	for (int i=0; i<=mid; i++)
		lc.PB(vec[i]);
	lc = dc(lc);
	vector<pii> pts;
	for (auto it:lc)
		pts.PB({ip[it].x, ip[it].y});
	tree.init(pts);
	for (int i=mid+1; i<n; i++) {
		int id = vec[i];
		int mx = ip[id].x / 2;
		int my = ip[id].y / 2;
		ll d2 = tree.query(mx, my);
		ll r2 = 1LL * mx * mx + 1LL * my * my;
		if (d2 > r2) rc.PB(id);
	}

	rc = dc(rc);
	
	vector<int> res;
	for (auto it:lc) res.PB(it);
	for (auto it:rc) res.PB(it);
	return res;
}

int main() {
	IOS;
	FILEIO("nothingontv");
	cin >> N;
	ip.resize(N);
	for (int i=0, x, y; i<N; i++) {
		cin >> x >> y;
		x <<= 1;
		y <<= 1;
		ip[i] = {x,y,i};
	}
	sort(ALL(ip), comp);
	vector<int> ans;
	for (int i=0; i<N; i++)
		ans.PB(i);
	ans = dc(ans);
	cout << SZ(ans) << endl;
	for (int i=0; i<SZ(ans); i++) {
		int id = ip[ans[i]].id + 1;
		cout << id << " \n"[i == SZ(ans) - 1];
	}

    return 0;
}

