#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)

typedef long long LL;
const int MXN = 300005;

int N, Q, col[MXN], at[MXN], seq[MXN];
int step,st[MXN],ed[MXN];
__int128_t tree[MXN*4], bit[129], mask;

vector<int> E[MXN];

void DFS(int u) {
	st[u] = at[u] = ++step;
	seq[step] = u;
	for (auto v:E[u])
		DFS(v);
	ed[u] = step;
}
void flip(__int128_t &v, int x) {
	v ^= bit[x];
}
void build_tree(int l, int r, int id) {
	if (l == r) {
		tree[id] = 0;
		int x = seq[l];
		flip(tree[id], col[x]);
		return;
	}
	int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
	build_tree(l, mid, lc);
	build_tree(mid+1, r, rc);
	tree[id] = tree[lc] ^ tree[rc];
}
void update(int l, int r, int fn, int v, int id) {
	if (l == r) {
		int x = seq[l];
		flip(tree[id], col[x]);
		col[x] = v;
		flip(tree[id], col[x]);
		return;
	}
	int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
	if (fn <= mid) update(l, mid, fn, v, lc);
	else update(mid+1, r, fn, v, rc);
	tree[id] = tree[lc] ^ tree[rc];
}
__int128_t query(int l, int r, int fl, int fr, int id) {
	if (l == fl && r == fr) return tree[id];
	int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
	if (fr <= mid) return query(l,mid,fl,fr,lc);
	if (mid<fl) return query(mid+1,r,fl,fr,rc);
	return query(l,mid,fl,mid,lc) ^ query(mid+1,r,mid+1,fr,rc);
}
int getAns(__int128_t x) {
	
	int res=0;
	for (int i=0; i<128; i++)
		if (x & bit[i]) res++;
	return res;
	
	return __builtin_popcount((unsigned long long)(x&mask)) +
	       __builtin_popcount((unsigned long long)((x>>64)&mask));
}

int main() {
	for (int i=0; i<64; i++) {
		mask |= (1LLu << i);
	}
	bit[0] = 1;
	for (int i=1; i<129; i++) {
		bit[i] = bit[i-1] *2;
	}
	while (cin >> N >> Q) {
		for (int i=1; i<=N; i++) {
			E[i].clear();
		}
		for (int i=1; i<=N; i++) {
			cin >> col[i];
			col[i]--;
		}
		for (int i=2, f; i<=N; i++) {
			cin >> f;
			E[f].PB(i);
		}
		step = 0;
		DFS(1);
		build_tree(1, N, 0);
		int K, v;
		while (Q--) {
			cin >> K >> v;
			if (K == 0){
				__int128_t res = query(1,step,st[v],ed[v],0);
				int ans = getAns(res);
				cout << ans << "\n";
			} else {
				K--;
				update(1,step,at[v],K,0);
			}
		}
	}

	return 0;
}

