//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	scanf("%d",&head);
	RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
	return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef pair<int,int> pii;

const int MX = 1024;

struct Chip{
	int r,c;
	vector<pii> node;
	Chip () {
		node.PB(MP(0,0));
		node.PB(MP(0,1));
		node.PB(MP(0,2));
		r = 0;
		c = 2;
	}
	void getRC(){
		r = c = -2147483647;
		for (auto it : node){
			r = max(r,it.F);
			c = max(c,it.S);
		}
	}
	void extend(int k){
		k -= c;
		for (int i=1; i<(int)node.size(); i++)
			node[i].S += k;
		getRC();
	}
	void removeST(){
		for (int i=1; i<(int)node.size(); i++){
			node[i-1] = node[i];
		}
		node.resize(node.size()-2);
		for (auto &it : node)
			it.S --;
		getRC();
	}
}G[MX];

Chip op1(Chip a, Chip b){
	Chip ret;
	ret.node.clear();
	ret.node.PB(MP(0,0));
	a.removeST();
	b.removeST();
	for (auto it : a.node){
		ret.node.PB(MP(it.F,it.S+1));
	}
	for (auto it : b.node){
		ret.node.PB(MP(it.F+a.r, it.S+a.c+2));
	}
	ret.node.PB(MP(ret.node.back().F,ret.node.back().S+1));
	ret.getRC();
	return ret;
}
Chip op2(Chip a, Chip b){
	Chip ret;
	ret.node.clear();
	ret.node.PB(MP(0,0));
	a.removeST();
	b.removeST();
	pii x = MP(0,1);
	pii y = MP(a.r+b.r+1,max(a.c,b.c) + 2);
	ret.node.PB(x);
	for (auto it : a.node){
		ret.node.PB(MP(it.F, it.S + y.S - a.c));
	}
	for (auto it : b.node){
		ret.node.PB(MP(it.F + a.r + 1, it.S + 1));
	}
	ret.node.PB(y);
	ret.node.PB(MP(y.F,y.S+1));
	ret.getRC();
	return ret;
}

int main(){
	IOS;
	FILEIO("grid");
	int N;
	while (cin >> N && N != -1){
		for (int i=1; i<=N; i++){
			string op;
			int a,b;
			cin >> op >> a >> b;
			if (op == "+"){
				G[i] = op1(G[a], G[b]);
			} else {
				G[i] = op2(G[a], G[b]);
			}
		}
		cout << G[N].node.size() << "\n";
		for (auto it : G[N].node)
			cout << it.F << " " << it.S << "\n";
//		cout << endl;
	}
	return 0;
}

