#include <bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MXN = 30005;
const int MEM = MXN * 35;

struct Node {
	int is;
	int eg[2];
}tree[MEM];

int N, nMem, root;
vector<string> ans;

int getNode() {
	tree[nMem].is = 0;
	tree[nMem].eg[0] = tree[nMem].eg[1] = 0;
	return nMem++;
}

string toStr(long long c) {
	if (c == 0) return string("0");
	string ret;
	while (c) {
		ret += static_cast<char>('0' + c % 10);
		c /= 10;
	}
	reverse(ret.begin(), ret.end());
	return ret;
}

void DFS(int id, int dep, int bit[]) {
	if (tree[id].is) return;
	if (!tree[id].eg[0] && !tree[id].eg[1]) {
		string str;
		for (int i=0; i<4; i++) {
			int c = 0;
			for (int j=0; j<8; j++) {
				c <<= 1;
				c += bit[i*8+j];
			}
			str += toStr(c);
			if (i == 3) {
				str += "/";
			} else {
				str += ".";
			}
		}
		str += toStr(dep+1);
		ans.PB(str);

		return ;
	}
	bit[dep] = 0;
	if (tree[id].eg[0]) {
		DFS(tree[id].eg[0], dep+1, bit);
	} else {
		string str;
		for (int i=0; i<4; i++) {
			int c = 0;
			for (int j=0; j<8; j++) {
				c <<= 1;
				c += bit[i*8+j];
			}
			str += toStr(c);
			if (i == 3) {
				str += "/";
			} else {
				str += ".";
			}
		}
		str += toStr(dep+1);
		ans.PB(str);
	}
	bit[dep] = 1;
	if (tree[id].eg[1]) {
		DFS(tree[id].eg[1], dep+1, bit);
	} else {
		string str;
		for (int i=0; i<4; i++) {
			int c = 0;
			for (int j=0; j<8; j++) {
				c <<= 1;
				c += bit[i*8+j];
			}
			str += toStr(c);
			if (i == 3) {
				str += "/";
			} else {
				str += ".";
			}
		}
		str += toStr(dep+1);
		ans.PB(str);
	}
	bit[dep] = 0;
}

int trash;
int main() {
	int nT;
	trash = scanf("%d", &nT);
	for (int t=1; t<=nT; t++) {
		nMem = 1;
		trash = scanf("%d", &N);
		root = getNode();
		for (int i=1; i<=N; i++) {
			int ip[4], subnet;
			int bit[32];
			trash = scanf("%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &subnet);
			for (int j=0, c=0; j<4; j++) {
				for (int k=0; k<8; k++) {
					bit[c++] = (ip[j] >> (8-k-1)) & 1;
				}
			}
			int id = root;
			for (int j=0; j<subnet; j++) {
				if (tree[id].eg[bit[j]]) {
					// do nothing
				} else {
					tree[id].eg[bit[j]] = getNode();
				}
				id = tree[id].eg[bit[j]];
			}
			tree[id].is = 1;
		}
		if (!tree[root].eg[0] && !tree[root].eg[1]) {
			printf("Case #%d:\n", t);
			if (tree[root].is) {
				puts("0");
			} else {
				printf("1\n");
				printf("0.0.0.0/0\n");
			}
			continue;
		}
		ans.clear();
		int bit[32];
		FZ(bit);
		int id = root;
		DFS(id, 0, bit);
		printf("Case #%d:\n", t);
		printf("%d\n", SZ(ans));
		for (const auto& it : ans)
			printf("%s\n", it.c_str());
	}

	return 0;
}
