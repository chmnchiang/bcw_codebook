#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MX = 300006;

struct Node {
	int mn, lazy;
}tree[MX*4];

int N, Q;
char str[MX];
set<int> lbra, rbra;
int sum[MX];

void init(int l, int r, int id) {
	tree[id] = {0, 0};
	if (l == r) {
		tree[id].mn = sum[l];
		return ;
	}
	int mid = (l+r)/2, lc = id*2+1, rc = id*2+2;
	init(l, mid, lc);
	init(mid+1, r,rc);
	tree[id].mn = min(tree[lc].mn, tree[rc].mn);
}

void push(int id) {
	int &val = tree[id].lazy;
	if (!val) return ;
	int lc = id*2+1, rc = id*2+2;
	tree[lc].mn += val;
	tree[lc].lazy += val;
	tree[rc].mn += val;
	tree[rc].lazy += val;
	val = 0;
}

void update(int l, int r, int fl, int fr, int v, int id) {
	if (l == fl && r == fr) {
		tree[id].mn += v;
		tree[id].lazy += v;
		return ;
	}
	push(id);
	int mid = (l+r)/2, lc = id*2+1, rc = id*2+2;
	if (fr <= mid) update(l, mid, fl, fr, v, lc);
	else if (mid < fl) update(mid+1, r, fl, fr, v, rc);
	else {
		update(l, mid, fl, mid, v, lc);
		update(mid+1, r, mid+1, fr, v, rc);
	}
	tree[id].mn = min(tree[lc].mn, tree[rc].mn);
}
int query(int l, int r, int fl, int fr, int id) {
	if (l == fl && r == fr) {
		return tree[id].mn;
	}
	push(id);
	int mid = (l+r)/2, lc = id*2+1, rc = id*2+2;
	if (fr <= mid) return query(l, mid, fl, fr, lc);
	if (mid < fl) return query(mid+1, r, fl, fr, rc);
	return min(query(l, mid, fl, mid, lc),
			query(mid+1, r, mid+1, fr, rc));
}

int main() {
	IOS;
	cin >> N >> Q;
	cin >> &str[1];
	sum[0] = 0;
	for (int i=1; i<=N; i++) {
		if (str[i] == '(') {
			lbra.insert(i);
			sum[i] = sum[i-1] + 1;
		} else {
			rbra.insert(i);
			sum[i] = sum[i-1] - 1;
		}
	}
	init(1, N, 0);
	while (Q--) {
		int v;
		cin >> v;
		if (str[v] == '(') {
			str[v] = ')';
			lbra.erase(v);
			rbra.insert(v);
			update(1, N, v, N, -2, 0);
			int ans = *rbra.begin();
			cout << ans << "\n";
			str[ans] = '(';
			rbra.erase(ans);
			lbra.insert(ans);
			update(1, N, ans, N, 2, 0);
		} else {
			int l = 1, r = v+1;
			str[v] = '(';
			rbra.erase(v);
			lbra.insert(v);
			update(1, N, v, N, 2, 0);

			while (l < r) {
				int mid = (l + r) / 2;
				if (query(1, N, mid, v, 0) <= 1) l = mid+1;
				else r = mid;
			}
			int ans = l;
			cout << ans << "\n";
			str[ans] = ')';
			lbra.erase(ans);
			rbra.insert(ans);
			update(1, N, ans, N, -2, 0);
		}
	}

    return 0;
}

