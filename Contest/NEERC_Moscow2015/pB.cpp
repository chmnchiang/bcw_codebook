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

const int MX = 543210;

struct SegmentTree {
	struct State {
		int l, r, id;
	};
	int n, tree[MX*8];
	vector<State> vec;
	void init_tree(int l, int r, int id, int a[]) {
		tree[id] = 0;
		if (l == r) {
			tree[id] = a[l];
			return ;
		}
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		init_tree(l, mid, lc, a);
		init_tree(mid+1, r, rc, a);
		tree[id] = max(tree[lc], tree[rc]);
	}

	void init(int a[], int len) {
		n = len;
		init_tree(0, len, 0, a);
	}
	void qry(int l, int r, int fl, int fr, int x, int id) {
		if (l == fl && r == fr) {
			vec.PB({l, r, id});
			return ;
		}
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		if (fr <= mid) return qry(l, mid, fl, fr, x, lc);
		if (mid < fl) return qry(mid+1, r, fl, fr, x, rc);
		qry(l, mid, fl, mid, x, lc);
		qry(mid+1, r, mid+1, fr, x, rc);
	}
	int go(int l, int r, int x, int id) {
		if (l == r) return l;
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		if (tree[rc] >= x) return go(mid+1, r, x, rc);
		return go(l, mid, x, lc);
	}
	int query(int l, int r, int x) {
		vec.clear();
		qry(0, n, l, r, x, 0);
		reverse(ALL(vec));
		for (auto it : vec) {
			int id = it.id;
			if (tree[id] >= x) {
				return go(it.l, it.r, x, it.id);
			}
		}
		return -1;
	}

}tree;

char A[MX], B[MX];
int la, lb;
char s1[MX*3], s2[MX*3];
int z1[MX*3], z2[MX*3];
int zz[MX*3];
int l1, l2;
int dq[MX*3], dh, dt;

void Z_value(char *s, int *z, int len) {
	int i,j,left,right;
	left=right=0; z[0]=len;
	for(i=1;i<len;i++) {
		j=max(min(z[i-left],right-i),0);
		for(;i+j<len&&s[i+j]==s[j];j++);
		z[i]=j;
		if(i+z[i]>right) {
			right=i+z[i];
			left=i;
		}
	}
}

void push_in(int p) {
	while (dh > dt and dq[dh-1] <= z2[p]) {
		dh --;
	}

	dq[dh++] = z2[p];
}

int main() {

	scanf("%s%s", A, B);
	la = strlen(A); lb = strlen(B);

	for (int i=0; i<lb; i++) {
		s1[i] = B[i];
	}

	for (int i=0; i<la; i++) {
		s1[lb+i] = s1[lb+i+la] = A[i];
	}

	for (int i=0; i<lb; i++) {
		s2[i] = B[lb-i-1];
	}

	for (int i=0; i<la; i++) {
		s2[lb+i] = s2[lb+i+la] = A[la-i-1];
	}

	l1 = l2 = la + la + lb;	
	Z_value(s1, z1, l1);
	Z_value(s2, z2, l2);


	if (lb > la) {
		puts("-1"); return 0;
	}

	for (int i=lb; i<lb+la; i++) {
		if (z1[i] >= lb) {
			printf("%d\n", la);
			return 0;
		}
	}

	for (int i=0; i<la; i++) {
		zz[i] = zz[i+la] = z2[lb+la-i-1];
	}

	tree.init(z1+lb, la*2); 

	bool hv = false;
	int ans = 0;
	for (int i=0; i<la; i++) {
		int jl = i + 1, jr = la - lb + i + 1;
		int zi = zz[i];
		int id = -1;
		id = tree.query(jl, jr, lb - zi);
//		int id = -1;
//		for (int j=jr; j>=jl; j--) {
//			if (z1[lb+j] >= lb-zi) {
//				id = j;break;
//			}
//		}
		if (id != -1) {
			hv = true;
			ans = max(ans, id - i - 1 + lb);
		}
	}

	if (!hv) {
		puts("-1");
	} else printf("%d\n", ans);


    return 0;
}

