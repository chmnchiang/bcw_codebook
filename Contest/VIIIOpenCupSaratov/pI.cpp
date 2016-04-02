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

const int MXN = 100005;
typedef pair<int,int> pii;
struct Node {
	int id,sum,l;
	friend ostream& operator << (ostream &s, Node he) {
		return s << "[" << he.id << "," << he.sum << "," << he.l << "]";
	}
};
struct set_t {
	int offSum,offL;
	map<int,Node> mp;
	int size() { return SZ(mp); }
	int exist(int x) {
		return mp.count(x-offSum);
	}
	Node qry(int x) {
		assert(exist(x));
		x -= offSum;
		Node res = mp[x];
		res.sum += offSum;
		res.l += offL;
		return res;
	}
	void add(Node v) {
		v.sum -= offSum;
		v.l -= offL;
		if (not mp.count(v.sum)) mp[v.sum] = v;
		else if (mp[v.sum].l < v.l) mp[v.sum] = v;
	}
	vector<Node> get_vec() {
		vector<Node> vec;
		for (auto it:mp) {
			vec.PB(it.S);
			vec.back().sum += offSum;
			vec.back().l += offL;
		}
		return vec;
	}
	
}st[MXN];

int N,value[MXN],sid[MXN];
int plen;
pii path;
vector<int> pvec;
string str;
vector<int> E[MXN];

int merge(int x, int y) {
	if (st[x].size() < st[y].size()) swap(x,y);
//	cout << "MERGE " << x << " " << y << endl;
//	cout << st[x].get_vec() << endl;
//	cout << st[y].get_vec() << endl;
	auto vec = st[y].get_vec();
	for (auto it:vec) st[x].add(it);
	return x;
}
void update_answer(int x, int y) {
	if (st[x].size() < st[y].size()) swap(x,y);
//	cout << st[y].get_vec() << endl;
//	cout << st[x].get_vec() << endl;
	auto vec = st[y].get_vec();
	for (auto it:vec) {
		if (st[x].exist(-it.sum)) {
			auto res = st[x].qry(-it.sum);
			int len = res.l + it.l;
			int id = res.id;
//			cout << pii(id,it.id) << " " << res.l << " " << it.l << " " << len << endl;
			if (plen < len) {
				plen = len;
				path = pii(id,it.id);
			}
		}
	}
}
void DFS(int u, int f) {
	sid[u] = u;
	st[u].offL = st[u].offSum = 0;
	st[u].add({u,value[u],1});
	for (auto it:E[u]) {
		int v = it;
		if (v == f) continue;
		DFS(v,u);
//		cout << "UPDATE ANSWER " << u << endl;
		update_answer(sid[u], sid[v]);

		st[sid[v]].offL += 1;
		st[sid[v]].offSum += value[u];

		sid[u] = merge(sid[u], sid[v]);
	}

	int id = sid[u];
	if (st[id].exist(0)) {
		auto res = st[id].qry(0);
		int len = res.l;
		if (plen < len) {
			plen = len;
			path = pii(u,res.id);
		}
	}
//	cout << u << " : " << st[id].get_vec() << endl;
}
bool go(int u, int f) {
	if (u == path.S) {
		pvec.PB(u);
		return true;
	}
	for (auto it:E[u]) {
		int v = it;
		if (v == f) continue;
		if (go(v,u)) {
			pvec.PB(u);
			return true;
		}
	}
	return false;
}
int main() {
	IOS;
	FILEIO("shoes");
	cin >> N;
	cin >> str;
	REP(i,N) {
		if (str[i] == 'L') value[i+1] = -1;
		else value[i+1] = 1;
	}
	REP(_,N-1) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
		E[v].PB(u);
	}
	plen = -1;
	DFS(1,1);
	if (plen == -1) cout << 0 << endl;
	else {
		cout << plen << endl;
		pvec.clear();
		go(path.F,path.F);
		assert(plen == SZ(pvec));
		for (auto v:pvec)
			cout << v << " ";
		cout << endl;
	}

	return 0;
}

